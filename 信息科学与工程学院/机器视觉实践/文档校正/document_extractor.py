import cv2
import numpy as np
import os
import glob
import time
import argparse
from pathlib import Path
import warnings

warnings.filterwarnings("ignore")


class DocumentExtractor:
    def __init__(self, debug=False):
        """
        初始化文档提取器

        参数:
            debug (bool): 是否显示调试图像
        """
        self.debug = debug
        self.min_area = 5000  # 增加最小轮廓面积，过滤小区域
        self.approx_epsilon = 0.02  # 多边形逼近的精度

    def load_image(self, image_path):
        """
        加载图像

        参数:
            image_path (str): 图像路径

        返回:
            numpy.ndarray: 加载的图像
        """
        image = cv2.imread(image_path)
        if image is None:
            print(f"错误: 无法加载图像 {image_path}")
            return None
        return image

    def preprocess_image(self, image):
        """
        增强图像预处理，更好检测文档边缘

        参数:
            image (numpy.ndarray): 输入图像

        返回:
            numpy.ndarray: 预处理后的图像
        """
        # 转换为灰度图
        gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

        # 高斯模糊降噪
        blurred = cv2.GaussianBlur(gray, (7, 7), 0)

        # 使用边缘检测替代二值化，更好检测文档边界
        edges = cv2.Canny(blurred, 50, 150)

        # 形态学操作连接边缘
        kernel = np.ones((5, 5), np.uint8)
        edges = cv2.dilate(edges, kernel, iterations=1)
        edges = cv2.erode(edges, kernel, iterations=1)

        if self.debug:
            cv2.imshow("Edges", edges)
            cv2.waitKey(1)

        return edges, gray

    def find_document_contour(self, edge_image, original_image):
        """
        改进的文档轮廓检测，使用边缘检测和多层筛选

        参数:
            edge_image (numpy.ndarray): 边缘图像
            original_image (numpy.ndarray): 原始图像

        返回:
            numpy.ndarray: 文档轮廓点
        """
        # 查找轮廓
        contours, _ = cv2.findContours(
            edge_image, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE
        )

        if not contours:
            return None

        # 按面积排序
        contours = sorted(contours, key=cv2.contourArea, reverse=True)

        # 寻找最大的近似四边形轮廓
        document_contour = None

        for contour in contours:
            area = cv2.contourArea(contour)
            if area < self.min_area:
                continue

            # 计算轮廓周长
            perimeter = cv2.arcLength(contour, True)

            # 多边形逼近
            epsilon = self.approx_epsilon * perimeter
            approx = cv2.approxPolyDP(contour, epsilon, True)

            # 如果是四边形
            if len(approx) == 4:
                # 检查四边形是否凸的
                if cv2.isContourConvex(approx):
                    document_contour = approx
                    break
            # 如果不是四边形，尝试找到凸包
            elif len(approx) > 4:
                # 获取凸包
                hull = cv2.convexHull(approx)
                hull_perimeter = cv2.arcLength(hull, True)
                hull_epsilon = 0.02 * hull_perimeter
                hull_approx = cv2.approxPolyDP(hull, hull_epsilon, True)

                if len(hull_approx) == 4 and cv2.isContourConvex(hull_approx):
                    document_contour = hull_approx
                    break

        # 如果没有找到合适的四边形，使用最大的凸四边形
        if document_contour is None and len(contours) > 0:
            largest_contour = contours[0]
            hull = cv2.convexHull(largest_contour)
            perimeter = cv2.arcLength(hull, True)
            epsilon = 0.02 * perimeter
            approx = cv2.approxPolyDP(hull, epsilon, True)

            if len(approx) == 4:
                document_contour = approx

        if self.debug and document_contour is not None:
            debug_img = original_image.copy()
            cv2.drawContours(debug_img, [document_contour], -1, (0, 255, 0), 3)

            # 绘制四个角点
            for point in document_contour:
                cv2.circle(debug_img, tuple(point[0]), 10, (0, 0, 255), -1)

            cv2.imshow("Document Contour with Points", debug_img)
            cv2.waitKey(1)

        return document_contour

    def order_points(self, pts):
        """
        改进的点排序方法，确保正确的方向

        参数:
            pts (numpy.ndarray): 四个点

        返回:
            numpy.ndarray: 排序后的点
        """
        # 转换为浮点型
        pts = pts.reshape(4, 2).astype("float32")

        # 初始化坐标点
        rect = np.zeros((4, 2), dtype="float32")

        # 找到左上和右下点
        s = pts.sum(axis=1)
        rect[0] = pts[np.argmin(s)]  # 左上：和最小
        rect[2] = pts[np.argmax(s)]  # 右下：和最大

        # 找到右上和左下点
        diff = np.diff(pts, axis=1)
        rect[1] = pts[np.argmin(diff)]  # 右上：差最小
        rect[3] = pts[np.argmax(diff)]  # 左下：差最大

        return rect

    def correct_perspective(self, image, pts):
        """
        改进的透视校正方法，确保正面视角

        参数:
            image (numpy.ndarray): 原始图像
            pts (numpy.ndarray): 四个角点

        返回:
            numpy.ndarray: 校正后的图像
        """
        # 获取有序的点
        rect = self.order_points(pts)
        (tl, tr, br, bl) = rect

        # 计算新图像的宽度（取两条边的平均值）
        width_a = np.sqrt(((br[0] - bl[0]) ** 2) + ((br[1] - bl[1]) ** 2))
        width_b = np.sqrt(((tr[0] - tl[0]) ** 2) + ((tr[1] - tl[1]) ** 2))
        max_width = max(int(width_a), int(width_b))

        # 计算新图像的高度
        height_a = np.sqrt(((tr[0] - br[0]) ** 2) + ((tr[1] - br[1]) ** 2))
        height_b = np.sqrt(((tl[0] - bl[0]) ** 2) + ((tl[1] - bl[1]) ** 2))
        max_height = max(int(height_a), int(height_b))

        # 创建目标点，确保文档为正面矩形
        dst = np.array(
            [
                [0, 0],
                [max_width - 1, 0],
                [max_width - 1, max_height - 1],
                [0, max_height - 1],
            ],
            dtype="float32",
        )

        # 计算透视变换矩阵
        M = cv2.getPerspectiveTransform(rect, dst)

        # 应用透视变换
        warped = cv2.warpPerspective(
            image,
            M,
            (max_width, max_height),
            flags=cv2.INTER_CUBIC,
            borderMode=cv2.BORDER_REPLICATE,
        )

        # 检查是否需要旋转（确保文本方向正确）
        warped = self.ensure_upright(warped)

        return warped

    def ensure_upright(self, image):
        """
        确保图像方向正确（文本朝上）

        参数:
            image (numpy.ndarray): 输入图像

        返回:
            numpy.ndarray: 方向正确的图像
        """
        # 转换为灰度
        gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

        # 使用Sobel算子检测边缘方向
        sobelx = cv2.Sobel(gray, cv2.CV_64F, 1, 0, ksize=3)
        sobely = cv2.Sobel(gray, cv2.CV_64F, 0, 1, ksize=3)

        # 计算梯度方向
        orientation = np.arctan2(np.abs(sobely), np.abs(sobelx)) * 180 / np.pi

        # 计算方向直方图
        hist, bins = np.histogram(orientation.flatten(), bins=36, range=[0, 180])

        # 找到主要方向
        dominant_angle = bins[np.argmax(hist)]

        # 如果主要方向接近90度，图像可能是横躺的
        if abs(dominant_angle - 90) < 20:
            # 旋转90度
            (h, w) = image.shape[:2]
            center = (w // 2, h // 2)
            M = cv2.getRotationMatrix2D(center, 90, 1.0)
            rotated = cv2.warpAffine(image, M, (h, w))
            return rotated

        return image

    def deskew_image(self, image):
        """
        改进的倾斜校正方法，使用投影轮廓分析

        参数:
            image (numpy.ndarray): 输入图像

        返回:
            numpy.ndarray: 校正后的图像
        """
        # 转换为灰度
        gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

        # 二值化
        _, binary = cv2.threshold(gray, 0, 255, cv2.THRESH_BINARY_INV + cv2.THRESH_OTSU)

        # 形态学操作去除噪声
        kernel = np.ones((3, 3), np.uint8)
        binary = cv2.morphologyEx(binary, cv2.MORPH_CLOSE, kernel)

        # 使用投影轮廓分析检测倾斜角度
        height, width = binary.shape

        # 计算水平投影
        horizontal_projection = np.sum(binary, axis=1)

        # 找到文本区域
        text_mask = horizontal_projection > np.mean(horizontal_projection) * 0.1

        # 获取文本区域索引
        text_indices = np.where(text_mask)[0]

        if len(text_indices) < 2:
            return image

        # 使用最小二乘法拟合直线，计算倾斜角度
        y_coords = text_indices
        x_coords = np.array(
            [
                (
                    np.mean(np.where(binary[y] > 0)[0])
                    if np.any(binary[y] > 0)
                    else width / 2
                )
                for y in y_coords
            ]
        )

        # 拟合直线
        A = np.vstack([x_coords, np.ones(len(x_coords))]).T
        slope, intercept = np.linalg.lstsq(A, y_coords, rcond=None)[0]

        # 计算角度
        angle = np.degrees(np.arctan(slope))

        # 如果角度太小，不旋转
        if abs(angle) < 0.5:
            return image

        # 旋转图像
        (h, w) = image.shape[:2]
        center = (w // 2, h // 2)
        M = cv2.getRotationMatrix2D(center, angle, 1.0)

        # 计算新的边界
        cos = np.abs(M[0, 0])
        sin = np.abs(M[0, 1])

        new_w = int((h * sin) + (w * cos))
        new_h = int((h * cos) + (w * sin))

        # 调整旋转矩阵
        M[0, 2] += (new_w / 2) - center[0]
        M[1, 2] += (new_h / 2) - center[1]

        # 执行旋转
        rotated = cv2.warpAffine(
            image,
            M,
            (new_w, new_h),
            flags=cv2.INTER_CUBIC,
            borderMode=cv2.BORDER_REPLICATE,
        )

        return rotated

    def enhance_document(self, image):
        """
        改进的图像增强，保持清晰边缘和色彩

        参数:
            image (numpy.ndarray): 输入图像

        返回:
            numpy.ndarray: 增强后的图像
        """
        if len(image.shape) == 3:
            # 彩色图像：对每个通道分别应用CLAHE
            channels = cv2.split(image)
            clahe = cv2.createCLAHE(clipLimit=2.0, tileGridSize=(8, 8))
            enhanced_channels = [clahe.apply(ch) for ch in channels]
            enhanced = cv2.merge(enhanced_channels)
            return enhanced
        else:
            # 灰度图像：直接应用CLAHE
            clahe = cv2.createCLAHE(clipLimit=2.0, tileGridSize=(8, 8))
            enhanced = clahe.apply(image)
            return enhanced

    def detect_and_correct_with_hough(self, image):
        """
        使用霍夫变换检测直线并校正透视

        参数:
            image (numpy.ndarray): 输入图像

        返回:
            numpy.ndarray: 校正后的图像
        """
        # 转换为灰度
        gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

        # 边缘检测
        edges = cv2.Canny(gray, 50, 150, apertureSize=3)

        # 使用霍夫变换检测直线
        lines = cv2.HoughLines(edges, 1, np.pi / 180, 200)

        if lines is None:
            return image

        # 分组直线（水平和垂直）
        horizontal_lines = []
        vertical_lines = []

        for line in lines:
            rho, theta = line[0]

            # 分类为水平或垂直
            angle = theta * 180 / np.pi
            if angle < 45 or angle > 135:
                horizontal_lines.append((rho, theta))
            else:
                vertical_lines.append((rho, theta))

        # 如果没有足够的直线，返回原图
        if len(horizontal_lines) < 2 or len(vertical_lines) < 2:
            return image

        # 找到最外面的四条直线
        horizontal_lines.sort(key=lambda x: x[0])
        vertical_lines.sort(key=lambda x: x[0])

        # 选择两条水平线和两条垂直线
        top_line = horizontal_lines[0]
        bottom_line = horizontal_lines[-1]
        left_line = vertical_lines[0]
        right_line = vertical_lines[-1]

        # 计算四个交点
        def intersection(line1, line2):
            rho1, theta1 = line1
            rho2, theta2 = line2

            A = np.array(
                [[np.cos(theta1), np.sin(theta1)], [np.cos(theta2), np.sin(theta2)]]
            )
            b = np.array([[rho1], [rho2]])

            try:
                x, y = np.linalg.solve(A, b)
                return int(x), int(y)
            except np.linalg.LinAlgError:
                return None

        # 计算四个角点
        corners = []

        # 左上角：top_line 和 left_line 的交点
        tl = intersection(top_line, left_line)
        if tl:
            corners.append(tl)

        # 右上角：top_line 和 right_line 的交点
        tr = intersection(top_line, right_line)
        if tr:
            corners.append(tr)

        # 右下角：bottom_line 和 right_line 的交点
        br = intersection(bottom_line, right_line)
        if br:
            corners.append(br)

        # 左下角：bottom_line 和 left_line 的交点
        bl = intersection(bottom_line, left_line)
        if bl:
            corners.append(bl)

        # 如果有四个角点，进行透视校正
        if len(corners) == 4:
            corners = np.array(corners, dtype="float32")
            return self.correct_perspective(image, corners)

        return image

    def process_image(self, image_path, output_dir=None):
        """
        改进的图像处理流程

        参数:
            image_path (str): 输入图像路径
            output_dir (str): 输出目录

        返回:
            tuple: (成功标志, 处理时间, 输出路径)
        """
        start_time = time.time()

        # 加载图像
        original = self.load_image(image_path)
        if original is None:
            return False, 0, None

        # 备份原始图像
        image = original.copy()

        # 方法1：使用边缘检测和轮廓分析
        edges, gray = self.preprocess_image(image)
        document_contour = self.find_document_contour(edges, image)

        if document_contour is not None:
            # 透视变换校正
            corrected = self.correct_perspective(original, document_contour)
            method_used = "contour_based"
        else:
            # 方法2：使用霍夫变换检测直线
            corrected = self.detect_and_correct_with_hough(original)
            if corrected is not original:
                method_used = "hough_based"
            else:
                # 方法3：使用倾斜校正
                corrected = self.deskew_image(original)
                method_used = "deskew"

        # 增强文档
        enhanced = self.enhance_document(corrected)

        # 保存结果
        if output_dir is None:
            output_dir = os.path.dirname(image_path)

        # 创建输出文件名
        filename = os.path.basename(image_path)
        name, ext = os.path.splitext(filename)

        # 保存校正后的图像
        output_filename = f"{name}_corrected{ext}"
        output_path = os.path.join(output_dir, output_filename)
        cv2.imwrite(output_path, enhanced)

        # 保存原始校正图像
        corrected_filename = f"{name}_corrected_raw{ext}"
        corrected_path = os.path.join(output_dir, corrected_filename)
        cv2.imwrite(corrected_path, corrected)

        processing_time = time.time() - start_time

        print(f"处理完成: {filename}")
        print(f"  使用方法: {method_used}")
        print(f"  处理时间: {processing_time:.3f}秒")
        print(f"  输出文件: {output_filename}, {corrected_filename}")
        print("-" * 50)

        return True, processing_time, (output_path, corrected_path)

    def process_folder(self, input_folder, output_folder=None):
        """
        处理整个文件夹中的图像

        参数:
            input_folder (str): 输入文件夹路径
            output_folder (str): 输出文件夹路径

        返回:
            dict: 处理结果统计
        """
        # 获取所有图像文件
        image_extensions = ["*.jpg", "*.jpeg", "*.png", "*.bmp", "*.tiff"]
        image_paths = []

        for ext in image_extensions:
            image_paths.extend(glob.glob(os.path.join(input_folder, ext)))

        if not image_paths:
            print(f"在文件夹 {input_folder} 中没有找到图像文件")
            return None

        print(f"找到 {len(image_paths)} 张图像需要处理")

        # 创建输出文件夹
        if output_folder is None:
            output_folder = os.path.join(input_folder, "corrected_output")

        os.makedirs(output_folder, exist_ok=True)

        # 处理每张图像
        results = {
            "total": len(image_paths),
            "success": 0,
            "failed": 0,
            "total_time": 0,
            "details": [],
        }

        for i, image_path in enumerate(image_paths, 1):
            print(f"处理图像 {i}/{len(image_paths)}: {os.path.basename(image_path)}")

            success, proc_time, output_paths = self.process_image(
                image_path, output_folder
            )

            if success:
                results["success"] += 1
                results["total_time"] += proc_time
                results["details"].append(
                    {
                        "input": image_path,
                        "output": output_paths[0],
                        "enhanced": output_paths[1],
                        "time": proc_time,
                        "success": True,
                    }
                )
            else:
                results["failed"] += 1
                results["details"].append(
                    {
                        "input": image_path,
                        "output": None,
                        "time": proc_time,
                        "success": False,
                    }
                )

        # 打印统计信息
        print("\n" + "=" * 50)
        print("处理完成!")
        print(f"成功处理: {results['success']}/{results['total']}")
        print(f"平均处理时间: {results['total_time']/max(results['success'], 1):.3f}秒")
        print(f"输出文件夹: {output_folder}")
        print("=" * 50)

        return results


def main():
    """
    主函数：解析命令行参数并运行文档提取器
    """
    parser = argparse.ArgumentParser(description="改进的文档图像提取与校正系统")
    parser.add_argument(
        "--input",
        type=str,
        default="./input_images",
        help="输入图像文件夹路径 (默认: ./input_images)",
    )
    parser.add_argument(
        "--output",
        type=str,
        default=None,
        help="输出文件夹路径 (默认: 输入文件夹/corrected_output)",
    )
    parser.add_argument(
        "--debug", action="store_true", help="启用调试模式，显示中间处理步骤"
    )
    parser.add_argument(
        "--single", type=str, default=None, help="处理单张图像，指定图像路径"
    )

    args = parser.parse_args()

    # 创建文档提取器
    extractor = DocumentExtractor(debug=args.debug)

    if args.debug:
        print("调试模式已启用")
        print("提示：按任意键继续查看下一张调试图像")

    if args.single:
        # 处理单张图像
        print(f"处理单张图像: {args.single}")
        success, time_taken, output_paths = extractor.process_image(
            args.single, args.output
        )

        if success:
            print(f"成功处理，结果保存在: {output_paths[0]}")
            # 使用matplotlib展示原图和校正后效果对比
            import matplotlib.pyplot as plt

            original = extractor.load_image(args.single)
            corrected = extractor.load_image(output_paths[0])
            # OpenCV读取的图像是BGR，matplotlib需要RGB
            original_rgb = cv2.cvtColor(original, cv2.COLOR_BGR2RGB)
            # 校正后图像可能是灰度或BGR，需判断
            if len(corrected.shape) == 2:
                corrected_rgb = cv2.cvtColor(corrected, cv2.COLOR_GRAY2RGB)
            elif corrected.shape[2] == 3:
                corrected_rgb = cv2.cvtColor(corrected, cv2.COLOR_BGR2RGB)
            else:
                corrected_rgb = corrected
            plt.figure(figsize=(10, 5))
            plt.subplot(1, 2, 1)
            plt.imshow(original_rgb)
            plt.title("Original")
            plt.axis("off")
            plt.subplot(1, 2, 2)
            plt.imshow(corrected_rgb)
            plt.title("Corrected")
            plt.axis("off")
            plt.tight_layout()
            plt.show()
        else:
            print("处理失败")
    else:
        # 处理文件夹
        print(f"处理文件夹: {args.input}")

        # 检查输入文件夹是否存在
        if not os.path.exists(args.input):
            print(f"错误: 输入文件夹 {args.input} 不存在")
            return

        # 处理文件夹中的所有图像
        results = extractor.process_folder(args.input, args.output)

        # 生成处理报告
        if results:
            report_path = os.path.join(
                (
                    args.output
                    if args.output
                    else os.path.join(args.input, "corrected_output")
                ),
                "processing_report.txt",
            )

            with open(report_path, "w", encoding="utf-8") as f:
                f.write("文档图像处理报告\n")
                f.write("=" * 50 + "\n")
                f.write(f"处理时间: {time.strftime('%Y-%m-%d %H:%M:%S')}\n")
                f.write(f"输入文件夹: {args.input}\n")
                f.write(f"总图像数: {results['total']}\n")
                f.write(f"成功处理: {results['success']}\n")
                f.write(f"处理失败: {results['failed']}\n")
                f.write(f"总处理时间: {results['total_time']:.2f}秒\n")
                f.write(
                    f"平均处理时间: {results['total_time']/max(results['success'], 1):.3f}秒\n"
                )
                f.write("\n详细信息:\n")

                for detail in results["details"]:
                    f.write(f"\n文件: {os.path.basename(detail['input'])}\n")
                    f.write(f"  状态: {'成功' if detail['success'] else '失败'}\n")
                    if detail["success"]:
                        f.write(f"  处理时间: {detail['time']:.3f}秒\n")
                        f.write(f"  输出文件: {os.path.basename(detail['output'])}\n")

            print(f"处理报告已保存: {report_path}")


if __name__ == "__main__":
    main()
