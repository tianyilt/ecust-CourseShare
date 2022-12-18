a = float(input("a="))
b = float(input("b="))
c = float(input("c="))
if (a + b - c) * (a + c - b) * (b + c - a) > 0:
    print('YES')
    p = (a + b + c) / 2
    area = (p * (p - a) * (p - b) * (p - c)) ** (1 / 2)
    print(area)
else:
    print('NO')
