 // bo3-3.cpp 用单链表的基本操作实现链队列(存储结构由c3-2.h定义)的基本操作(9个)
 typedef QElemType ElemType; // 定义单链表的元素类型为队列的元素类型
 #define LinkList QueuePtr // 定义单链表的类型为相应的链队列的类型
 #define LNode QNode
 #include"bo2-2.cpp" // 单链表的基本操作
 void InitQueue(LinkQueue &Q)
 { // 构造一个空队列Q
  InitList(Q.front); // 以Q.front为头指针，构造空链表(调用单链表的基本操作)
  Q.rear=Q.front; // Q.rear与Q.front共同指向链队列的头结点
 }

 void DestroyQueue(LinkQueue &Q)
 { // 销毁队列Q(无论空否均可)
   DestroyList(Q.front); // 销毁Q.front为头指针的链表，且置Q.front为空
   Q.rear=Q.front; // 置Q.rear也为空
 }

 void ClearQueue(LinkQueue &Q)
 { // 将队列Q清为空队列
   ClearList(Q.front); // 清空以Q.front为头指针的链表，头结点的指针域为空
   Q.rear=Q.front; // Q.rear也指向空队列的头结点
 }

 Status QueueEmpty(LinkQueue Q)
 { // 若队列Q为空队列，则返回TRUE；否则返回FALSE
   return ListEmpty(Q.front); // 以Q.front为头指针的单链表为空，则队列Q为空，反之亦然
 }

 int QueueLength(LinkQueue Q)
 { // 求队列Q的长度
   return ListLength(Q.front); // 队列Q的长度即为以Q.front为头指针的单链表的长度
 }

 Status GetHead(LinkQueue Q,QElemType &e)
 { // 若队列Q不空，则用e返回Q的队头元素，并返回OK；否则返回ERROR
   return GetElem(Q.front,1,e); // 队头元素即为以Q.front为头指针的单链表的第1个元素
 }

 void EnQueue(LinkQueue &Q,QElemType e)
 { // 插入元素e为队列Q的新的队尾元素
   ListInsert(Q.front,ListLength(Q.front)+1,e); // 在最后一个元素之后插入e
 }

 Status DeQueue(LinkQueue &Q,QElemType &e)
 { // 若队列Q不空，删除Q的队头元素，用e返回其值，并返回OK；否则返回ERROR
   if(Q.front->next==Q.rear) // 队列仅有1个元素(删除的也是队尾元素)
     Q.rear=Q.front; // 令队尾指针指向头结点
   return ListDelete(Q.front,1,e); // 删除以Q.front为头指针的单链表的第1个元素
 }

 void QueueTraverse(LinkQueue Q,void(*visit)(QElemType))
 { // 从队头到队尾依次对队列Q中每个元素调用函数visit()
   ListTraverse(Q.front,visit); // 依次对以Q.front为头指针的单链表的元素调用visit()
 }
