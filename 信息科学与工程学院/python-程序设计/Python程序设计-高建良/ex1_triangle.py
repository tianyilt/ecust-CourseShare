from math import acos, sqrt

a = float(input("请输入第一条边边长："))
b = float(input("请输入第二条边边长："))
c = float(input("请输入第三条边边长："))
p = (a+b+c)/2
cos_angle = (b**2+c**2-a**2)/2*b*c

print("三角形的面积为：", format(sqrt(p*(p-a)*(p-b)*(p-c)), '.2f'))
print("角A为%.2f弧度" % acos(cos_angle))
