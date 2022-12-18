N = int(input("input N:"))
p = 1
for i in range(1, N + 1):
    p = p * i

print("{}!={}".format(N, p))
