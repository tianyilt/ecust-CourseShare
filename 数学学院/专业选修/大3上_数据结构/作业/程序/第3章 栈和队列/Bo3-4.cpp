 // bo3-4.cpp 循环队列(存储结构由c3-3.h定义)的基本操作(9个)
 void InitQueue(SqQueue &Q)
 { // 构造一个空队列Q。在教科书第64页
   Q.base=(QElemType*)malloc(MAX_QSIZE*sizeof(QElemType));
   if(!Q.base) // 存储分配失败
     exit(OVERFLOW);
   Q.front=Q.rear=0;
 }

 void DestroyQueue(SqQueue &Q)
 { // 销毁队列Q，Q不再存在
   if(Q.base) // 队列Q存在
     free(Q.base); // 释放Q.base所指的存储空间
   Q.base=NULL; // Q.base不指向任何存储单元
   Q.front=Q.rear=0;
 }

 void ClearQueue(SqQueue &Q)
 { // 将队列Q清为空队列
   Q.front=Q.rear=0;
 }

 Status QueueEmpty(SqQueue Q)
 { // 若队列Q为空队列，则返回TRUE；否则返回FALSE
   if(Q.front==Q.rear) // 队列空的标志
     return TRUE;
   else
     return FALSE;
 }

 Status GetHead(SqQueue Q,QElemType &e)
 { // 若队列Q不空，则用e返回Q的队头元素，并返回OK；否则返回ERROR
   if(Q.front==Q.rear) // 队列空
     return ERROR;
   e=Q.base[Q.front]; // 将队头元素的值赋给e
   return OK;
 }

 Status EnQueue(SqQueue &Q,QElemType e)
 { // 插入元素e为队列Q的新的队尾元素。在教科书第65页
   if((Q.rear+1)%MAX_QSIZE==Q.front) // 队列满
     return ERROR;
   Q.base[Q.rear]=e; // 将e插在队尾
   Q.rear=(Q.rear+1)%MAX_QSIZE; // 队尾指针+1后对MAX_QSIZE取余
   return OK;
 }

 int QueueLength(SqQueue Q)
 { // 返回队列Q的元素个数，即队列的长度。在教科书第64页
   return(Q.rear-Q.front+MAX_QSIZE)%MAX_QSIZE;
 }

 Status DeQueue(SqQueue &Q,QElemType &e) // 在教科书第65页
 { // 若队列Q不空，则删除Q的队头元素，用e返回其值，并返回OK；否则返回ERROR
   if(Q.front==Q.rear) // 队列空
     return ERROR;
   e=Q.base[Q.front]; // 将队头元素的值赋给e
   Q.front=(Q.front+1)%MAX_QSIZE; // 移动队头指针
   return OK;
 }

 void QueueTraverse(SqQueue Q,void(*visit)(QElemType))
 { // 从队头到队尾依次对队列Q中每个元素调用函数visit()
   int i=Q.front; // i最初指向队头元素
   while(i!=Q.rear) // i指向队列Q中的元素
   { visit(Q.base[i]); // 对i所指元素调用函数visit()
     i=(i+1)%MAX_QSIZE; // i指向下一个元素
   }
   printf("\n");
 }
