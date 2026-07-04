import cv2
import numpy as np
import os
import matplotlib.pyplot as plt


class SimpleMoleRemover:
    def __init__(self):
        self.original_img = None
        self.display_img = None
        self.result_img = None
        self.mask = None
        self.mole_points = []
        self.brush_size = 15
        self.is_drawing = False
        self.window_name = "SPACE to process, R to reset, Q to quit"


    def load_image(self, path):
        """加载图像"""
        self.original_img = cv2.imread(path)
        if self.original_img is None:
            print(f"错误: 无法读取图片 '{path}'")
            return False

        print(f"✓ 图片尺寸: {self.original_img.shape[1]}x{self.original_img.shape[0]}")

        # 调整图片大小以适应显示
        h, w = self.original_img.shape[:2]
        if max(h, w) > 800:
            scale = 800 / max(h, w)
            new_w = int(w * scale)
            new_h = int(h * scale)
            self.original_img = cv2.resize(self.original_img, (new_w, new_h))
            print(f"✓ 调整为: {new_w}x{new_h}")

        # 创建显示图像的副本
        self.display_img = self.original_img.copy()

        # 初始化掩码
        self.mask = np.zeros(self.original_img.shape[:2], dtype=np.uint8)

        return True

    def mouse_callback(self, event, x, y, flags, param):
        """鼠标回调函数"""
        if event == cv2.EVENT_LBUTTONDOWN:
            self.is_drawing = True
            self.add_mole(x, y)

        elif event == cv2.EVENT_MOUSEMOVE:
            if self.is_drawing:
                self.add_mole(x, y)

        elif event == cv2.EVENT_LBUTTONUP:
            self.is_drawing = False

    def add_mole(self, x, y):
        """添加痣标记"""
        # 确保坐标在图像范围内
        x = max(self.brush_size, min(x, self.original_img.shape[1] - self.brush_size - 1))
        y = max(self.brush_size, min(y, self.original_img.shape[0] - self.brush_size - 1))

        # 检查是否已经在此位置附近标记过
        too_close = False
        for px, py, radius in self.mole_points:
            distance = np.sqrt((x - px) ** 2 + (y - py) ** 2)
            if distance < self.brush_size * 1.5:
                too_close = True
                break

        if not too_close:
            # 添加到痣列表
            self.mole_points.append((x, y, self.brush_size))

            # 在掩码上标记
            cv2.circle(self.mask, (x, y), self.brush_size, 255, -1)

            # 在显示图像上标记为蓝色空心圆（去掉中心实心点）
            cv2.circle(self.display_img, (x, y), self.brush_size, (255, 0, 0), 2)

            # 显示编号
            cv2.putText(self.display_img, f"{len(self.mole_points)}",
                        (x - 5, y + 5), cv2.FONT_HERSHEY_SIMPLEX,
                        0.6, (255, 255, 255), 2)

    def remove_mole(self):
        """移除最后一个标记"""
        if self.mole_points:
            self.mole_points.pop()

            # 重新绘制显示图像
            self.display_img = self.original_img.copy()
            self.redraw_moles()

    def redraw_moles(self):
        """重新绘制所有痣标记"""
        self.mask = np.zeros(self.original_img.shape[:2], dtype=np.uint8)

        for i, (x, y, radius) in enumerate(self.mole_points):
            # 在掩码上标记
            cv2.circle(self.mask, (x, y), radius, 255, -1)

            # 在显示图像上标记为蓝色空心圆（去掉中心实心点）
            cv2.circle(self.display_img, (x, y), radius, (255, 0, 0), 2)

            # 显示编号
            cv2.putText(self.display_img, f"{i + 1}",
                        (x - 5, y + 5), cv2.FONT_HERSHEY_SIMPLEX,
                        0.6, (255, 255, 255), 2)

    def adjust_brush_size(self, increase=True):
        """调整画笔大小"""
        if increase:
            self.brush_size = min(30, self.brush_size + 2)
        else:
            self.brush_size = max(5, self.brush_size - 2)

        print(f"画笔大小: {self.brush_size}")

    def process_moles(self):
        """处理标记的痣"""
        if len(self.mole_points) == 0:
            print("没有标记痣，无法处理")
            return None

        print(f"正在处理 {len(self.mole_points)} 个痣...")

        # 创建增强掩码
        enhanced_mask = self.mask.copy()
        kernel = np.ones((3, 3), np.uint8)
        enhanced_mask = cv2.dilate(enhanced_mask, kernel, iterations=2)

        # 使用图像修复算法
        self.result_img = cv2.inpaint(self.original_img, enhanced_mask,
                                      inpaintRadius=self.brush_size + 3,
                                      flags=cv2.INPAINT_TELEA)

        print("✓ 处理完成")
        return self.result_img

    def show_comparison(self):
        """显示对比图"""
        if self.result_img is None:
            print("错误: 没有处理结果可显示")
            return

        # 设置中文字体
        plt.rcParams['font.sans-serif'] = ['SimHei', 'Microsoft YaHei', 'DejaVu Sans']
        plt.rcParams['axes.unicode_minus'] = False

        # 创建对比图
        fig, axes = plt.subplots(1, 2, figsize=(12, 5))

        # 显示原图
        axes[0].imshow(cv2.cvtColor(self.original_img, cv2.COLOR_BGR2RGB))
        axes[0].set_title('原始图片', fontsize=14)
        axes[0].axis('off')

        # 显示结果
        axes[1].imshow(cv2.cvtColor(self.result_img, cv2.COLOR_BGR2RGB))
        axes[1].set_title('祛痣结果', fontsize=14)
        axes[1].axis('off')

        plt.tight_layout()
        plt.show()

    def save_result(self):
        """保存结果"""
        if self.result_img is None:
            return False

        # 生成文件名
        import datetime
        timestamp = datetime.datetime.now().strftime("%Y%m%d_%H%M%S")
        path = f"result_{timestamp}.jpg"

        cv2.imwrite(path, self.result_img)
        print(f"✓ 结果已保存为: {path}")
        return True

    def reset_all(self):
        """重置所有标记"""
        self.display_img = self.original_img.copy()
        self.mask = np.zeros(self.original_img.shape[:2], dtype=np.uint8)
        self.mole_points = []
        print("✓ 已重置所有标记")

    def run_interactive(self):
        """运行交互式界面"""
        if self.original_img is None:
            print("错误: 请先加载图像")
            return

        # 创建窗口
        cv2.namedWindow(self.window_name, cv2.WINDOW_NORMAL)
        cv2.setMouseCallback(self.window_name, self.mouse_callback)

        print("=" * 50)
        print("    手动祛痣程序")
        print("=" * 50)
        print("使用方法:")
        print("  鼠标左键: 标记痣的位置")
        print("  + / - : 增大/减小画笔大小")
        print("  R : 重置所有标记")
        print("  SPACE : 开始处理")
        print("  Q / ESC : 退出程序")
        print("=" * 50)

        while True:
            # 显示图像
            cv2.imshow(self.window_name, self.display_img)

            # 处理按键
            key = cv2.waitKey(1) & 0xFF

            if key == ord('q') or key == 27:  # Q 或 ESC
                print("退出程序")
                break

            elif key == ord(' '):  # 空格键 - 开始处理
                if len(self.mole_points) > 0:
                    cv2.destroyAllWindows()
                    self.process_moles()
                    self.save_result()  # 自动保存
                    self.show_comparison()  # 显示对比图
                    break
                else:
                    print("请先标记至少一个痣的位置")

            elif key == ord('r') or key == ord('R'):  # 重置
                self.reset_all()

            elif key == ord('+') or key == 43:  # 增大画笔
                self.adjust_brush_size(increase=True)

            elif key == ord('-') or key == 45:  # 减小画笔
                self.adjust_brush_size(increase=False)

        cv2.destroyAllWindows()


def main():
    print("手动祛痣程序 - 简化版")

    # ========== 在这里设置图片路径 ==========
    image_path = "input.png"  # 改成你的图片文件名
    # ======================================

    # 检查文件是否存在
    if not os.path.exists(image_path):
        print(f"错误: 找不到文件 '{image_path}'")
        print("当前目录下的图片文件:")
        for f in os.listdir('.'):
            if f.lower().endswith(('.jpg', '.jpeg', '.png', '.bmp')):
                print(f"  - {f}")
        return

    # 创建祛痣器
    remover = SimpleMoleRemover()

    # 加载图像
    if not remover.load_image(image_path):
        return

    # 运行交互式界面
    remover.run_interactive()

    print("程序结束")


if __name__ == "__main__":
    main()