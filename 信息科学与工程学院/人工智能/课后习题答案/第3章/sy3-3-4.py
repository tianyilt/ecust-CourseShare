x = float(input("请输入被除数x: "))
y = float(input("请输入除数y: "))
if y == 0:
    z = 0
else:
    z = round(x / y, 2)
print("z=x/y=", z)
