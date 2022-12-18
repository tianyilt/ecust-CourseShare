m = int(input("m="))
n = int(input("n="))
if m > n:
    m, n = n, m
total = 0
for i in range(m, n + 1):
    total = total + i
print("m~n的累加和为:{}".format(total))
