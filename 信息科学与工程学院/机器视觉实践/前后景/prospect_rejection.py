
try:
	import matplotlib.pyplot as plt
	from matplotlib.widgets import Slider, Button, RadioButtons
except Exception:
	plt = None
	Slider = None
	Button = None
	RadioButtons = None

import os
import sys
import cv2
import numpy as np


# ----------------------------
# 可调主要参数（放在文件顶部，便于修改）
# ----------------------------
# 原图文件名（相对本脚本目录）。如果文件名不同请修改。
SRC_FILENAME = 'lenna.png'              # 推荐: 'lenna.png' 或 'Lenna.png'

# 输出文件前缀（会生成 <PREFIX>_foreground_on_black.png 等）
OUTPUT_PREFIX = 'lenna'                 # 推荐: 依据图片命名

# 是否启用 Matplotlib 交互界面（滑动条）
# 推荐: True 用于交互调参；False 仅输出静态结果
USE_MATPLOTLIB_UI = True

# GrabCut 参数
GRABCUT_ITER = 1                        # 推荐范围: 1 - 10（默认 5）
RECT_MARGIN = 1                      # 推荐范围: 0 - 50（越大包含更多背景）

# 掩码精修（形态学）
MORPH_KERNEL_SIZE = 3                   # 推荐范围: 1 - 11（奇数优先）。越大能去更多噪点，但会侵蚀细节
MORPH_OPEN_ITER = 2                     # 推荐范围: 0 - 5
MORPH_DILATE_ITER = 1                   # 推荐范围: 0 - 5

# 羽化（高斯模糊）
BLUR_SIZE = 21                          # 推荐范围: 3 - 101（必须为奇数）。越大边缘越柔和

# 是否保存调试用的掩码图
SAVE_DEBUG_MASKS = True                 # True/False
# 前景预扩展（在精修前对初始前景掩码做膨胀，以包含更多区域，例如肩膀）
# 推荐范围: 0 - 100（像素）
FG_EXPAND_PIXELS = 0                    # 若肩膀被裁剪，可以增大此值
# ----------------------------


def ensure_cv2():
	try:
		_ = cv2.__version__
	except Exception as e:
		print('OpenCV 未安装或无法导入：', e)
		sys.exit(1)


def load_image(path):
	if not os.path.exists(path):
		print('未找到图片:', path)
		sys.exit(1)
	img = cv2.imdecode(np.fromfile(path, dtype=np.uint8), cv2.IMREAD_UNCHANGED)
	if img is None:
		print('无法读取图片:', path)
		sys.exit(1)
	return img


def save_image(path, img):
	# 使用 imencode+tofile 以支持带中文路径/Windows
	ext = os.path.splitext(path)[1]
	success, enc = cv2.imencode(ext, img)
	if not success:
		raise IOError('保存图片失败: ' + path)
	with open(path, 'wb') as f:
		f.write(enc.tobytes())


def grabcut_foreground(img, iter_count=GRABCUT_ITER, rect_margin=RECT_MARGIN):
	h, w = img.shape[:2]
	mask = np.zeros((h, w), np.uint8)
	rect = (rect_margin, rect_margin, max(1, w - 2 * rect_margin), max(1, h - 2 * rect_margin))
	bgdModel = np.zeros((1, 65), np.float64)
	fgdModel = np.zeros((1, 65), np.float64)
	cv2.grabCut(img, mask, rect, bgdModel, fgdModel, iter_count, cv2.GC_INIT_WITH_RECT)
	# 前景掩码（1 表示前景）
	fg_mask = np.where((mask == cv2.GC_FGD) | (mask == cv2.GC_PR_FGD), 1, 0).astype('uint8')
	return fg_mask


def mask_from_otsu(img):
	"""基于 Otsu 的全局阈值分割，返回 0/1 掩码"""
	gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
	blur = cv2.GaussianBlur(gray, (5, 5), 0)
	_, th = cv2.threshold(blur, 0, 255, cv2.THRESH_BINARY + cv2.THRESH_OTSU)
	mask = (th // 255).astype('uint8')
	return mask


def mask_from_hsv(img):
	"""基于 HSV 的颜色阈值分割（皮肤/人像常用范围），返回 0/1 掩码"""
	hsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)
	# 这里为通用的人像/肤色范围，可按需微调
	lower = np.array([0, 30, 30], dtype=np.uint8)
	upper = np.array([50, 255, 255], dtype=np.uint8)
	m = cv2.inRange(hsv, lower, upper)
	mask = (m > 0).astype('uint8')
	return mask


