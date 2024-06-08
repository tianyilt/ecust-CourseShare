# 输出Fibonacci数列所有小于100的项
# 运行结果参考：
# 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89
a=1
b=1
while(a<100):
    print(a, end=',')  
    a,b=b,b+a
