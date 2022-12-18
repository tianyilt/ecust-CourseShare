# 判断一个点在圆内、圆上还是圆外
from math import sqrt

r = float(input("请输入圆半径："))
print("请输入点的坐标:")
x = float(input("x："))
y = float(input("y："))
d = sqrt(x * x + y * y)
print(d)
if d < r:
    print("点在圆内")
elif d > r:
    print("点在圆外")
else:
    print("点在圆上")
