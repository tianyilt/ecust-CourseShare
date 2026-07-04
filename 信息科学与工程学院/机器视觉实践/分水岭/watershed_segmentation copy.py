import os
import argparse
import random

import cv2
import numpy as np
import subprocess
import colorsys

# ==================== 可调参数（请在此处调整） ====================
# 算法参数说明见文件末尾注释
# 平滑参数：高斯模糊内核，奇数元组
BLUR_KERNEL = (5, 5)
# 形态学结构元素
MORPH_KERNEL_SHAPE = cv2.MORPH_ELLIPSE
MORPH_KERNEL_SIZE = (3, 3)
# 形态学迭代次数
OPENING_ITER = 2
DILATE_ITER = 2
# 距离变换阈值因子（相对于 dist_transform.max()），用于确定 sure foreground
DIST_THRESH_FACTOR = 0.5
# 距离变换方法和掩模大小
DIST_METHOD = cv2.DIST_L2
DIST_MASK_SIZE = 3
# 最大保留标签数（避免标签数超过 uint8 范围）
MAX_LABELS = 254
# HSV 配色饱和度与亮度（高对比度）
HSV_S = 0.96
HSV_V = 0.96
# 叠加透明度
OVERLAY_ALPHA = 0.45
# MATLAB 可执行文件名（若不在 PATH 中可改为全路径）
MATLAB_EXECUTABLE = 'matlab'
# ================================================================


def make_dirs(path):
    if not os.path.exists(path):
        os.makedirs(path, exist_ok=True)


