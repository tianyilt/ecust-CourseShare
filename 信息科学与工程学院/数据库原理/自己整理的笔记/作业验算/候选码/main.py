def trans(x):
    res=list(x)
    res.sort()
    return res

def PowerSetsBinary(items):
  N = len(items)
  b=[]
  for i in range(2**N):
    zj =''
    for j in range(N):
      if(i >> j ) % 2 == 1:
        zj=zj+zj.join(items[j])
    b.append(zj)
  return b

def closure(r,f1,f2,input,pr):
    if(pr):print('步骤   FD         closure\n----------------------------\n1.      赋初值      ',trans(input))
    flag=1
    all=1
    while(flag):
        temp=input.copy()
        c=0
        for c in range(len(f1)):
            if(f1[c].issubset(input) and f2[c].issubset(input)==0):
                flag=1
                for i in f2[c]:
                    input.add(i)
                all+=1
                if(pr):print(all,'.',trans(f1[c]),'->',trans(f2[c]),'   ',trans(input))
                if(input==r):
                    break
        if(r==input or input==temp):
            flag=0
    if(pr):print('闭包为：',trans(input))
    return trans(input)

def houxuanma(r,f1,f2):
    res = []
    sub = PowerSetsBinary(list(r))
    for k in sub:
        if (k == ''): continue
        if (closure(r, f1, f2, set(k), False) == trans(r)):
            res.append(k)
    res.sort(key=lambda ele: len(ele))
    res2={res[0]}
    for i in range(1,len(res)):
        flag=0
        for k in range(0,i):
            if(set(res[k]).issubset(set(res[i]))):
                flag=1
        if(flag==0):res2.add(res[i])
    return res2

num=int(input("输入关系模式，函数依赖集，闭包 \nn个字母，并分别输入\n"))
in1=[]
in2=[]
input1=[]
input2=[]
inr={}
inputt={}
for i in range(num):
    t=input()
    in1.append(str(t))
inr=set(in1)
in1.clear()
num=int(input("n个函数依赖，并依次输入，格式AB-CD\n"))
for i in range(num):
    in1.clear()
    in2.clear()
    t=input()
    process=str(t).split("-")
    for k in process[0]:
        in1.append(str(k))
    for k in process[1]:
        in2.append(str(k))
    input1.append(set(in1))
    input2.append(set(in2))
#print(inr,input1,input2)
print('候选码：',houxuanma(inr,input1,input2))


for i in range(100):
    in1.clear()
    t = input("请输入要求的闭包\n")
    for k in t:
        in1.append(str(k))
    inputt = set(in1)
    closure(inr, input1, input2, inputt, True)
#r={'A','B','C','D','E','G'}
#f1 = [{'B'}, {'A'}, {'A', 'C'}, {'B', 'C'}]
#f2 = [{'A','D','E'}, {'B','E'}, {'G'}, {'D'}]
#inputt = {'A', 'C'}

#closure(r,f1,f2,inputt,True)
#print('候选码：',houxuanma(r,f1,f2))