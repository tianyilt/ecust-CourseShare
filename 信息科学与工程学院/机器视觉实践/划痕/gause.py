from pathlib import Path
from typing import Optional

import cv2
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.widgets import Slider, Button
from skimage.restoration import denoise_tv_chambolle
import sys


def _process_image(
    img_bgr: np.ndarray,
    inpaint_radius: int = 3,
    denoise_strength: int = 3,
    apply_feather: bool = True,
    mask_path: Optional[Path] = None,
) -> np.ndarray:
    """
    Detect and repair scratches on a color BGR image, return the repaired BGR image.
    Algorithm steps:
    - Load mask from specified file path
    - Use OpenCV inpaint to repair color image
    - Optional denoising (fast non-local means) for slight smoothing
    """
    if img_bgr is None:
        raise ValueError("Input image is empty")

    # Load mask from file
    if mask_path is None:
        mask_path = Path("E:\\testField\\scratch_mask.png")

    mask = cv2.imread(str(mask_path), cv2.IMREAD_GRAYSCALE)
    if mask is None:
        raise ValueError(f"Cannot read mask from {mask_path}")
        
    # 将mask缩放到与原图相同的尺寸
    if mask.shape[:2] != img_bgr.shape[:2]:
        mask = cv2.resize(mask, (img_bgr.shape[1], img_bgr.shape[0]))

    # 5) Use inpaint to repair color image (Telea is generally fast and effective)
    inpainted = cv2.inpaint(img_bgr, mask, inpaint_radius, cv2.INPAINT_TELEA)

    # 7) Optional denoising: reduce default strength to minimize blur
    if denoise_strength and denoise_strength > 0:
        # Use relatively mild denoising parameters for color and brightness, too high will cause graying and blur
        h = max(1, int(denoise_strength))
        # Recommendation: small h values (e.g., 1-5) for color preservation, too large will blur details
        inpainted = cv2.fastNlMeansDenoisingColored(inpainted, None, h, h, 7, 21)

    # 8) Feather blending (optional): blend repaired area with original using Gaussian feather to avoid gray/color difference edges
    if apply_feather:
        mask_f = mask.astype(np.float32) / 255.0
        # Use moderately large kernel for feathering
        k = 31 if max(img_bgr.shape[:2]) > 300 else 15
        feather = cv2.GaussianBlur(mask_f, (k | 1, k | 1), 0)
        feather = feather[..., None]
        inpainted = (
            inpainted.astype(np.float32) * feather
            + img_bgr.astype(np.float32) * (1.0 - feather)
        ).astype(np.uint8)

    return inpainted


def remove_scratch_gause(
    input: Path, output: Path, inpaint_radius: int = 3, denoise_strength: int = 10
):
    """Read image -> repair -> save. Keep color and use inpaint to recover scratches."""
    image = cv2.imread(str(input), cv2.IMREAD_COLOR)
    if image is None:
        raise FileNotFoundError(f"Cannot read image: {input}")

    repaired = _process_image(
        image, inpaint_radius=inpaint_radius, denoise_strength=denoise_strength
    )

    # Save as jpg/png (keep BGR)
    cv2.imwrite(str(output), repaired)


