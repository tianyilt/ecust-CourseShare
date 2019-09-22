 // bo3-2.cpp 链队列(存储结构由c3-2.h定义)的基本操作(9个)
 void InitQueue(LinkQueue &Q)
 { // 构造一个空队列Q。在教科书第62页
   Q.front=Q.rear=(QueuePtr)malloc(sizeof(QNode)); // 生成头结点
   if(!Q.front) // 生成头结点失败
     exit(OVERFLOW);
   Q.front->next=NULL; // 头结点的next域为空
 }

 void DestroyQueue(LinkQueue &Q)
 { // 销毁队列Q(无论空否均可)。在教科书第62页
  while(Q.front) // Q.front不为空
  { Q.rear=Q.front->next; // Q.rear指向Q.front的下一个结点
    free(Q.front); // 释放Q.front所指结点
    Q.front=Q.rear; // Q.front指向Q.front的下一个结点
   }
 }

 void ClearQueue(LinkQueue &Q)
 { // 将队列Q清为空队列
   DestroyQueue(Q); // 销毁队列Q
   InitQueue(Q); // 重新构造空队列Q
 }

 Status QueueEmpty(LinkQueue Q)
 { // 若队列Q为空队列，则返回TRUE；否则返回FALSE
   if(Q.front->next==NULL)
     return TRUE;
   else
     return FALSE;
 }

 int QueueLength(LinkQueue Q)
 { // 求队列Q的长度
   int i=0; // 计数器，初值为0
   QueuePtr p=Q.front; // p指向头结点
   while(Q.rear!=p) // p所指不是尾结点
   { i++; // 计数器+1
     p=p->next; // p指向下一个结点
   }
   return i;
 }

 Status GetHead(LinkQueue Q,QElemType &e)
 { // 若队列Q不空，则用e返回Q的队头元素，并返回OK；否则返回ERROR
   QueuePtr p;
   if(Q.front==Q.rear) // 队列空
     return ERROR;
   p=Q.front->next; // p指向队头结点
   e=p->data; // 将队头元素的值赋给e
   return OK;
 }

 void EnQueue(LinkQueue &Q,QElemType e)
 { // 插入元素e为队列Q的新的队尾元素。在教科书第62页
   QueuePtr p;
   p=(QueuePtr)malloc(sizeof(QNode)); // 动态生成新结点
   if(!p)
     exit(OVERFLOW); // 失败则退出
   p->data=e; // 将值e赋给新结点
   p->next=NULL; // 新结点的指针域为空
   Q.rear->next=p; // 原队尾结点的指针指向新结点
   Q.rear=p; // 尾指针指向新结点
 }

 Status DeQueue(LinkQueue &Q,QElemType &e)
 { // 若队列Q不空，删除Q的队头元素，用e返回其值，
   // 并返回OK；否则返回ERROR。在教科书第62页
   QueuePtr p;
   if(Q.front==Q.rear) // 队列空
     return ERROR;
   p=Q.front->next; // p指向队头结点
   e=p->data; // 将队头元素的值赋给e
   Q.front->next=p->next; // 头结点指向下一个结点
   if(Q.rear==p) // 删除的是队尾结点
     Q.rear=Q.front; // 修改队尾指针指向头结点(空队列)
   free(p); // 释放队头结点
   return OK;
 }

 void QueueTraverse(LinkQueue Q,void(*visit)(QElemType))
 { // 从队头到队尾依次对队列Q中每个元素调用函数visit()
   QueuePtr p=Q.front->next; // p指向队头结点
   while(p) // p指向结点
   { visit(p->data); // 对p所指元素调用visit()
     p=p->next; // p指向下一个结点
   }
   printf("\n");
 }
