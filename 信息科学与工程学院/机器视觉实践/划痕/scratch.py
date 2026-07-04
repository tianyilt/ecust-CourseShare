from pathlib import Path
import matplotlib.pyplot as plt
import cv2

# Set matplotlib to use SimHei font for Chinese characters
plt.rcParams['font.sans-serif'] = ['SimHei']
plt.rcParams['axes.unicode_minus'] = False

def ipt(img: Path, mask: Path, output: Path):
    original_image = cv2.imread(str(img))
    mask_image = cv2.imread(str(mask), 0)  # mask is grayscale image

    # Use inpaint method to repair scratches
    restored_image = cv2.inpaint(
        src=original_image,
        inpaintMask=mask_image,
        inpaintRadius=3,
        # flags=cv2.INPAINT_NS,
        flags=cv2.INPAINT_TELEA,
    )

    # Save the restored image
    cv2.imwrite(str(output), restored_image)


def main():
    input_path = Path("E:\\testField\\scratch_pic.png")
    mask_path = Path("E:\\testField\\scratch_mask.jpg")
    output_path = Path("E:\\testField\\scratch_ipt_output.jpg")
    ipt(input_path, mask_path, output_path)


if __name__ == "__main__":
    main()
