import os
import cv2
import dlib
import numpy as np

# 可调参数
L_THRESH = 135  # 初始 L 阈值
A_MAX = 150  # A 通道上限（排除偏红）
B_MAX = 150  # B 通道上限（排除过蓝/非黄）
S_MAX = 110  # HSV S 通道上限（牙齿通常饱和度较低）
MIN_AREA = 150  # 保留连通域最小面积
DILATE_K = 7  # 掩码膨胀大小
GAUSS_BLUR = 15  # alpha 高斯模糊核，越大过渡越平滑
GAIN = 1.30  # L 通道增强倍数
ADD = 25  # L 通道增强偏移
B_REDUCE = 0.82  # B 通道缩放（减少黄度）
DEBUG = False  # 若为 True 会保存中间掩码到当前目录方便调试


def load_predictor():
    # try common locations
    here = os.path.dirname(__file__)
    cand = os.path.join("E:\\testField", "shape_predictor_81_face_landmarks.dat")
    cand = os.path.abspath(cand)
    if os.path.exists(cand):
        return cand
    cand2 = os.path.join(here, "models", "shape_predictor_81_face_landmarks.dat")
    if os.path.exists(cand2):
        return cand2
    # fallback: raise to let user know
    raise FileNotFoundError(
        "shape_predictor_81_face_landmarks.dat not found. Place it in magic_face-master/models or 4牙齿/models"
    )


def get_landmarks(img, predictor_path):
    detector = dlib.get_frontal_face_detector()
    predictor = dlib.shape_predictor(predictor_path)
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    rects = detector(gray, 1)
    if len(rects) == 0:
        return None
    shape = predictor(gray, rects[0])
    coords = np.zeros((68, 2), dtype=int)
    for i in range(68):
        coords[i] = (shape.part(i).x, shape.part(i).y)
    return coords


def inner_mouth_mask_from_landmarks(img, landmarks, dilate_px=DILATE_K):
    h, w = img.shape[:2]
    inner = landmarks[60:68]  # 68-point dlib inner lip
    hull = cv2.convexHull(inner)
    mask = np.zeros((h, w), dtype=np.uint8)
    cv2.fillConvexPoly(mask, hull, 255)
    if dilate_px > 0:
        k = cv2.getStructuringElement(cv2.MORPH_ELLIPSE, (dilate_px, dilate_px))
        mask = cv2.dilate(mask, k, iterations=1)
    return mask


