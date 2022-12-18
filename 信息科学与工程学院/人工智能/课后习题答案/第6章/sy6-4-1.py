# 导入Pillow库
from PIL import Image

# 读入图像lena.jpg
im = Image.open('lena.jpg')
print('图像的尺寸为：', im.size)

# 模式转换为灰度图
new_im_L = im.convert("L")
print('图像new_im_L的模式为：', new_im_L.mode)

# 将图像设置为220*150，并显示
im_resize = im.resize((220, 150))  # 重新设定大小
print('图像im_resize的尺寸为：', im_resize.size)
im_resize.show()

# 显示边缘信息
from PIL import ImageFilter

im_test = im.filter(ImageFilter.CONTOUR)
im_test.show()
