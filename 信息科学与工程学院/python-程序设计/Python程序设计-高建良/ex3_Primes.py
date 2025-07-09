# 输出150以内的所有素数，每9个一行
# 运行结果参考：
# 1     2     3     5     7     11    13    17    19   
# 23    29    31    37    41    43    47    53    59   
# 61    67    71    73    79    83    89    97    101 
# 103  107  109  113  127  131  137  139  149

prime=[]

for i in range(2,150):
    j=2
    for j in range(2,i):
        if(i%j==0):
            break
    else:
        prime.append(i)

#print(prime)
count=0
for num in prime:
    count+=1
    print(num,end="\t")
    if(count%9==0):
        print("")
    