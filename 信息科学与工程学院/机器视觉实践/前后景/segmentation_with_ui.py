"""
Interactive foreground/background segmentation using matplotlib and OpenCV GrabCut.

Usage:
  - Run: `python segmentation_with_ui.py`
  - Keys:
        - f : switch to foreground drawing mode
        - b : switch to background drawing mode
        - c : run GrabCut with current scribbles
        - r : reset masks and drawings
        - s : save current segmentation to `segmentation_result.png`
        - q or ESC : quit

Mouse:
  - Left button drag to draw strokes (color shows mode: red=fg, blue=bg)

This script loads `lenna.png` from the same folder as the script by default.
"""

import os
import cv2
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.widgets import Slider


IMG_PATH = os.path.abspath("E:\\testField\\lenna.png")
BG_IMG_PATH = os.path.abspath("E:\\testField\\test_bg.jpg")


class InteractiveGrabCut:
    def __init__(self, img_path):
        img_bgr = cv2.imread(img_path)
        if img_bgr is None:
            raise FileNotFoundError(f"Cannot load image: {img_path}")
        self.img = cv2.cvtColor(img_bgr, cv2.COLOR_BGR2RGB)
        self.h, self.w = self.img.shape[:2]

        # mask for grabcut: 0=bg,1=fg,2=pr_bg,3=pr_fg
        self.mask = np.full((self.h, self.w), cv2.GC_PR_BGD, dtype=np.uint8)
        self.fg_strokes = np.zeros((self.h, self.w), dtype=np.uint8)
        self.bg_strokes = np.zeros((self.h, self.w), dtype=np.uint8)

        # drawing state
        self.drawing = False
        self.mode = "fg"  # 'fg' or 'bg'
        self.brush_radius = 7

        # matplotlib figure layout using GridSpec:
        # left: large original+overlay (spans rows 0..2)
        # right: three vertical panels: mask, extracted fg, composite (rows 0,1,2)
        # bottom: slider (row 3, spans both columns)
        self.fig = plt.figure(figsize=(14, 8))
        gs = self.fig.add_gridspec(nrows=4, ncols=2, width_ratios=[2, 1], height_ratios=[1, 1, 1, 0.08], hspace=0.25, wspace=0.12)
        self.ax_img = self.fig.add_subplot(gs[0:3, 0])
        self.ax_mask = self.fig.add_subplot(gs[0, 1])
        self.ax_fg = self.fig.add_subplot(gs[1, 1])
        self.ax_comp = self.fig.add_subplot(gs[2, 1])
        ax_slider = self.fig.add_subplot(gs[3, :])

        self.im_artist = self.ax_img.imshow(self.img)
        self.overlay = np.zeros_like(self.img)
        self.overlay_artist = self.ax_img.imshow(self.overlay, alpha=0.5)

        self.mask_artist = self.ax_mask.imshow(self.get_mask_overlay())

        # placeholder images for extracted fg and composite
        empty = np.zeros_like(self.img)
        self.fg_artist = self.ax_fg.imshow(empty)
        self.comp_artist = self.ax_comp.imshow(empty)

        self.ax_img.set_title("Image (left: draw; f:fg b:bg c:run r:reset s:save q:quit)")
        self.ax_mask.set_title("Segmentation mask")
        self.ax_fg.set_title("Extracted FG (black background)")
        self.ax_comp.set_title("Composite on background image")
        for ax in (self.ax_img, self.ax_mask, self.ax_fg, self.ax_comp):
            ax.axis("off")

        # try load background image (resize to target)
        if os.path.exists(BG_IMG_PATH):
            bg_bgr = cv2.imread(BG_IMG_PATH)
            if bg_bgr is not None:
                bg_rgb = cv2.cvtColor(bg_bgr, cv2.COLOR_BGR2RGB)
                self.bg_img = cv2.resize(bg_rgb, (self.w, self.h))
            else:
                self.bg_img = np.zeros_like(self.img)
        else:
            self.bg_img = np.zeros_like(self.img)

        # slider for feathering (sigma)
        self.feather_sigma = 0.0
        self.slider = Slider(ax_slider, 'Feather', 0.0, 20.0, valinit=self.feather_sigma)
        self.slider.on_changed(self.on_slider_changed)

        # connect events
        self.cid_press = self.fig.canvas.mpl_connect(
            "button_press_event", self.on_press
        )
        self.cid_release = self.fig.canvas.mpl_connect(
            "button_release_event", self.on_release
        )
        self.cid_move = self.fig.canvas.mpl_connect("motion_notify_event", self.on_move)
        self.cid_key = self.fig.canvas.mpl_connect("key_press_event", self.on_key)

    def get_mask_overlay(self):
        # return RGB image visualizing current segmentation mask (fg white, bg black, unknown gray)
        m = np.zeros((self.h, self.w, 3), dtype=np.uint8)
        seg = (self.mask == cv2.GC_FGD) | (self.mask == cv2.GC_PR_FGD)
        m[seg] = [255, 255, 255]
        m[~seg] = [50, 50, 50]
        return m

    def draw_brush(self, x, y):
        # x,y are image coords (float) from matplotlib event
        if x is None or y is None:
            return
        xi = int(round(x))
        yi = int(round(y))
        cv2.circle(
            self.overlay, (xi, yi), self.brush_radius, (0, 0, 0), -1
        )  # unused base
        if self.mode == "fg":
            cv2.circle(self.fg_strokes, (xi, yi), self.brush_radius, 255, -1)
        else:
            cv2.circle(self.bg_strokes, (xi, yi), self.brush_radius, 255, -1)

        # update overlay colors for display (red for fg, blue for bg)
        overlay = np.zeros_like(self.img)
        overlay[self.fg_strokes.astype(bool)] = [255, 0, 0]
        overlay[self.bg_strokes.astype(bool)] = [0, 0, 255]
        self.overlay_artist.set_data(overlay)
        self.fig.canvas.draw_idle()

    def on_press(self, event):
        if event.button != 1:
            return
        if event.inaxes != self.ax_img:
            return
        self.drawing = True
        self.draw_brush(event.xdata, event.ydata)

    def on_release(self, event):
        if event.button != 1:
            return
        self.drawing = False

    def on_move(self, event):
        if not self.drawing:
            return
        if event.inaxes != self.ax_img:
            return
        self.draw_brush(event.xdata, event.ydata)

    def update_mask_from_strokes(self):
        # strokes are 0/255 arrays
        fg = self.fg_strokes.astype(bool)
        bg = self.bg_strokes.astype(bool)
        # Mark definite fg/bg
        self.mask[bg] = cv2.GC_BGD
        self.mask[fg] = cv2.GC_FGD

    def get_extracted_image(self):
        # return image where background is black and foreground kept
        alpha = self._feathered_alpha(self.feather_sigma)
        out = (self.img.astype(np.float32) * alpha[..., None]).astype(np.uint8)
        return out

    def get_composite_on_bg(self):
        # composite extracted fg onto self.bg_img (bg already resized)
        alpha = self._feathered_alpha(self.feather_sigma)
        fg = self.img.astype(np.float32)
        bg = self.bg_img.astype(np.float32)
        comp = (bg * (1.0 - alpha[..., None]) + fg * (alpha[..., None])).astype(np.uint8)
        return comp

    def _feathered_alpha(self, sigma):
        # return float alpha mask in [0,1] with gaussian feathering
        mask_fg = ((self.mask == cv2.GC_FGD) | (self.mask == cv2.GC_PR_FGD)).astype(np.float32)
        if sigma <= 0.5:
            return mask_fg
        # determine kernel size from sigma (approx): k = 2*ceil(3*sigma)+1
        k = max(3, int(2 * int(np.ceil(3 * sigma)) + 1))
        # cv2.GaussianBlur requires kernel size odd
        if k % 2 == 0:
            k += 1
        blurred = cv2.GaussianBlur(mask_fg, (k, k), sigmaX=sigma)
        # normalize to [0,1]
        if blurred.max() > 0:
            blurred = blurred / blurred.max()
        return blurred

    def run_grabcut(self, iter_count=5):
        # prepare mask and models
        self.update_mask_from_strokes()
        bgdModel = np.zeros((1, 65), np.float64)
        fgdModel = np.zeros((1, 65), np.float64)
        # call grabCut with mask initialization
        mask_copy = self.mask.copy()
        cv2.grabCut(
            self.img[:, :, ::-1],
            mask_copy,
            None,
            bgdModel,
            fgdModel,
            iter_count,
            cv2.GC_INIT_WITH_MASK,
        )
        self.mask = mask_copy
        # update displays: mask, extracted fg, composite
        self.mask_artist.set_data(self.get_mask_overlay())
        self.fg_artist.set_data(self.get_extracted_image())
        self.comp_artist.set_data(self.get_composite_on_bg())
        self.fig.canvas.draw_idle()

    def reset(self):
        self.mask[:] = cv2.GC_PR_BGD
        self.fg_strokes.fill(0)
        self.bg_strokes.fill(0)
        self.overlay_artist.set_data(np.zeros_like(self.img))
        self.mask_artist.set_data(self.get_mask_overlay())
        self.fg_artist.set_data(np.zeros_like(self.img))
        self.comp_artist.set_data(np.zeros_like(self.img))
        self.fig.canvas.draw_idle()

    def on_slider_changed(self, val):
        try:
            self.feather_sigma = float(val)
        except Exception:
            self.feather_sigma = 0.0
        # update extracted and composite previews
        self.fg_artist.set_data(self.get_extracted_image())
        self.comp_artist.set_data(self.get_composite_on_bg())
        self.fig.canvas.draw_idle()

    def save_result(self, out_path="segmentation_result.png"):
        # produce RGBA result where bg is transparent
        mask_fg = (self.mask == cv2.GC_FGD) | (self.mask == cv2.GC_PR_FGD)
        out = self.img.copy()
        alpha = mask_fg.astype(np.uint8) * 255
        # save as PNG with alpha
        bgr = cv2.cvtColor(out, cv2.COLOR_RGB2BGRA)
        bgr[:, :, 3] = alpha
        cv2.imwrite(out_path, bgr)
        print(f"Saved segmentation to {out_path}")

    def on_key(self, event):
        key = event.key
        if key is None:
            return
        if key == "f":
            self.mode = "fg"
            print("Mode: foreground")
        elif key == "b":
            self.mode = "bg"
            print("Mode: background")
        elif key == "c":
            print("Running GrabCut...")
            self.run_grabcut()
        elif key == "r":
            print("Resetting...")
            self.reset()
        elif key == "s":
            self.save_result()
        elif key == "q" or key == "escape":
            plt.close(self.fig)

    def show(self):
        plt.show()


def main():
    print("Loading image:", IMG_PATH)
    igc = InteractiveGrabCut(IMG_PATH)
    igc.show()


if __name__ == "__main__":
    main()
