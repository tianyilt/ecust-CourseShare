from PIL import Image


def combine_images(image_paths, output_path):
    images = [Image.open(path) for path in image_paths]

    # 调整图像大小
    resized_images = [img.resize(target_size) for img in images]

    # 获取最大宽度和总高度
    max_width = max([img.size[0] for img in resized_images])
    total_height = sum([img.size[1] for img in resized_images])

    # 创建一个新的空白图像，宽度为最大宽度，高度为总高度
    combined_image = Image.new('RGB', (max_width, total_height))

    # 将图像逐个粘贴到新图像中
    y_offset = 0
    for img in resized_images:
        combined_image.paste(img, (0, y_offset))
        y_offset += img.size[1]
    # 保存合并后的图像
    combined_image.save(output_path)

target_size = (2000, 2859)
# 示例用法
image_paths=[]
for i in range(73):
    if i<=8:
        path='周学勤 20002520_页面_'+'0'+str(i+1)+'.jpf'
        image_paths.append(path)
    else:
        path = '周学勤 20002520_页面_' + str(i + 1) + '.jpf'
        image_paths.append(path)
output_path = 'combined_image.png'
combine_images(image_paths, output_path)
