 // bo2-2.cpp 带有头结点的单链表(存储结构由c2-2.h定义)的基本操作(12个)，
 // 包括算法2.8～2.10
 void InitList(LinkList &L)
 { // 操作结果：构造一个空的线性表L
   L=(LinkList)malloc(sizeof(LNode)); // 产生头结点，并使L指向此头结点
   if(!L) // 存储分配失败
     exit(OVERFLOW);
   L->next=NULL; // 头结点的指针域为空
 }

 void DestroyList(LinkList &L)
 { // 初始条件：线性表L已存在。操作结果：销毁线性表L
   LinkList q;
   while(L) // L指向结点(非空)
   { q=L->next; // q指向首元结点
     free(L); // 释放头结点
     L=q; // L指向原首元结点，现头结点
   }
 }

 void ClearList(LinkList L) // 不改变L
 { // 初始条件：线性表L已存在。操作结果：将L重置为空表
   LinkList p=L->next; // p指向第1个结点
   L->next=NULL; // 头结点指针域为空
   DestroyList(p); // 销毁p所指的单链表
 }

 Status ListEmpty(LinkList L)
 { // 初始条件：线性表L已存在。操作结果：若L为空表，则返回TRUE，否则返回FALSE
   if(L->next) // 非空
     return FALSE;
   else
     return TRUE;
 }

 int ListLength(LinkList L)
 { // 初始条件：线性表L已存在。操作结果：返回L中数据元素的个数
   int i=0; // 计数器初值为0
   LinkList p=L->next; // p指向第1个结点
   while(p) // 未到表尾
   { i++; // 计数器+1
     p=p->next; // p指向下一个结点
   }
   return i;
 }

 Status GetElem(LinkList L,int i,ElemType &e) // 算法2.8
 { // L为带头结点的单链表的头指针。当第i个元素存在时，其值赋给e并返回OK；否则返回ERROR
   int j=1; // 计数器初值为1
   LinkList p=L->next; // p指向第1个结点
   while(p&&j<i) // 顺指针向后查找，直到p指向第i个结点或p为空(第i个结点不存在)
   { j++; // 计数器+1
     p=p->next; // p指向下一个结点
   }
   if(!p||j>i) // 第i个结点不存在
     return ERROR;
   e=p->data; // 取第i个元素的值赋给e
   return OK;
 }

 int LocateElem(LinkList L,ElemType e,Status(*compare)(ElemType,ElemType))
 { // 初始条件：线性表L已存在，compare()是数据元素判定函数(满足为1，否则为0)
   // 操作结果：返回L中第1个与e满足关系compare()的数据元素的位序。
   //           若这样的数据元素不存在，则返回值为0
   int i=0; // 计数器初值为0
   LinkList p=L->next; // p指向第1个结点
   while(p) // 未到表尾
   { i++; // 计数器+1
     if(compare(p->data,e)) // 找到这样的数据元素
       return i; // 返回其位序
     p=p->next; // p指向下一个结点
   }
   return 0; // 满足关系的数据元素不存在
 }

 Status PriorElem(LinkList L,ElemType cur_e,ElemType &pre_e)
 { // 初始条件：线性表L已存在
   // 操作结果：若cur_e是L的数据元素，且不是第一个，则用pre_e返回它的前驱，返回OK，
   //           否则操作失败，pre_e无定义，返回ERROR
   LinkList q,p=L->next; // p指向第1个结点
   while(p->next) // p所指结点有后继
   { q=p->next; // q指向p的后继
     if(q->data==cur_e) // p的后继为cur_e
     { pre_e=p->data; // 将p所指元素的值赋给pre_e
       return OK; // 成功返回OK
     }
     p=q; // p的后继不为cur_e，p向后移
   }
   return ERROR; // 操作失败，返回ERROR
 }

 Status NextElem(LinkList L,ElemType cur_e,ElemType &next_e)
 { // 初始条件：线性表L已存在
   // 操作结果：若cur_e是L的数据元素，且不是最后一个，则用next_e返回它的后继，返回OK，
   //           否则操作失败，next_e无定义，返回ERROR
   LinkList p=L->next; // p指向第1个结点
   while(p->next) // p所指结点有后继
   { if(p->data==cur_e) // p所指结点的值为cur_e
     { next_e=p->next->data; // 将p所指结点的后继结点的值赋给next_e
       return OK; // 成功返回OK
     }
     p=p->next; // p指向下一个结点
   }
   return ERROR; // 操作失败，返回ERROR
 }

 Status ListInsert(LinkList L,int i,ElemType e) // 算法2.9。不改变L
 { // 在带头结点的单链线性表L中第i个位置之前插入元素e
   int j=0; // 计数器初值为0
   LinkList s,p=L; // p指向头结点
   while(p&&j<i-1) // 寻找第i-1个结点
   { j++; // 计数器+1
     p=p->next; // p指向下一个结点
   }
   if(!p||j>i-1) // i小于1或者大于表长
     return ERROR; // 插入失败
   s=(LinkList)malloc(sizeof(LNode)); // 生成新结点，以下将其插入L中
   s->data=e; // 将e赋给新结点
   s->next=p->next; // 新结点指向原第i个结点
   p->next=s; // 原第i-1个结点指向新结点
   return OK; // 插入成功
 }

 Status ListDelete(LinkList L,int i,ElemType &e) // 算法2.10。不改变L
 { // 在带头结点的单链线性表L中，删除第i个元素，并由e返回其值
   int j=0; // 计数器初值为0
   LinkList q,p=L; // p指向头结点
   while(p->next&&j<i-1) // 寻找第i个结点，并令p指向其前驱
   { j++; // 计数器+1
     p=p->next; // p指向下一个结点
   }
   if(!p->next||j>i-1) // 删除位置不合理
     return ERROR; // 删除失败
   q=p->next; // q指向待删除结点
   p->next=q->next; // 待删结点的前驱指向待删结点的后继
   e=q->data; // 将待删结点的值赋给e
   free(q); // 释放待删结点
   return OK; // 删除成功
 }

 void ListTraverse(LinkList L,void(*visit)(ElemType))
 // visit的形参类型为ElemType，与bo2-1.cpp中相应函数的形参类型ElemType&不同
 { // 初始条件：线性表L已存在。操作结果：依次对L的每个数据元素调用函数visit()
   LinkList p=L->next; // p指向第1个结点
   while(p) // p所指结点存在
   { visit(p->data); // 对p所指结点调用函数visit()
     p=p->next; // p指向下一个结点
   }
   printf("\n");
 }