def show_interactive_ui(image_path: Path, initial_output: Optional[Path] = None):
    """Use matplotlib to show left-right comparison and provide Slider for parameter adjustment and save button."""
    img_bgr = cv2.imread(str(image_path), cv2.IMREAD_COLOR)
    if img_bgr is None:
        raise FileNotFoundError(f"Cannot read image: {image_path}")

    img_rgb = cv2.cvtColor(img_bgr, cv2.COLOR_BGR2RGB)

    # Initial parameters
    init_radius = 3
    init_denoise = 3

    repaired_bgr = _process_image(
        img_bgr, inpaint_radius=init_radius, denoise_strength=init_denoise
    )
    repaired_rgb = cv2.cvtColor(repaired_bgr, cv2.COLOR_BGR2RGB)

    fig, axes = plt.subplots(1, 2, figsize=(12, 6))
    ax_orig, ax_rep = axes
    ax_orig.imshow(img_rgb)
    ax_orig.set_title("Original")
    ax_orig.axis("off")

    img_handle = ax_rep.imshow(repaired_rgb)
    ax_rep.set_title("Repaired")
    ax_rep.axis("off")

    plt.subplots_adjust(left=0.1, bottom=0.25)

    axcolor = "lightgoldenrodyellow"
    ax_radius = plt.axes((0.15, 0.07, 0.7, 0.03), facecolor=axcolor)
    ax_denoise = plt.axes((0.15, 0.02, 0.7, 0.03), facecolor=axcolor)

    s_radius = Slider(
        ax_radius, "Inpaint Radius", 1, 10, valinit=init_radius, valstep=1
    )
    s_denoise = Slider(
        ax_denoise, "Denoise Strength", 0, 30, valinit=init_denoise, valstep=1
    )

    # Show mask or not (toggle button)
    ax_toggle = plt.axes((0.66, 0.85, 0.12, 0.06))
    btn_toggle = Button(ax_toggle, "Show Mask", color="lightgray", hovercolor="0.975")
    show_mask = {"val": False}

    def update(val):
        radius = int(s_radius.val)
        denoise = int(s_denoise.val)
        new_bgr = _process_image(
            img_bgr, inpaint_radius=radius, denoise_strength=denoise
        )
        new_rgb = cv2.cvtColor(new_bgr, cv2.COLOR_BGR2RGB)
        # Update mask when showing mask, otherwise update repaired image
        if show_mask["val"]:
            mask_path = Path("E:\\testField\\scratch_mask.png")
            mask = cv2.imread(str(mask_path), cv2.IMREAD_GRAYSCALE)
            img_handle.set_data(mask)
        else:
            img_handle.set_data(new_rgb)
        fig.canvas.draw_idle()

    s_radius.on_changed(update)
    s_denoise.on_changed(update)

    # Save button
    ax_save = plt.axes((0.81, 0.85, 0.12, 0.06))
    btn_save = Button(ax_save, "Save Result", color="lightblue", hovercolor="0.975")

    def on_save(event):
        radius = int(s_radius.val)
        denoise = int(s_denoise.val)
        out_bgr = _process_image(
            img_bgr, inpaint_radius=radius, denoise_strength=denoise
        )
        out_path = initial_output or (
            image_path.parent / (image_path.stem + "_repaired.png")
        )
        cv2.imwrite(str(out_path), out_bgr)
        print(f"Saved: {out_path}")

    btn_save.on_clicked(on_save)

    def on_toggle(event):
        # Toggle between repaired image and mask
        show_mask["val"] = not show_mask["val"]
        if show_mask["val"]:
            btn_toggle.label.set_text("Show Repaired")
            mask_path = Path("E:\\testField\\scratch_mask.png")
            mask = cv2.imread(str(mask_path), cv2.IMREAD_GRAYSCALE)
            img_handle.set_data(mask)
            ax_rep.set_title("Mask (white=detection)")
        else:
            btn_toggle.label.set_text("Show Mask")
            # Refresh to repaired image
            denoise = int(s_denoise.val)
            radius = int(s_radius.val)
            new_bgr = _process_image(
                img_bgr, inpaint_radius=radius, denoise_strength=denoise
            )
            img_handle.set_data(cv2.cvtColor(new_bgr, cv2.COLOR_BGR2RGB))
            ax_rep.set_title("Repaired")
        fig.canvas.draw_idle()

    btn_toggle.on_clicked(on_toggle)

    plt.show()


def main():
    # 支持命令行：python gause.py <input> [output]
    if len(sys.argv) >= 2:
        input_path = Path(sys.argv[1])
    else:
        # 默认示例路径（用户请自行改为有效路径）
        input_path = Path(r"E:\testField\scratch_pic.png")

    output_path = None
    if len(sys.argv) >= 3:
        output_path = Path(sys.argv[2])

    # 打开交互界面，用户可调参数并保存
    show_interactive_ui(input_path, initial_output=output_path)


if __name__ == "__main__":
    main()
