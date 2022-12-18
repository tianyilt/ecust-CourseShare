import math


def isPrime(m):
    if m == 1:
        return False
    for i in range(2, int(math.sqrt(m)) + 1):
        if (m % i == 0):
            return False
    else:
        return True


def prtPrime(m, n):
    c = 0
    print("[%d,%d]范围内的素数有:" % (m, n))
    for i in range(m, n + 1):
        if isPrime(i):
            c += 1
            if c % 5 == 0:
                print(i, end=' \n')
            else:
                print(i, end=' ')
    return c


def main():
    m, n = input("输入m,n: ").split(",")
    m, n = int(m), int(n)

    if m <= 0 or n <= 0:
        print("输入不是正整数!")
    else:
        if m > n:
            m, n = n, m
        count = prtPrime(m, n)
        if count == 0:
            print("不存在素数!")


main()
