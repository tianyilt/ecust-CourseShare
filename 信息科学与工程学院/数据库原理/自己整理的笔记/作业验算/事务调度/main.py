class node:
    rw='R'
    num=0
    un='X'
    def __init__(self,str):
        self.rw=str[0]
        self.num=int(str[1])
        self.un=str[2]
while(1):
    maxn=0
    n=int(input('输入个数，之后并依次输入并发调度指令（R1X）\n'))
    a=[]
    for i in range(n):
        str=input()
        a.append(node(str))
        maxn=max(maxn,int(str[1]))
    res = [[0,0,0,0,0],[0,0,0,0,0],[0,0,0,0,0],[0,0,0,0,0],[0,0,0,0,0]]
    for i in range(n):
        for j in range(i+1,n):
            if(a[i].num!=a[j].num and a[i].un==a[j].un and (a[i].rw == 'W' or a[j].rw=='W') ):
                res[a[i].num][a[j].num]=1
    for i in range(5):
        for j in range(5):
            if(res[i][j]==1):
                print(i,"->",j)