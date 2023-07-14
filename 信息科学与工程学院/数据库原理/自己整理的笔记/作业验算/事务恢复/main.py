class task:
    num=0
    name='X'
    v1=0
    v2=0
    def __init__(self,num,name,v1,v2):
        self.num=num
        self.name=name
        self.v1=v1
        self.v2=v2
print("输入格式1 start\n1 X 0 2\n结束请输入0")
tasks=[]
arr=input('')
check_num=0
c=0
undo=set()
redo=set()
begin=set()
map={}
while(arr!='0'):
    inp=arr.split(' ')
    if(inp[0]) == 'check' or(inp[0]) == 'Check' or (inp[0]) == 'CHECK':
        tasks.append(task(0, 'check', 0, 0))
        check_num=c
    elif((inp[1])=='commit' or (inp[1])=='Commit' or (inp[1])=='COMMIT'):
        tasks.append(task(int(inp[0]),'commit',0,0))
    elif (inp[1])=='start' or (inp[1])=='Start' or (inp[1])=='START':
        tasks.append(task(int(inp[0]),'start',0,0))
    else:
        tasks.append(task(int(inp[0]),inp[1],int(inp[2]),int(inp[3])))
    arr = input('')
    c+=1


for i in range(0,check_num):
    if(tasks[i].name=='start'):undo.add(tasks[i].num)
    if(tasks[i].name=='commit'):undo.discard(tasks[i].num)
print("(1)分析阶段")
print("                   UNDO-Set      REDO-set")
print("<Checkpoint>       ",undo)
begin=undo.copy()
for i in range(check_num+1,len(tasks)):
    if(tasks[i].name=='start'):
        undo.add(tasks[i].num)
        print("<T"+str(tasks[i].num)+",START>       ",undo,"      ",redo)
    if(tasks[i].name=='commit'):
        redo.add(tasks[i].num)
        undo.discard(tasks[i].num)
        print("<T"+str(tasks[i].num)+",COMMIT>       ", undo, "      ", redo)
print("(2)撤销阶段")
for i in range(len(tasks)-1,check_num+1,-1):
    if(tasks[i].num in undo and tasks[i].name!='start'and tasks[i].name!='commit'):
        print("<T"+str(tasks[i].num)+","+str(tasks[i].name)+","+str(tasks[i].v1)+","+str(tasks[i].v2)+">："+str(tasks[i].name)+"="+str(tasks[i].v1))
        map.update({tasks[i].name:tasks[i].v1})
print("其次，对于同时出现在UNDO-set与Checkpoint列表中的事务集T",begin.intersection(undo),",从最后一次检查点开始继续反向扫描日志至遇到这些事务的START止，\n对每一条属于T",begin.intersection(undo),"中事务的更新操作依次执行UNDO操作。撤销过程如下:")
for i in range(check_num-1,0,-1):
    if(tasks[i].num in begin.intersection(undo) and tasks[i].name!='start'and tasks[i].name!='commit'):
        print("<T"+str(tasks[i].num)+","+str(tasks[i].name)+","+str(tasks[i].v1)+","+str(tasks[i].v2)+">："+str(tasks[i].name)+"="+str(tasks[i].v1))
        map.update({tasks[i].name:tasks[i].v1})
print("撤销后的结果为：",map)
print("(3)重做阶段")
for i in range(check_num+1,len(tasks)-1):
    if(tasks[i].num in redo and tasks[i].name!='start'and tasks[i].name!='commit'):
        print("<T"+str(tasks[i].num)+","+str(tasks[i].name)+","+str(tasks[i].v1)+","+str(tasks[i].v2)+">："+str(tasks[i].name)+"="+str(tasks[i].v2))
        map.update({tasks[i].name:tasks[i].v2})
print("因此，最后的结果为：",map)

while(1):input()