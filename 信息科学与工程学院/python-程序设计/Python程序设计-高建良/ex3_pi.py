# 利用下列级数求和公式求Pi的值：
# Pi/2=1+1/3+(1/3)*(2/5)+(1/3)*(2/5)*(3/7)+...
# 运行结果参考：
# 通过级数求和得到Pi的值为：3.1415926533
# math模块的pi值为：3.1415926536
# 程序文件名为ex2_Pi.py
from math import pi
a=1
s=1
for i in range(1,31):
    a*=i/(2*i+1)
    s+=a
print("my:",round(2*s,10))
print("pi:",round(pi,10))