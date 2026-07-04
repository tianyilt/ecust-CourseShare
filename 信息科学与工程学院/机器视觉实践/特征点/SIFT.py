"""
SIFT 特征检测与匹配 可视化脚本

说明:
- 使用 OpenCV 的 SIFT 实现特征点检测与描述子计算
- 使用 BFMatcher + Lowe Ratio Test 进行匹配
- 使用 matplotlib 将匹配结果可视化: 在两图并排的画布上用线连接匹配点

使用方法 (在文件头部配置参数或命令行传入图片路径):
        python sift.py --img1 path/to/1.jpg --img2 path/to/2.jpg

依赖:
        pip install opencv-contrib-python matplotlib numpy

所有可配置参数都放在文件顶部，便于修改。
中文注释用于说明每一步的作用。
"""

import argparse
import os
import sys
import cv2
import numpy as np
import matplotlib.pyplot as plt

# ==================== 配置区（所有参数写在这里） ====================
# 图片路径（若使用命令行传参，会覆盖这里的设置）
IMG1_PATH = "E:\\testField\\road_view\\0000000000.png"  # 示例: r"d:/path/to/image1.jpg"
IMG2_PATH = "E:\\testField\\road_view\\0000000003.png"  # 示例: r"d:/path/to/image2.jpg"

# SIFT 参数
SIFT_NFEATURES = 0  # 检测到的特征点上限，0 表示使用默认
SIFT_NOCTAVE_LAYERS = 3
SIFT_CONTRAST_THRESHOLD = 0.04
SIFT_EDGE_THRESHOLD = 10
SIFT_SIGMA = 1.6

# 匹配与绘图参数
RATIO_TEST = 0.8  # Lowe ratio 测试阈值
TOP_K_MATCHES = 100  # 最多绘制的匹配对数量
DRAW_KEYPOINTS = True  # 是否在图上绘制检测到的关键点
SAVE_RESULT = True  # 是否保存可视化结果到文件
OUTPUT_PATH = os.path.join(".", "sift_matches.png")
FIGSIZE = (14, 8)

# ==================================================================


def create_sift():
    """创建 SIFT 特征提取器，兼容不同 OpenCV 版本"""
    try:
        sift = cv2.SIFT_create(
            SIFT_NFEATURES,
            SIFT_NOCTAVE_LAYERS,
            SIFT_CONTRAST_THRESHOLD,
            SIFT_EDGE_THRESHOLD,
            SIFT_SIGMA,
        )
    except Exception:
        # fallback for older OpenCV with xfeatures2d
        sift = cv2.xfeatures2d.SIFT_create(
            SIFT_NFEATURES,
            SIFT_NOCTAVE_LAYERS,
            SIFT_CONTRAST_THRESHOLD,
            SIFT_EDGE_THRESHOLD,
            SIFT_SIGMA,
        )
    return sift


def load_image(path):
    """加载图片，若为灰度则转为 BGR 三通道以便显示和绘制颜色标记"""
    img = cv2.imread(path, cv2.IMREAD_COLOR)
    if img is None:
        raise FileNotFoundError(f"无法加载图片: {path}")
    return img


def detect_and_compute(detector, img):
    """检测关键点并计算描述子。输入 BGR 图，返回 keypoints 和 descriptors"""
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    kp, des = detector.detectAndCompute(gray, None)
    return kp, des


def match_descriptors(des1, des2, ratio=0.75):
    """使用 BFMatcher + Lowe ratio test 进行描述子匹配，返回通过比率测试的 matches 列表"""
    # SIFT 描述子为浮点型，使用 L2 距离
    bf = cv2.BFMatcher(cv2.NORM_L2, crossCheck=False)
    raw_matches = bf.knnMatch(des1, des2, k=2)
    good = []
    for m_n in raw_matches:
        if len(m_n) != 2:
            continue
        m, n = m_n
        if m.distance < ratio * n.distance:
            good.append(m)
    return good


