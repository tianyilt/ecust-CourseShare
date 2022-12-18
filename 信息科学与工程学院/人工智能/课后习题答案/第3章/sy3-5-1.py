n = int(input("n=(n<100)："))
ls = []
for i in range(n):
    if i % 7 == 0 or i % 10 == 7 or i // 10 == 7:
        ls.append(i)
print(ls)
print("sum=", sum(ls))
