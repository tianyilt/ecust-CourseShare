import os
import cv2
import numpy as np
import argparse
from PIL import Image, ImageDraw, ImageFont


def ensure_divisible_by_block(img, block=8):
    h, w = img.shape[:2]
    nh = h - (h % block)
    nw = w - (w % block)
    if nh != h or nw != w:
        img = img[0:nh, 0:nw]
    return img


def make_text_mask(text, shape, font_scale=4, thickness=8, font_path=None, fill_width_ratio=0.9):
    h, w = shape
    # Try to render Chinese text using Pillow (supports TrueType fonts)
    try:
        img_pil = Image.new('L', (w, h), 0)
        draw = ImageDraw.Draw(img_pil)
        # choose font path: priority argument -> found system font -> None
        if font_path is None:
            font_path = find_chinese_font()

        # binary search for maximum font size that fits target width
        target_w = int(w * float(fill_width_ratio))
        low, high = 1, max(8, w)
        best_size = 1
        while low <= high:
            mid = (low + high) // 2
            try:
                if font_path and os.path.exists(font_path):
                    font_try = ImageFont.truetype(font_path, mid)
                else:
                    font_try = ImageFont.load_default()
                try:
                    bbox = draw.textbbox((0, 0), text, font=font_try)
                    tw = bbox[2] - bbox[0]
                except Exception:
                    tw, _ = draw.textsize(text, font=font_try)
            except Exception:
                tw = w + 1
            if tw <= target_w:
                best_size = mid
                low = mid + 1
            else:
                high = mid - 1

        # create final font with best_size
        if font_path and os.path.exists(font_path):
            try:
                font = ImageFont.truetype(font_path, best_size)
            except Exception:
                font = ImageFont.load_default()
        else:
            font = ImageFont.load_default()

        try:
            bbox = draw.textbbox((0, 0), text, font=font)
            tw = bbox[2] - bbox[0]
            th = bbox[3] - bbox[1]
        except Exception:
            tw, th = draw.textsize(text, font=font)

        x = max((w - tw) // 2, 0)
        y = max((h - th) // 2, 0)
        draw.text((x, y), text, fill=255, font=font)
        mask = np.array(img_pil, dtype=np.uint8)
        _, mask = cv2.threshold(mask, 127, 1, cv2.THRESH_BINARY)
        return mask
    except Exception:
        # fallback to OpenCV (may not support Chinese)
        mask = np.zeros((h, w), dtype=np.uint8)
        font = cv2.FONT_HERSHEY_SIMPLEX
        (tw, th), _ = cv2.getTextSize(text, font, font_scale, thickness)
        x = max((w - tw) // 2, 0)
        y = max((h + th) // 2, th)
        cv2.putText(mask, text, (x, y), font, font_scale, (255,), thickness, cv2.LINE_AA)
        _, mask = cv2.threshold(mask, 127, 1, cv2.THRESH_BINARY)
        return mask


def find_chinese_font():
    """Search for common Chinese fonts in Windows Fonts folder and return first match."""
    fonts_dir = os.path.join(os.environ.get('WINDIR', 'C:\\Windows'), 'Fonts')
    if not os.path.isdir(fonts_dir):
        return None
    candidates = ['msyh', 'msyhl', 'simhei', 'simsun', 'kaiu', 'fang', 'ntailu', 'youyuan', 'NotoSansCJK']
    for fn in os.listdir(fonts_dir):
        lname = fn.lower()
        for cand in candidates:
            if cand in lname:
                return os.path.join(fonts_dir, fn)
    return None


def block_dct(mat, block=8):
    h, w = mat.shape
    dct_mat = np.zeros_like(mat, dtype=np.float32)
    for i in range(0, h, block):
        for j in range(0, w, block):
            block_img = mat[i:i+block, j:j+block].astype(np.float32)
            dct_block = cv2.dct(block_img)
            dct_mat[i:i+block, j:j+block] = dct_block
    return dct_mat


def block_idct(dct_mat, block=8):
    h, w = dct_mat.shape
    img = np.zeros_like(dct_mat, dtype=np.float32)
    for i in range(0, h, block):
        for j in range(0, w, block):
            dct_block = dct_mat[i:i+block, j:j+block]
            block_img = cv2.idct(dct_block)
            img[i:i+block, j:j+block] = block_img
    return img


def embed_watermark(y_channel, watermark_mask, alpha=20, block=8):
    """Embed watermark into the Y (luminance) channel (uint8) and return modified Y channel."""
    cover = y_channel.astype(np.float32)
    h, w = cover.shape
    # watermark_mask should be binary (0/1) same size as image
    wm = cv2.resize(watermark_mask.astype(np.uint8), (w, h), interpolation=cv2.INTER_NEAREST)

    dct = np.zeros_like(cover, dtype=np.float32)
    # process blockwise
    for i in range(0, h, block):
        for j in range(0, w, block):
            blk = cover[i:i+block, j:j+block]
            D = cv2.dct(blk)
            # choose two mid-frequency coefficients
            (p1, p2) = ((2, 3), (3, 2))
            c1 = D[p1]
            c2 = D[p2]
            # sample watermark bit at block center
            bi = min(i + block // 2, h - 1)
            bj = min(j + block // 2, w - 1)
            bit = int(wm[bi, bj] > 0)
            if bit == 1:
                if c1 - c2 <= alpha:
                    D[p1] = c2 + alpha
            else:
                if c2 - c1 <= alpha:
                    D[p2] = c1 + alpha
            dct[i:i+block, j:j+block] = D

    watermarked = block_idct(dct, block=block)
    watermarked = np.clip(watermarked, 0, 255).astype(np.uint8)
    return watermarked


def extract_watermark(img, block=8):
    """Extract watermark from image. If input is color, convert to Y channel first."""
    if img.ndim == 3 and img.shape[2] == 3:
        ycb = cv2.cvtColor(img, cv2.COLOR_BGR2YCrCb)
        y = ycb[:, :, 0]
    else:
        y = img
    imgf = y.astype(np.float32)
    h, w = imgf.shape
    wm_bits = np.zeros((h // block, w // block), dtype=np.uint8)
    for bi, i in enumerate(range(0, h, block)):
        for bj, j in enumerate(range(0, w, block)):
            blk = imgf[i:i+block, j:j+block]
            D = cv2.dct(blk)
            (p1, p2) = ((2, 3), (3, 2))
            c1 = D[p1]
            c2 = D[p2]
            wm_bits[bi, bj] = 1 if (c1 - c2) > 0 else 0
    # upsample the bit mask to image size
    wm_up = cv2.resize(wm_bits * 255, (w, h), interpolation=cv2.INTER_NEAREST)
    return wm_up


def add_gaussian_noise(img, sigma=6):
    noise = np.random.normal(0, sigma, img.shape).astype(np.float32)
    out = img.astype(np.float32) + noise
    out = np.clip(out, 0, 255).astype(np.uint8)
    return out


def rotate_scale(img, angle=10, scale=1.0):
    h, w = img.shape[:2]
    center = (w // 2, h // 2)
    M = cv2.getRotationMatrix2D(center, angle, scale)
    out = cv2.warpAffine(img, M, (w, h), flags=cv2.INTER_LINEAR, borderMode=cv2.BORDER_REFLECT)
    return out


def parse_args():
    p = argparse.ArgumentParser()
    p.add_argument('--input', '-i', required=True, help='Path to cover image')
    p.add_argument('--output', '-o', default='outputs', help='Output folder')
    p.add_argument('--text', '-t', default='张鸿尧', help='Watermark text (default: 张鸿尧)')
    p.add_argument('--font', '-f', default=None, help='Path to TTF/OTF font to use for rendering text (optional)')
    p.add_argument('--block', type=int, default=8, help='DCT block size (default 8)')
    p.add_argument('--alpha', type=float, default=20.0, help='Embedding strength alpha (default 20)')
    p.add_argument('--noise-sigma', type=float, default=6.0, help='Gaussian noise sigma for perturbation (default 6)')
    return p.parse_args()


def main():
    args = parse_args()
    inp = args.input
    outdir = args.output
    os.makedirs(outdir, exist_ok=True)

    img = cv2.imdecode(np.fromfile(inp, dtype=np.uint8), cv2.IMREAD_COLOR)
    if img is None:
        raise FileNotFoundError(f'Cannot read input image: {inp}')

    img = ensure_divisible_by_block(img, args.block)

    # convert to YCrCb and split channels (preserve color)
    ycrcb = cv2.cvtColor(img, cv2.COLOR_BGR2YCrCb)
    y, cr, cb = cv2.split(ycrcb)

    # create watermark mask (same size as Y)
    fs = max(2, min(img.shape[1], img.shape[0]) // 200)
    mask = make_text_mask(args.text, (y.shape[0], y.shape[1]), font_scale=fs, thickness=fs+2, font_path=args.font, fill_width_ratio=0.95)

    wm_mask_vis = (mask * 255).astype(np.uint8)
    cv2.imwrite(os.path.join(outdir, 'watermark_mask.png'), wm_mask_vis)

    # embed only in Y channel
    watermarked_y = embed_watermark(y, mask, alpha=args.alpha, block=args.block)

    # reconstruct color image preserving Cr/Cb
    ycrcb_w = cv2.merge([watermarked_y, cr, cb])
    watermarked_bgr = cv2.cvtColor(ycrcb_w, cv2.COLOR_YCrCb2BGR)

    cv2.imwrite(os.path.join(outdir, 'original.png'), img)
    cv2.imwrite(os.path.join(outdir, 'watermarked.png'), watermarked_bgr)

    # apply perturbations (on color image)
    perturbed = add_gaussian_noise(watermarked_bgr, sigma=args.noise_sigma)
    perturbed = rotate_scale(perturbed, angle=5, scale=0.98)
    cv2.imwrite(os.path.join(outdir, 'perturbed.png'), perturbed)

    # extract watermark from watermarked and perturbed (operate on color images)
    extracted_from_watermarked = extract_watermark(watermarked_bgr, block=args.block)
    extracted_from_perturbed = extract_watermark(perturbed, block=args.block)
    cv2.imwrite(os.path.join(outdir, 'extracted_from_watermarked.png'), extracted_from_watermarked)
    cv2.imwrite(os.path.join(outdir, 'extracted_from_perturbed.png'), extracted_from_perturbed)

    print('Saved outputs to', outdir)


if __name__ == '__main__':
    main()
