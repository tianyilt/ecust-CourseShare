# 导入Pillow库
from PIL import Image

# 读入图像lena.jpg
im = Image.open('lena.jpg')

# 模式转换为二值图像
new_im_test = im.convert("1")
print('图像new_im_L的模式为：', new_im_test.mode)
new_im_test.show()

# 将图像逆时针选择180度
im_test = im.rotate(180)
im_test.show()

# 获取(100,100)像素的颜色值
print(im.getpixel((100, 100)))

# 分离合并颜色通道
R, G, B = im.split()