def run_segmentation_method(method, src, params):
	"""根据 method 名称运行对应的分割方法，返回 0/1 掩码。
	支持: 'GrabCut', 'Otsu', 'HSV'。"""
	method = str(method).lower()
	if 'grab' in method:
		it = int(round(params.get('grabcut_iter', GRABCUT_ITER)))
		rect = int(round(params.get('rect_margin', RECT_MARGIN)))
		return grabcut_foreground(src, iter_count=it, rect_margin=rect)
	elif 'otsu' in method:
		return mask_from_otsu(src)
	elif 'hsv' in method:
		return mask_from_hsv(src)
	else:
		# fallback to grabcut
		return grabcut_foreground(src, iter_count=GRABCUT_ITER, rect_margin=RECT_MARGIN)


def refine_mask(mask, kernel_size=MORPH_KERNEL_SIZE, open_iter=MORPH_OPEN_ITER, dilate_iter=MORPH_DILATE_ITER, blur_size=BLUR_SIZE, expand_pixels=FG_EXPAND_PIXELS):
	# 预扩展前景（可将肩膀等未包含区域纳入）
	m0 = mask.copy()
	if expand_pixels and expand_pixels > 0:
		# 使用小核多次膨胀来扩展区域（iterations = expand_pixels）
		k_small = np.ones((3, 3), np.uint8)
		m0 = cv2.dilate(m0, k_small, iterations=int(max(1, expand_pixels)))

	# 形态学去噪并羽化
	kernel = np.ones((kernel_size, kernel_size), np.uint8)
	if open_iter > 0:
		m = cv2.morphologyEx(m0, cv2.MORPH_OPEN, kernel, iterations=open_iter)
	else:
		m = m0.copy()
	if dilate_iter > 0:
		m = cv2.morphologyEx(m, cv2.MORPH_DILATE, kernel, iterations=dilate_iter)
	# 转为 float 并羽化
	m_float = m.astype(np.float32)
	# 高斯模糊半径应为奇数
	if blur_size % 2 == 0:
		blur_size += 1
	alpha = cv2.GaussianBlur(m_float, (blur_size, blur_size), 0)
	# 归一化到 0-1
	alpha = (alpha - alpha.min()) / (alpha.max() - alpha.min() + 1e-8)
	return (m * 255).astype('uint8'), (alpha * 255).astype('uint8'), alpha


def composite_on_black(src, alpha):
	# src: BGR 图像 uint8
	# alpha: 2D float mask 0..1
	h, w = src.shape[:2]
	if len(alpha.shape) == 2:
		a = alpha[..., None]
	else:
		a = alpha
	# black background
	bg = np.zeros_like(src, dtype=np.uint8)
	# 将 src 转为 float
	src_f = src.astype(np.float32) / 255.0
	bg_f = bg.astype(np.float32) / 255.0
	out_f = src_f * a + bg_f * (1 - a)
	out = (out_f * 255).astype(np.uint8)
	return out


