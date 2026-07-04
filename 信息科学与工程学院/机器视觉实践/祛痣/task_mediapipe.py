import argparse
import sys
from pathlib import Path

import cv2
import mediapipe as mp
import numpy as np

# 有些安装环境中 `mediapipe` 包的 `solutions` 子模块可能不可直接通过 `mp.solutions` 访问
# 我们尝试稳健地获取 `mediapipe.solutions` 到 `mpsol` 变量中
try:
	mpsol = mp.solutions
except Exception:
	try:
		import mediapipe.solutions as mpsol  # type: ignore
	except Exception as e:
		raise ImportError(
			"无法导入 mediapipe.solutions。请确认 mediapipe 已正确安装，或使用 `pip install mediapipe`。"
		) from e


MARGIN = 0.25  # 扩大人脸框比例，保证覆盖到脸边的痣


def detect_faces_mediapipe(img_bgr, min_conf=0.4, model_selection=1):
	"""使用 MediaPipe FaceDetection 返回人脸框列表 (x, y, w, h)。"""
	h, w = img_bgr.shape[:2]
	faces = []
	with mpsol.face_detection.FaceDetection(
		model_selection=model_selection, min_detection_confidence=min_conf
	) as fd:
		rgb = cv2.cvtColor(img_bgr, cv2.COLOR_BGR2RGB)
		results = fd.process(rgb)
		if not results.detections:
			return faces
		for det in results.detections:
			box = det.location_data.relative_bounding_box
			x = int(box.xmin * w)
			y = int(box.ymin * h)
			bw = int(box.width * w)
			bh = int(box.height * h)
			faces.append((x, y, bw, bh))
	return faces


def detect_moles_multiscale(mask_roi, strength=2):
	"""多尺度检测暗色小斑点（痣），返回 (mask, dilate, passes)。"""
	masks = []
	if strength <= 1:
		ks = [3]
		amts = [1.0]
		threshs = [10]
		min_area, max_area = 5, 200
		dilate = 3
		inpaint_passes = 1
	elif strength == 2:
		ks = [3, 5]
		amts = [1.2, 1.6]
		threshs = [8, 12]
		min_area, max_area = 4, 500
		dilate = 5
		inpaint_passes = 2
	else:
		ks = [3, 5, 7]
		amts = [1.4, 1.8, 2.2]
		threshs = [6, 10, 14]
		min_area, max_area = 3, 1000
		dilate = 7
		inpaint_passes = 3

	h, w = mask_roi.shape[:2]
	for ksize, amt, thresh in zip(ks, amts, threshs):
		k = ksize if ksize % 2 == 1 else ksize + 1
		blurred = cv2.GaussianBlur(mask_roi, (k, k), 0)
		sharp = cv2.addWeighted(mask_roi, 1 + amt, blurred, -amt, 0)
		mean = np.mean(sharp)
		_, spot = cv2.threshold(sharp, max(mean - thresh, 0), 255, cv2.THRESH_BINARY_INV)
		spot = cv2.morphologyEx(spot, cv2.MORPH_OPEN, np.ones((3, 3), np.uint8))
		spot = cv2.morphologyEx(spot, cv2.MORPH_CLOSE, np.ones((3, 3), np.uint8))
		num_labels, labels, stats, _ = cv2.connectedComponentsWithStats(spot, connectivity=8)
		cleaned = np.zeros_like(spot)
		for i in range(1, num_labels):
			area = stats[i, cv2.CC_STAT_AREA]
			if min_area <= area <= max_area:
				cleaned[labels == i] = 255
		masks.append(cleaned)

	if len(masks) == 0:
		return np.zeros((h, w), dtype=np.uint8), dilate, inpaint_passes

	combined = masks[0]
	for m in masks[1:]:
		combined = cv2.bitwise_or(combined, m)

	num_labels, labels, stats, _ = cv2.connectedComponentsWithStats(combined, connectivity=8)
	final = np.zeros_like(combined)
	for i in range(1, num_labels):
		area = stats[i, cv2.CC_STAT_AREA]
		if area >= max(2, min_area // 2):
			final[labels == i] = 255

	return final, dilate, inpaint_passes


def remove_moles_with_mediapipe(image_bgr, strength=2, min_conf=0.4, model_selection=1):
	img = image_bgr.copy()
	gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
	faces = detect_faces_mediapipe(img, min_conf=min_conf, model_selection=model_selection)
	if len(faces) == 0:
		print("未检测到人脸，跳过。")
		return img

	for (x, y, w, h) in faces:
		dx, dy = int(w * MARGIN), int(h * MARGIN)
		x0, y0 = max(0, x - dx), max(0, y - dy)
		x1, y1 = min(img.shape[1], x + w + dx), min(img.shape[0], y + h + dy)
		roi_gray = gray[y0:y1, x0:x1]

		spot_mask, dilate, passes = detect_moles_multiscale(roi_gray, strength=strength)
		if np.count_nonzero(spot_mask) == 0:
			continue

		full_mask = np.zeros(gray.shape, dtype=np.uint8)
		kernel = np.ones((dilate, dilate), np.uint8)
		spot_mask_d = cv2.dilate(spot_mask, kernel, iterations=1)
		full_mask[y0:y1, x0:x1] = spot_mask_d

		radii = [3, 5, 8]
		for i in range(passes):
			r = radii[min(i, len(radii) - 1)]
			img = cv2.inpaint(img, full_mask, inpaintRadius=r, flags=cv2.INPAINT_TELEA)

	return img


def main():
	parser = argparse.ArgumentParser(
		description="使用 MediaPipe 人脸检测的祛痣脚本，支持强度调节"
	)
	parser.add_argument("-i", "--input", required=True, help="输入图片路径")
	parser.add_argument("-o", "--output", default="output_mediapipe.png", help="输出图片路径")
	parser.add_argument("-s", "--strength", type=int, choices=[1, 2, 3], default=2, help="祛痣强度：1=弱，2=中，3=强")
	parser.add_argument("--min-conf", type=float, default=0.4, help="人脸检测最小置信度")
	parser.add_argument(
		"--model-selection",
		type=int,
		choices=[0, 1],
		default=1,
		help="MediaPipe FaceDetection 的 model_selection (0:近距离,1:远距离)",
	)
	args = parser.parse_args()

	image = cv2.imread(args.input)
	if image is None:
		print(f"无法读取图片: {args.input}")
		sys.exit(2)

	result = remove_moles_with_mediapipe(
		image,
		strength=args.strength,
		min_conf=args.min_conf,
		model_selection=args.model_selection,
	)
	cv2.imwrite(args.output, result)
	print(f"已保存: {args.output}")


if __name__ == "__main__":
	main()