def compute_teeth_mask(img, inner_mask):
    # color-based candidate in LAB + HSV
    lab = cv2.cvtColor(img, cv2.COLOR_BGR2LAB)
    L = lab[:, :, 0]
    A = lab[:, :, 1]
    B = lab[:, :, 2]

    hsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)
    S = hsv[:, :, 1]

    mL = L > L_THRESH
    mA = A < A_MAX
    mB = B < B_MAX
    mS = S < S_MAX

    cand = (mL & mA & mB & mS).astype(np.uint8) * 255
    cand = cv2.bitwise_and(cand, inner_mask)

    # morphology clean
    k1 = cv2.getStructuringElement(cv2.MORPH_ELLIPSE, (3, 3))
    cand = cv2.morphologyEx(cand, cv2.MORPH_OPEN, k1, iterations=1)
    cand = cv2.morphologyEx(cand, cv2.MORPH_CLOSE, k1, iterations=2)

    # keep sufficiently large components
    num, labels, stats, _ = cv2.connectedComponentsWithStats(cand, connectivity=8)
    out = np.zeros_like(cand)
    for i in range(1, num):
        if stats[i, cv2.CC_STAT_AREA] >= MIN_AREA:
            out[labels == i] = 255

    # If still empty, relax thresholds once
    if out.sum() == 0:
        # relax L threshold
        mL2 = L > (L_THRESH - 10)
        cand2 = (mL2 & mA & mS).astype(np.uint8) * 255
        cand2 = cv2.bitwise_and(cand2, inner_mask)
        cand2 = cv2.morphologyEx(cand2, cv2.MORPH_OPEN, k1, iterations=1)
        cand2 = cv2.morphologyEx(cand2, cv2.MORPH_CLOSE, k1, iterations=2)
        num2, labels2, stats2, _ = cv2.connectedComponentsWithStats(
            cand2, connectivity=8
        )
        for i in range(1, num2):
            if stats2[i, cv2.CC_STAT_AREA] >= (MIN_AREA // 2):
                out[labels2 == i] = 255

    return out


def smooth_alpha_from_mask(mask, blur_kernel=GAUSS_BLUR):
    # mask: uint8 0/255 -> float alpha 0..1
    a = mask.astype(np.float32) / 255.0
    k = blur_kernel if blur_kernel % 2 == 1 else blur_kernel + 1
    a = cv2.GaussianBlur(a, (k, k), 0)
    a = np.clip(a, 0.0, 1.0)
    return a


def enhance_teeth_lab(img, alpha):
    # img: BGR uint8, alpha: float 0..1 same HxW
    lab = cv2.cvtColor(img, cv2.COLOR_BGR2LAB).astype(np.float32)
    L = lab[:, :, 0]
    A = lab[:, :, 1]
    B = lab[:, :, 2]

    # create boosted versions
    L_boost = np.clip(L * GAIN + ADD, 0, 255)
    B_boost = np.clip(B * B_REDUCE, 0, 255)

    # blend using alpha
    L_new = (1.0 - alpha) * L + alpha * L_boost
    B_new = (1.0 - alpha) * B + alpha * B_boost

    lab[:, :, 0] = L_new
    lab[:, :, 2] = B_new

    out = cv2.cvtColor(lab.astype(np.uint8), cv2.COLOR_LAB2BGR)
    return out


def process_image(input_path, output_path, debug=DEBUG):
    predictor_path = load_predictor()
    img = cv2.imread(input_path)
    if img is None:
        raise FileNotFoundError(f"Image not found: {input_path}")

    landmarks = get_landmarks(img, predictor_path)
    if landmarks is None:
        print("No face detected; saving original image.")
        cv2.imwrite(output_path, img)
        return

    inner_mask = inner_mouth_mask_from_landmarks(img, landmarks, dilate_px=DILATE_K)
    teeth_mask = compute_teeth_mask(img, inner_mask)

    if teeth_mask.sum() == 0:
        print("未检测到牙齿候选（掩码为空），建议增大 L 阈值放宽或查看 debug 图像。")
        # 写入原图以示无处理
        cv2.imwrite(output_path, img)
        return

    alpha = smooth_alpha_from_mask(teeth_mask, blur_kernel=GAUSS_BLUR)
    enhanced = enhance_teeth_lab(img, alpha)

    # 最终按 alpha 混合
    alpha_3 = np.repeat(alpha[:, :, None], 3, axis=2)
    result = (
        enhanced.astype(np.float32) * alpha_3 + img.astype(np.float32) * (1 - alpha_3)
    ).astype(np.uint8)

    # ensure output directory exists
    out_dir = os.path.dirname(output_path) or os.getcwd()
    os.makedirs(out_dir, exist_ok=True)

    # save result image
    cv2.imwrite(output_path, result)

    # always save masks and intermediate images to output directory
    try:
        cv2.imwrite(os.path.join(out_dir, "inner_mask.png"), inner_mask)
        cv2.imwrite(os.path.join(out_dir, "teeth_mask.png"), teeth_mask)
        cv2.imwrite(os.path.join(out_dir, "alpha.png"), (alpha * 255).astype(np.uint8))
        cv2.imwrite(os.path.join(out_dir, "enhanced.png"), enhanced)
    except Exception:
        # if any mask save fails, continue silently
        pass

    if debug:
        # also write debug files with explicit names
        cv2.imwrite(os.path.join(out_dir, "debug_inner_mask.png"), inner_mask)
        cv2.imwrite(os.path.join(out_dir, "debug_teeth_mask.png"), teeth_mask)
        cv2.imwrite(os.path.join(out_dir, "debug_alpha_dbg.png"), (alpha * 255).astype(np.uint8))
        cv2.imwrite(os.path.join(out_dir, "debug_enhanced_dbg.png"), enhanced)

    print(f"Wrote: {output_path}")


if __name__ == "__main__":
    # 输入目录与输出目录（输出目录为用户要求的 teeth_out）
    base_input = "E:\\testField"
    out_dir = "E:\\testField\\teeth_out"
    src = os.path.join(base_input, "teeth_test.jpg")
    dst = os.path.join(out_dir, "test_bright.jpg")
    process_image(src, dst, debug=False)