def launch_matplotlib_ui(src, fg_mask):
	"""使用 matplotlib 显示交互滑动条：
	- 可实时调整形态学与羽化参数
	- 可通过按钮重新运行 GrabCut（调整迭代次数与 rect margin）
	"""
	if plt is None:
		print('Matplotlib 未安装，无法启动交互界面。请安装 matplotlib 后重试。')
		return

	# 初始参数使用全局常量
	params = {
		'morph_kernel': float(MORPH_KERNEL_SIZE),
		'open_iter': float(MORPH_OPEN_ITER),
		'dilate_iter': float(MORPH_DILATE_ITER),
		'blur_size': float(BLUR_SIZE),
		'grabcut_iter': float(GRABCUT_ITER),
		'rect_margin': float(RECT_MARGIN),
		'expand': float(FG_EXPAND_PIXELS),
	}

	# helper 更新函数（根据当前 params 计算 refine + composite）
	def compute_and_get_images():
		k = int(max(1, round(params['morph_kernel'])))
		if k % 2 == 0:
			k += 1
		open_it = int(max(0, round(params['open_iter'])))
		dil_it = int(max(0, round(params['dilate_iter'])))
		blur = int(max(3, round(params['blur_size'])))
		if blur % 2 == 0:
			blur += 1
		expand_px = int(max(0, round(params.get('expand', 0))))
		mask_vis, alpha_vis, alpha = refine_mask(fg_mask, kernel_size=k, open_iter=open_it, dilate_iter=dil_it, blur_size=blur, expand_pixels=expand_px)
		comp = composite_on_black(src, alpha)
		# convert BGR->RGB for matplotlib
		src_rgb = cv2.cvtColor(src, cv2.COLOR_BGR2RGB)
		comp_rgb = cv2.cvtColor(comp, cv2.COLOR_BGR2RGB)
		return src_rgb, mask_vis, alpha_vis, comp_rgb

	# 创建图和滑动条布局
	fig, axes = plt.subplots(2, 2, figsize=(10, 7))
	plt.subplots_adjust(left=0.1, right=0.95, top=0.95, bottom=0.25)
	ax_src = axes[0, 0]
	ax_mask = axes[0, 1]
	ax_alpha = axes[1, 0]
	ax_comp = axes[1, 1]

	src_rgb, mask_vis, alpha_vis, comp_rgb = compute_and_get_images()

	im_src = ax_src.imshow(src_rgb)
	ax_src.set_title('Original')
	ax_src.axis('off')

	im_mask = ax_mask.imshow(mask_vis, cmap='gray', vmin=0, vmax=255)
	ax_mask.set_title('Binary Mask')
	ax_mask.axis('off')

	im_alpha = ax_alpha.imshow(alpha_vis, cmap='gray', vmin=0, vmax=255)
	ax_alpha.set_title('Alpha (feathered)')
	ax_alpha.axis('off')

	im_comp = ax_comp.imshow(comp_rgb)
	ax_comp.set_title('Composite on Black')
	ax_comp.axis('off')

	# slider 区域
	axcolor = 'lightgoldenrodyellow'
	ax_morph = plt.axes([0.12, 0.15, 0.35, 0.03], facecolor=axcolor)
	ax_open = plt.axes([0.12, 0.11, 0.35, 0.03], facecolor=axcolor)
	ax_dilate = plt.axes([0.12, 0.07, 0.35, 0.03], facecolor=axcolor)
	ax_blur = plt.axes([0.12, 0.03, 0.35, 0.03], facecolor=axcolor)
	ax_expand = plt.axes([0.12, 0.19, 0.35, 0.03], facecolor=axcolor)

	ax_grab_iter = plt.axes([0.6, 0.15, 0.25, 0.03], facecolor=axcolor)
	ax_rect = plt.axes([0.6, 0.11, 0.25, 0.03], facecolor=axcolor)
	ax_method = plt.axes([0.6, 0.19, 0.25, 0.08], facecolor=axcolor)

	s_morph = Slider(ax_morph, 'Morph K', 1, 11, valinit=params['morph_kernel'], valstep=1)
	s_open = Slider(ax_open, 'Open It', 0, 5, valinit=params['open_iter'], valstep=1)
	s_dilate = Slider(ax_dilate, 'Dilate It', 0, 5, valinit=params['dilate_iter'], valstep=1)
	s_blur = Slider(ax_blur, 'Blur', 3, 101, valinit=params['blur_size'], valstep=2)
	s_expand = Slider(ax_expand, 'Expand', 0, 50, valinit=params['expand'], valstep=1)

	s_grab_iter = Slider(ax_grab_iter, 'GrabIter', 1, 10, valinit=params['grabcut_iter'], valstep=1)
	s_rect = Slider(ax_rect, 'RectMargin', 0, min(src.shape[0], src.shape[1]) // 4, valinit=params['rect_margin'], valstep=1)

	# Buttons: Run segmentation (recompute fg_mask), Save
	ax_button_apply = plt.axes([0.6, 0.03, 0.12, 0.04])
	ax_button_save = plt.axes([0.74, 0.03, 0.12, 0.04])
	b_apply = Button(ax_button_apply, 'Run Segmentation')
	b_save = Button(ax_button_save, 'Save')

	# Method selector (RadioButtons)
	methods = ('GrabCut', 'Otsu', 'HSV')
	if RadioButtons is not None:
		r_method = RadioButtons(ax_method, methods)
	else:
		r_method = None

	def refresh_display():
		src_rgb, mask_vis_cur, alpha_vis_cur, comp_rgb = compute_and_get_images()
		im_mask.set_data(mask_vis_cur)
		im_alpha.set_data(alpha_vis_cur)
		im_comp.set_data(comp_rgb)
		# original not changed
		fig.canvas.draw_idle()

	# slider 回调，只更新 refine+composite，不重新运行 GrabCut
	def sliders_on_changed(val):
		params['morph_kernel'] = s_morph.val
		params['open_iter'] = s_open.val
		params['dilate_iter'] = s_dilate.val
		params['blur_size'] = s_blur.val
		params['expand'] = s_expand.val
		refresh_display()

	s_morph.on_changed(sliders_on_changed)
	s_open.on_changed(sliders_on_changed)
	s_dilate.on_changed(sliders_on_changed)
	s_blur.on_changed(sliders_on_changed)
	s_expand.on_changed(sliders_on_changed)

	# Run segmentation 按钮回调：根据当前 method 重新运行所选分割方法（可能较慢）
	def run_segmentation(event):
		params['grabcut_iter'] = s_grab_iter.val
		params['rect_margin'] = int(round(s_rect.val))
		# 重新运行所选方法
		nonlocal fg_mask
		method = params.get('method', 'GrabCut')
		print('Running segmentation:', method, 'iter=', int(params['grabcut_iter']), 'rect_margin=', int(params['rect_margin']))
		fg_mask = run_segmentation_method(method, src, params)
		refresh_display()

	b_apply.on_clicked(run_segmentation)

	# RadioButtons 回调：切换分割方法并立即运行一次
	def method_changed(label):
		params['method'] = label
		# 立即运行所选方法并更新显示
		nonlocal fg_mask
		fg_mask = run_segmentation_method(label, src, params)
		refresh_display()

	if r_method is not None:
		# 设定初始值
		params['method'] = methods[0]
		r_method.on_clicked(method_changed)

	# Save 当前结果
	def save_current(event):
		# compute final images
		_, mask_vis_cur, alpha_vis_cur, comp_rgb = compute_and_get_images()
		out_dir = os.path.dirname(__file__)
		out_path = os.path.join(out_dir, f'{OUTPUT_PREFIX}_foreground_on_black.png')
		mask_path = os.path.join(out_dir, f'{OUTPUT_PREFIX}_fg_mask.png')
		alpha_path = os.path.join(out_dir, f'{OUTPUT_PREFIX}_alpha.png')
		# comp_rgb 是 RGB，转换回 BGR 保存
		comp_bgr = cv2.cvtColor(comp_rgb, cv2.COLOR_RGB2BGR)
		save_image(out_path, comp_bgr)
		if SAVE_DEBUG_MASKS:
			save_image(mask_path, mask_vis_cur)
			save_image(alpha_path, alpha_vis_cur)
		print('Saved:', out_path)

	b_save.on_clicked(save_current)

	plt.show()


def main():
	ensure_cv2()
	base_dir = os.path.dirname(__file__)
	src_name = os.path.join(base_dir, SRC_FILENAME)
	if not os.path.exists(src_name):
		# 有时文件名为 Lenna.png
		alt = os.path.join(base_dir, 'Lenna.png')
		if os.path.exists(alt):
			src_name = alt
	print('读取图像:', src_name)
	src = load_image(src_name)
	# 若是带 alpha 的图片，先转换到 BGR
	if src.ndim == 3 and src.shape[2] == 4:
		src = cv2.cvtColor(src, cv2.COLOR_BGRA2BGR)

	fg_mask = grabcut_foreground(src)
	# 如果启用了交互 UI 并且 matplotlib 可用，则启动 UI（UI 中可保存结果）
	if USE_MATPLOTLIB_UI and plt is not None:
		launch_matplotlib_ui(src, fg_mask)
		return
	mask_vis, alpha_vis, alpha = refine_mask(fg_mask)

	result = composite_on_black(src, alpha)

	out_dir = base_dir
	out_path = os.path.join(out_dir, f'{OUTPUT_PREFIX}_foreground_on_black.png')
	mask_path = os.path.join(out_dir, f'{OUTPUT_PREFIX}_fg_mask.png')
	alpha_path = os.path.join(out_dir, f'{OUTPUT_PREFIX}_alpha.png')

	save_image(out_path, result)
	if SAVE_DEBUG_MASKS:
		save_image(mask_path, mask_vis)
		save_image(alpha_path, alpha_vis)

	print('已生成：')
	print(' - 合成图:', out_path)
	if SAVE_DEBUG_MASKS:
		print(' - 二值掩码:', mask_path)
		print(' - 羽化掩码:', alpha_path)


if __name__ == '__main__':
	main()

