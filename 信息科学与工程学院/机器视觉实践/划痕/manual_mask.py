import cv2
import numpy as np


class ScratchMarker:
    def __init__(self, image_path):
        self.image_path = image_path
        self.original_img = cv2.imread(image_path)
        if self.original_img is None:
            print(f"Error: Cannot read image from {image_path}")
            exit(1)

        # 将图片放大1.5倍
        height, width = self.original_img.shape[:2]
        new_width = int(width * 1.5)
        new_height = int(height * 1.5)
        self.image = cv2.resize(self.original_img, (new_width, new_height), interpolation=cv2.INTER_LINEAR)

        self.mask = np.zeros(self.image.shape[:2], dtype=np.uint8)
        self.drawing = False
        self.last_point = None
        self.brush_size = 10

        cv2.namedWindow('Mark Scratches')
        cv2.setMouseCallback('Mark Scratches', self.mouse_callback)

        cv2.namedWindow('Controls')
        cv2.createTrackbar('Brush Size', 'Controls', 10, 30, self.update_brush_size)

    def update_brush_size(self, value):
        self.brush_size = max(1, value)

    def mouse_callback(self, event, x, y, flags, param):
        if event == cv2.EVENT_LBUTTONDOWN:
            self.drawing = True
            self.last_point = (x, y)
            cv2.circle(self.mask, (x, y), self.brush_size, 255, -1)

        elif event == cv2.EVENT_MOUSEMOVE:
            if self.drawing:
                if self.last_point:
                    cv2.line(self.mask, self.last_point, (x, y), 255, self.brush_size * 2)
                cv2.circle(self.mask, (x, y), self.brush_size, 255, -1)
                self.last_point = (x, y)

        elif event == cv2.EVENT_LBUTTONUP:
            self.drawing = False
            self.last_point = None

    def run(self):
        while True:
            display = self.image.copy()

            mask_color = np.zeros((*self.mask.shape, 3), dtype=np.uint8)
            mask_color[self.mask == 255] = [0, 0, 255]
            mask_color = cv2.addWeighted(display, 1.0, mask_color, 0.3, 0)
            display[self.mask == 255] = mask_color[self.mask == 255]

            cv2.imshow('Mark Scratches', display)

            key = cv2.waitKey(1) & 0xFF

            if key == ord('c') or key == ord('C'):
                cv2.imwrite('scratch_mask.png', self.mask)
                print("Mask saved as 'scratch_mask.png'")
                print(f"Mask size: {self.mask.shape}, Non-zero pixels: {np.count_nonzero(self.mask)}")
                break

            elif key == 27:
                print("Exiting without saving")
                break

        cv2.destroyAllWindows()

        if np.count_nonzero(self.mask) > 0:
            cv2.imshow('Final Mask', self.mask)
            cv2.waitKey(1000)
            cv2.destroyAllWindows()


if __name__ == "__main__":
    image_path = r"E:\testField\scratch_pic.png"
    marker = ScratchMarker(image_path)
    marker.run()