def draw_matches_matplotlib(
    img1,
    kp1,
    img2,
    kp2,
    matches,
    top_k=100,
    draw_kp=True,
    figsize=(14, 8),
    output_path=None,
):
    """在 matplotlib 中绘制匹配：两图上下排列，匹配点用线连接。

    参数:
            img1, img2: BGR 格式的 numpy 数组
            kp1, kp2: keypoints 列表
            matches: DMatch 列表（已过滤、已排序）
            top_k: 绘制前 K 个匹配
            draw_kp: 是否在图上标注关键点圆点
            output_path: 若不为 None，则保存结果图像
    """
    # 限制绘制数量
    matches = sorted(matches, key=lambda x: x.distance)
    matches = matches[:top_k]

    # 将 BGR 转为 RGB 以便 matplotlib 显示
    img1_rgb = cv2.cvtColor(img1, cv2.COLOR_BGR2RGB)
    img2_rgb = cv2.cvtColor(img2, cv2.COLOR_BGR2RGB)

    h1, w1 = img1.shape[:2]
    h2, w2 = img2.shape[:2]
    out_h = h1 + h2
    out_w = max(w1, w2)

    # 创建合并画布
    canvas = np.zeros((out_h, out_w, 3), dtype=np.uint8)
    canvas[:h1, :w1, :] = img1_rgb
    canvas[h1:h1 + h2, :w2, :] = img2_rgb

    plt.figure(figsize=figsize)
    plt.imshow(canvas)
    plt.axis("off")

    # 在拼接图上绘制关键点和连接线
    for match in matches:
        pt1 = tuple(np.round(kp1[match.queryIdx].pt).astype(int))
        pt2 = tuple(np.round(kp2[match.trainIdx].pt).astype(int))
        pt2_shift = (pt2[0], pt2[1] + h1)  # 第二张图在画布上的偏移

        # 绘制关键点
        if draw_kp:
            plt.scatter([pt1[0]], [pt1[1]], s=30, c="r", marker="o")
            plt.scatter([pt2_shift[0]], [pt2_shift[1]], s=30, c="y", marker="o")

        # 绘制连接线，颜色按距离变化（短线更绿）
        # 归一化距离到 [0,1]
        # 使用 match.distance 来表示匹配质量
        # 如果距离较小，颜色更绿；距离大则偏红
        d = match.distance
        # 距离归一化（用简单剪裁避免除零）
        norm = max(1.0, d)
        color = (1.0 - min(1.0, norm / 400.0), min(1.0, norm / 400.0), 0.0)
        plt.plot(
            [pt1[0], pt2_shift[0]], [pt1[1], pt2_shift[1]], color=color, linewidth=0.8
        )

    plt.tight_layout()
    if output_path:
        plt.savefig(output_path, bbox_inches="tight", dpi=200)
    plt.show()


def main(argv=None):
    parser = argparse.ArgumentParser(description="SIFT 特征检测与匹配可视化")
    parser.add_argument("--img1", type=str, default=IMG1_PATH, help="第一张图片路径")
    parser.add_argument("--img2", type=str, default=IMG2_PATH, help="第二张图片路径")
    parser.add_argument(
        "--topk", type=int, default=TOP_K_MATCHES, help="绘制匹配对数量"
    )
    parser.add_argument(
        "--ratio", type=float, default=RATIO_TEST, help="Lowe ratio 参数"
    )
    parser.add_argument(
        "--out", type=str, default=OUTPUT_PATH, help="保存结果的路径（可选）"
    )
    args = parser.parse_args(argv)

    if not args.img1 or not args.img2:
        print(
            "请在文件顶部配置 IMG1_PATH 和 IMG2_PATH，或通过命令行传入 --img1 和 --img2"
        )
        return

    img1_path = args.img1
    img2_path = args.img2

    # 加载图片并检查
    img1 = load_image(img1_path)
    img2 = load_image(img2_path)

    # 创建 SIFT 检测器
    sift = create_sift()

    # 检测并计算描述子
    kp1, des1 = detect_and_compute(sift, img1)
    kp2, des2 = detect_and_compute(sift, img2)

    if des1 is None or des2 is None or len(kp1) == 0 or len(kp2) == 0:
        print("未检测到足够的关键点或描述子，无法匹配。")
        return

    # 匹配描述子
    matches = match_descriptors(des1, des2, ratio=args.ratio)
    print(
        f"检测到关键点: img1={len(kp1)}, img2={len(kp2)}；通过 ratio 测试的匹配数 = {len(matches)}"
    )

    # 可视化匹配结果
    out_path = args.out if SAVE_RESULT else None
    if SAVE_RESULT and out_path:
        # 确保输出目录存在
        os.makedirs(os.path.dirname(out_path), exist_ok=True)

    draw_matches_matplotlib(
        img1,
        kp1,
        img2,
        kp2,
        matches,
        top_k=args.topk,
        draw_kp=DRAW_KEYPOINTS,
        figsize=FIGSIZE,
        output_path=out_path,
    )


if __name__ == "__main__":
    main()