def watershed_segmentation(img_path, out_dir, debug=False, call_matlab=False):
    make_dirs(out_dir)

    img = cv2.imdecode(np.fromfile(img_path, dtype=np.uint8), cv2.IMREAD_COLOR)
    if img is None:
        raise FileNotFoundError(f"Cannot read image: {img_path}")

    orig = img.copy()
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

    # Smooth to reduce noise
    blur = cv2.GaussianBlur(gray, BLUR_KERNEL, 0)

    # Use Otsu to get a binary image for background/foreground estimation
    _, thresh = cv2.threshold(blur, 200, 255, cv2.THRESH_BINARY + cv2.THRESH_OTSU)

    # Morphological opening to remove small objects
    kernel = cv2.getStructuringElement(MORPH_KERNEL_SHAPE, MORPH_KERNEL_SIZE)
    opening = cv2.morphologyEx(thresh, cv2.MORPH_OPEN, kernel, iterations=OPENING_ITER)

    # Sure background area by dilating
    sure_bg = cv2.dilate(opening, kernel, iterations=DILATE_ITER)

    # Distance transform for sure foreground
    dist_transform = cv2.distanceTransform(opening, DIST_METHOD, DIST_MASK_SIZE)
    # Heuristic threshold: DIST_THRESH_FACTOR * max
    ret, sure_fg = cv2.threshold(dist_transform, DIST_THRESH_FACTOR * dist_transform.max(), 255, 0)
    sure_fg = np.uint8(sure_fg)

    # Unknown region
    unknown = cv2.subtract(sure_bg, sure_fg)

    # Marker labelling
    num_markers, markers = cv2.connectedComponents(sure_fg)
    # Add one to all labels so that sure background is 1 instead of 0
    markers = markers + 1
    # Mark the unknown region with zero
    markers[unknown == 255] = 0

    # Apply watershed
    markers_copy = markers.copy()
    cv2.watershed(img, markers_copy)

    # After watershed, boundary regions are marked with -1
    # Create label image where each region has a positive integer label
    label_image = markers_copy.copy().astype(np.int32)
    # Set boundary to 0 for visualization non-region
    label_image[label_image == -1] = 0

    # Remap labels to consecutive range 0..N-1
    unique = np.unique(label_image)
    unique = unique[unique != 0]
    label_map = {v: i + 1 for i, v in enumerate(unique)}
    remapped = np.zeros_like(label_image, dtype=np.uint8)
    for k, v in label_map.items():
        remapped[label_image == k] = v

    # If there are too many labels (> MAX_LABELS), collapse extra labels into background
    if remapped.max() > MAX_LABELS:
        # keep first MAX_LABELS labels
        thresh_label = MAX_LABELS
        mask = remapped > thresh_label
        remapped[mask] = 0

    # image size (used for marker visualization)
    h, w = remapped.shape

    # Save original and label image
    orig_path = os.path.join(out_dir, "original.png")
    labels_path = os.path.join(out_dir, "labels.png")
    overlay_path = os.path.join(out_dir, "overlay.png")

    # cv2.imwrite cannot handle unicode paths reliably on Windows; use imencode+tofile
    _, buf = cv2.imencode('.png', orig)
    buf.tofile(orig_path)
    _, buf = cv2.imencode('.png', remapped)
    buf.tofile(labels_path)

    # Save intermediate results for visualization in MATLAB
    # thresh, opening, sure_bg, dist_transform (normalized), sure_fg, unknown, markers visualization
    saved = []
    def_save = []
    try:
        _, buf = cv2.imencode('.png', thresh)
        p = os.path.join(out_dir, 'thresh.png')
        buf.tofile(p)
        saved.append(p)
    except Exception:
        pass
    try:
        _, buf = cv2.imencode('.png', opening)
        p = os.path.join(out_dir, 'opening.png')
        buf.tofile(p)
        saved.append(p)
    except Exception:
        pass
    try:
        _, buf = cv2.imencode('.png', sure_bg)
        p = os.path.join(out_dir, 'sure_bg.png')
        buf.tofile(p)
        saved.append(p)
    except Exception:
        pass
    try:
        # normalize distance transform for display
        dt = dist_transform.copy()
        if dt.max() > 0:
            dt_norm = (dt / dt.max() * 255).astype(np.uint8)
        else:
            dt_norm = dt.astype(np.uint8)
        _, buf = cv2.imencode('.png', dt_norm)
        p = os.path.join(out_dir, 'dist_transform.png')
        buf.tofile(p)
        saved.append(p)
    except Exception:
        pass
    try:
        _, buf = cv2.imencode('.png', sure_fg)
        p = os.path.join(out_dir, 'sure_fg.png')
        buf.tofile(p)
        saved.append(p)
    except Exception:
        pass
    try:
        _, buf = cv2.imencode('.png', unknown)
        p = os.path.join(out_dir, 'unknown.png')
        buf.tofile(p)
        saved.append(p)
    except Exception:
        pass

    # markers visualization: map markers_copy labels to colors
    try:
        markers_vis = np.zeros((h, w, 3), dtype=np.uint8)
        unique_markers = np.unique(markers_copy)
        # map -1 to white boundary
        boundary_mask = markers_copy == -1
        markers_vis[boundary_mask] = (255, 255, 255)
        # positive labels
        pos_labels = [m for m in unique_markers if m > 0]
        rng = np.random.default_rng(42)
        label_colors = {m: tuple(int(x) for x in rng.integers(50, 230, size=3)) for m in pos_labels}
        for m, col in label_colors.items():
            markers_vis[markers_copy == m] = col
        p = os.path.join(out_dir, 'markers.png')
        _, buf = cv2.imencode('.png', markers_vis)
        buf.tofile(p)
        saved.append(p)
    except Exception as e:
        if debug:
            print('Failed to save markers.png:', repr(e))
            import traceback
            traceback.print_exc()

    # Some older runs may have produced a misspelled 'unkown.png' - if so, rename it
    try:
        miss = os.path.join(out_dir, 'unkown.png')
        good = os.path.join(out_dir, 'unknown.png')
        if os.path.exists(miss) and not os.path.exists(good):
            os.replace(miss, good)
            saved.append(good)
    except Exception:
        pass

    # Print saved intermediate files when in debug mode
    if debug:
        if saved:
            print('Saved intermediate files:')
            for s in saved:
                print('  ', s)
        else:
            print('No intermediate images were saved.')

    # Create colored overlay with transparency
    h, w = remapped.shape
    # Generate high-contrast colors using evenly spaced HSV hues
    n_labels = int(remapped.max())
    colors = [(0, 0, 0)] * (n_labels + 1)
    if n_labels > 0:
        for i in range(1, n_labels + 1):
            # evenly spaced hue, high saturation and value for contrast
            hue = (i - 1) / float(n_labels)
            r, g, b = colorsys.hsv_to_rgb(hue, HSV_S, HSV_V)
            # convert to 0-255 BGR tuple
            colors[i] = (int(b * 255), int(g * 255), int(r * 255))

    color_seg = np.zeros((h, w, 3), dtype=np.uint8)
    for i in range(1, n_labels + 1):
        color_seg[remapped == i] = colors[i]

    alpha = OVERLAY_ALPHA
    overlay = cv2.addWeighted(orig, 1.0 - alpha, color_seg, alpha, 0)

    _, buf = cv2.imencode('.png', overlay)
    buf.tofile(overlay_path)

    if debug:
        print(f"Saved original -> {orig_path}")
        print(f"Saved labels -> {labels_path}")
        print(f"Saved overlay -> {overlay_path}")

    # Optionally call MATLAB to display results using the existing show_results.m
    if call_matlab:
        try:
            script_dir = os.path.dirname(os.path.abspath(__file__))
            # MATLAB prefers forward slashes in paths on Windows too
            script_dir_matlab = script_dir.replace('\\', '/')
            matlab_cmd = (
                f"try, cd('{script_dir_matlab}'); show_results; catch e, disp(getReport(e)); end"
            )
            if debug:
                print('Calling MATLAB with command:', matlab_cmd)
            # Use Popen so Python does not block; do not use -nodesktop or exit so MATLAB GUI stays open
            try:
                subprocess.Popen([MATLAB_EXECUTABLE, '-nosplash', '-r', matlab_cmd])
            except Exception:
                # fallback to run (non-blocking behavior may differ)
                subprocess.run([MATLAB_EXECUTABLE, '-nosplash', '-r', matlab_cmd], check=False)
        except FileNotFoundError:
            print('MATLAB not found in PATH. Skipping MATLAB display.')
        except Exception as e:
            print('Error when attempting to call MATLAB:', str(e))

    return {
        'original': orig_path,
        'labels': labels_path,
        'overlay': overlay_path,
    }


def main():
    parser = argparse.ArgumentParser(description='Watershed segmentation using gradient + morphology')
    parser.add_argument('image', help='Input image path')
    parser.add_argument('--out', '-o', default='2_output', help='Output directory inside current folder')
    parser.add_argument('--debug', action='store_true')
    parser.add_argument('--matlab', action='store_true', help='If set, call local MATLAB to display results')
    args = parser.parse_args()

    out_dir = args.out
    # If user provided relative path, keep it; if default, put in same folder as script
    if out_dir == '2_output':
        script_dir = os.path.dirname(os.path.abspath(__file__))
        out_dir = os.path.join(script_dir, 'output')

    res = watershed_segmentation(args.image, out_dir, debug=args.debug, call_matlab=args.matlab)
    if args.debug:
        print('Results:', res)


if __name__ == '__main__':
    main()
