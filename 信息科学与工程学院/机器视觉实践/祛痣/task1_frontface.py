import cv2
import numpy as np
from pathlib import Path
import urllib.request
import shutil
import sys

CASCADE_PATH = Path("haarcascade_frontalface_default.xml")  # 确保已下载
MARGIN = 0.25  # 人脸框外扩比例

def ensure_cascade_exists(path: Path):
    """如果本地没有 Haar 模型，尝试从 OpenCV 仓库下载它。"""
    if path.exists():
        return
    url = (
        "https://raw.githubusercontent.com/opencv/opencv/master/data/haarcascades/"
        "haarcascade_frontalface_default.xml"
    )
    print(f"Haar 模型文件 {path} 不存在，尝试从 {url} 下载...")
    try:
        with urllib.request.urlopen(url, timeout=20) as resp, open(path, "wb") as out:
            shutil.copyfileobj(resp, out)
        print("下载完成。")
    except Exception as e:
        print("无法自动下载 Haar 模型：", e)
        print("请手动下载并放置到脚本同目录，或检查网络。")
        raise FileNotFoundError("缺少 Haar 模型文件，且自动下载失败。")

def detect_faces(img_gray):
    # 确保 Haar 模型存在（不存在则尝试下载）
    ensure_cascade_exists(CASCADE_PATH)
    face_cascade = cv2.CascadeClassifier(str(CASCADE_PATH))
    faces = face_cascade.detectMultiScale(img_gray, scaleFactor=1.1, minNeighbors=5, minSize=(80, 80))
    return faces

def detect_moles_multiscale(mask_roi, strength=2):
    """
    多尺度检测暗色小斑点（痣）。
    strength: 1(弱) - 3(强)。强度越高，检测更激进，掩模会更大且允许更大面积。
    返回二值掩模（uint8，0/255）。
    """
    masks = []
    # 根据强度选择参数组
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
        # 保留合适面积的连通域
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

    # 对合并掩模做一次小面积筛除并膨胀（以增加修复覆盖，去除边缘痕迹）
    num_labels, labels, stats, _ = cv2.connectedComponentsWithStats(combined, connectivity=8)
    final = np.zeros_like(combined)
    for i in range(1, num_labels):
        area = stats[i, cv2.CC_STAT_AREA]
        if area >= max(2, min_area // 2):
            final[labels == i] = 255

    # 返回掩模以及用于调用端的膨胀半径和修复次数建议
    return final, dilate, inpaint_passes

def remove_moles(image_bgr, strength=2):
    img = image_bgr.copy()
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    faces = detect_faces(gray)
    if len(faces) == 0:
        print("未检测到人脸，跳过。")
        return img

    for (x, y, w, h) in faces:
        # 外扩人脸区域
        dx, dy = int(w * MARGIN), int(h * MARGIN)
        x0, y0 = max(0, x - dx), max(0, y - dy)
        x1, y1 = min(img.shape[1], x + w + dx), min(img.shape[0], y + h + dy)
        roi_gray = gray[y0:y1, x0:x1]
        roi_color = img[y0:y1, x0:x1]

        spot_mask, dilate, passes = detect_moles_multiscale(roi_gray, strength=strength)

        if np.count_nonzero(spot_mask) == 0:
            continue

        # 将局部 mask 放回全局并膨胀
        full_mask = np.zeros(gray.shape, dtype=np.uint8)
        # 膨胀可以适当扩大修复区域，减少残留痕迹
        kernel = np.ones((dilate, dilate), np.uint8)
        spot_mask_d = cv2.dilate(spot_mask, kernel, iterations=1)
        full_mask[y0:y1, x0:x1] = spot_mask_d

        # 多次修复以增强效果（先小半径再大半径）
        radii = [3, 5, 8]
        for i in range(passes):
            r = radii[min(i, len(radii) - 1)]
            img = cv2.inpaint(img, full_mask, inpaintRadius=r, flags=cv2.INPAINT_TELEA)

    return img

def main():
    import argparse
    parser = argparse.ArgumentParser(description="人脸祛痣（Haar + 多尺度检测 + 修复）。使用 --strength 调整强度(1-3)")
    parser.add_argument("-i", "--input", required=True, help="输入图片路径")
    parser.add_argument("-o", "--output", default="output.png", help="输出图片路径")
    parser.add_argument("-s", "--strength", type=int, choices=[1,2,3], default=2, help="去痣强度：1=弱，2=中，3=强（更激进的掩模与多次修复）")
    args = parser.parse_args()

    image = cv2.imread(args.input)
    if image is None:
        print(f"无法读取图片: {args.input}")
        sys.exit(2)

    result = remove_moles(image, strength=args.strength)
    cv2.imwrite(args.output, result)
    print(f"已保存: {args.output}")

if __name__ == "__main__":
    main()