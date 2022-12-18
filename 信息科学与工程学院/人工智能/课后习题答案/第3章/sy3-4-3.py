import math


def areaCircle(radius):
    s = math.pi * radius * radius
    return s


R = float(input("外径= "))
r = float(input("内径= "))
n = float(input("数量= "))
area = n * (areaCircle(R) - areaCircle(r))
print('垫片的面积：{:.2f}'.format(area))
