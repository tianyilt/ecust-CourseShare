# 编写函数，判别一个正整数是否为素数；调用此函数，求前30个素数，按每行6个输出
# 例：
# 2	    3	5	7	11	13
# 17    19	23	29	31	37
# 41	43	47	53	59	61
# 67	71	73	79	83	89
# 97	101	103	107	109	113
# 程序文件名为：ex5_DefPrime.py

from math import sqrt

def is_Prime(x):
    for i in range(2,x):
        if(x%i==0):
            return False
    else:
        return True

count=0
num=2
while(count<30):
    if(is_Prime(num)):
        count+=1
        print(num,end="\t")
        if(count%6==0):
            print("")
    num+=1

