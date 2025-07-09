# 编写函数，求两个正整数的最大公约数和最小公倍数，
# 将此两个数作为一个元组返回；调用此函数，验证此函数功能

# 请输入两个正整数：24,16
# 24和16的最大公约数和最小公倍数分别为： (8, 48)

def getGcd(x, y):
    m = x*y  # 用于最终求最小公倍数
    z = x % y
    while(z):
        x = y
        y = z
        z = x % y
    return (y, int(m/y))


a, b = map(int, (input("请输入两个正整数 以逗号分开").split(",")))
print("{0}和{1}的最大公约数和最小公倍数为".format(a,b), getGcd(a, b))
# 这个语句改成format形式
