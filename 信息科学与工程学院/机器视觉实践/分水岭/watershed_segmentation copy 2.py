import os
import argparse
import cv2
import numpy as np
import colorsys


def extract_cloud_and_mountain(img,
                               cloud_thresh=200,
                               mountain_thresh=180,
                               close_kernel=(5, 5),
                               open_kernel=(2, 2),
                               close_iters=2,
                               open_iters=1):
    """
    分离云区域与山峰区域（利用亮度差异区分云/天空/山峰）。
    返回：云掩码（cloud_mask）、山峰掩码（mountain_mask）
    """
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

    _, thresh_cloud = cv2.threshold(gray, cloud_thresh, 255, cv2.THRESH_BINARY)
    kernel_large = np.ones(close_kernel, np.uint8)
    kernel_small = np.ones(open_kernel, np.uint8)
    cloud_mask = cv2.morphologyEx(thresh_cloud, cv2.MORPH_CLOSE, kernel_large, iterations=close_iters)
    cloud_mask = cv2.morphologyEx(cloud_mask, cv2.MORPH_OPEN, kernel_small, iterations=open_iters)

    _, thresh_mountain = cv2.threshold(gray, mountain_thresh, 255, cv2.THRESH_BINARY_INV)
    mountain_mask = cv2.bitwise_and(thresh_mountain, cv2.bitwise_not(cloud_mask))
    mountain_mask = cv2.morphologyEx(mountain_mask, cv2.MORPH_CLOSE, kernel_small, iterations=close_iters)
    mountain_mask = cv2.morphologyEx(mountain_mask, cv2.MORPH_OPEN, kernel_small, iterations=open_iters)

    return cloud_mask, mountain_mask


def _remap_positive_labels(markers):
    """Remap watershed labels to consecutive 1..N, keep boundary/background at 0."""
    label_img = markers.copy().astype(np.int32)
    label_img[label_img == -1] = 0
    unique = np.unique(label_img)
    unique = [u for u in unique if u > 1]  # ignore background 1
    remapped = np.zeros_like(label_img, dtype=np.uint8)
    for i, u in enumerate(unique, start=1):
        remapped[label_img == u] = i
    return remapped, remapped.max()


def _colorize_labels(remapped, n_labels, alpha, base_img, hue_shift=0.0, sat=0.96, val=0.96):
    h, w = remapped.shape
    colors = [(0, 0, 0)] * (n_labels + 1)
    for i in range(1, n_labels + 1):
        hue = (hue_shift + (i - 1) / max(n_labels, 1.0)) % 1.0
        r, g, b = colorsys.hsv_to_rgb(hue, sat, val)
        colors[i] = (int(b * 255), int(g * 255), int(r * 255))

    color_seg = np.zeros((h, w, 3), dtype=np.uint8)
    for i in range(1, n_labels + 1):
        color_seg[remapped == i] = colors[i]

    overlay = cv2.addWeighted(base_img, 1.0 - alpha, color_seg, alpha, 0)
    return overlay


def watershed_segment_single_region(mask,
                                    img,
                                    dilate_iters=4,
                                    dist_thresh_ratio=0.4,
                                    dist_kernel=(3, 3)):
    kernel = np.ones(dist_kernel, np.uint8)
    sure_bg = cv2.dilate(mask, kernel, iterations=dilate_iters)

    dist_transform = cv2.distanceTransform(mask, cv2.DIST_L2, 3)
    _, sure_fg = cv2.threshold(dist_transform, dist_thresh_ratio * dist_transform.max(), 255, 0)
    sure_fg = np.uint8(sure_fg)
    unknown = cv2.subtract(sure_bg, sure_fg)

    _, markers = cv2.connectedComponents(sure_fg)
    markers = markers + 1
    markers[unknown == 255] = 0

    markers = cv2.watershed(img, markers)
    return markers


def process_single_image(img_path):
    img = cv2.imread(img_path)
    if img is None:
        print(f"⚠️ 无法读取图片：{img_path}")
        return
    result = img.copy()

    cloud_mask, mountain_mask = extract_cloud_and_mountain(img)
    print("🔍 已分离云区域和山峰区域，开始分别执行分水岭分割...")

    cloud_markers = watershed_segment_single_region(cloud_mask, img)
    mountain_markers = watershed_segment_single_region(mountain_mask, img)

    cloud_remap, cloud_n = _remap_positive_labels(cloud_markers)
    mountain_remap, mountain_n = _remap_positive_labels(mountain_markers)

    print(f"☁️  检测到 {cloud_n} 层不同远近的云")
    result = _colorize_labels(cloud_remap, cloud_n, alpha=0.45, base_img=result, hue_shift=0.0)

    print(f"⛰️  检测到 {mountain_n} 层不同山峰/远近山体")
    result = _colorize_labels(mountain_remap, mountain_n, alpha=0.45, base_img=result, hue_shift=0.5)

    boundary_mask = (cloud_markers == -1) | (mountain_markers == -1)
    result[boundary_mask] = [0, 0, 255]

    dir_name, file_name = os.path.split(img_path)
    base_name, ext = os.path.splitext(file_name)
    save_path = os.path.join(dir_name, f"{base_name}_cloud_mountain_watershed{ext}")
    cv2.imwrite(save_path, result)
    print(f"✅ 云+山峰分层分割结果已保存：{save_path}\n")


def process_folder(folder_path):
    supported_formats = (".jpg", ".jpeg", ".png", ".bmp", ".tiff")
    for file in os.listdir(folder_path):
        if file.lower().endswith(supported_formats):
            img_path = os.path.join(folder_path, file)
            process_single_image(img_path)


def main():
    parser = argparse.ArgumentParser(description='Cloud & mountain watershed segmentation')
    parser.add_argument('path', nargs='?', default='.', help='Image file or folder to process (default: current dir)')
    args = parser.parse_args()

    target = args.path
    if os.path.isfile(target):
        process_single_image(target)
    elif os.path.isdir(target):
        process_folder(target)
    else:
        print(f"路径不存在: {target}")


if __name__ == '__main__':
    main()
