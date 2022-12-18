# 定义最大公约数函数
def gcd(x, y):  # 辗转相除法
    r = x % y
    while r != 0:
        x, y = y, r
        r = x % y
    return y


# 定义最小公倍数函数
def lcm(x, y):
    return int(x * y / gcd(x, y))


# 用户输入两个数字
num1 = int(input())
num2 = int(input())
print("最大公约数为: ", gcd(num1, num2))
print("最小公倍数为: ", lcm(num1, num2))
