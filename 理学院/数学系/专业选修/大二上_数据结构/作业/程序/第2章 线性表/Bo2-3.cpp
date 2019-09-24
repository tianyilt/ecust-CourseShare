 // bo2-3.cpp 不设头结点的单链表(存储结构由c2-2.h定义)的部分基本操作(9个)
 #define DestroyList ClearList // DestroyList()和ClearList()的操作是一样的
 void InitList(LinkList &L)
 { // 操作结果：构造一个空的线性表L
   L=NULL; // 指针为空
 }

 void ClearList(LinkList &L)
 { // 初始条件：线性表L已存在。操作结果：将L重置为空表
   LinkList p;
   while(L) // L不空
   { p=L; // p指向首元结点
     L=L->next; // L指向第2个结点(新首元结点)
     free(p); // 释放首元结点
   }
 }

 Status ListEmpty(LinkList L)
 { // 初始条件：线性表L已存在。操作结果：若L为空表，则返回TRUE，否则返回FALSE
   if(L)
     return FALSE;
   else
     return TRUE;
 }

 int ListLength(LinkList L)
 { // 初始条件：线性表L已存在。操作结果：返回L中数据元素的个数
   int i=0; // 计数器初值为0
   LinkList p=L; // p指向第1个结点
   while(p) // p指向结点(未到表尾)
   { i++; // 计数器+1
     p=p->next; // p指向下一个结点
   }
   return i;
 }

 Status GetElem(LinkList L,int i,ElemType &e)
 { // L为不设头结点的单链表的头指针。当第i个元素存在时，其值赋给e并返回OK，
   // 否则返回ERROR
   int j=1; // 计数器初值为1
   LinkList p=L; // p指向第1个结点
   if(i<1) // i值不合法
     return ERROR;
   while(j<i&&p) // 未到第i个元素，也未到表尾
   { j++; // 计数器+1
     p=p->next; // p指向下一个结点
   }
   if(j==i&&p) // 存在第i个元素
   { e=p->data; // 取第i个元素的值赋给e
     return OK; // 成功返回OK
   }
   return ERROR; // 不存在第i个元素，失败返回ERROR
 }

 int LocateElem(LinkList L,ElemType e,Status(*compare)(ElemType,ElemType))
 { // 初始条件：线性表L已存在，compare()是数据元素判定函数(满足为1，否则为0)
   // 操作结果：返回L中第1个与e满足关系compare()的数据元素的位序。
   //           若这样的数据元素不存在，则返回值为0
   int i=0; // 计数器初值为0
   LinkList p=L; // p指向第1个结点
   while(p) // 未到表尾
   { i++; // 计数器+1
     if(compare(p->data,e)) // 找到这样的数据元素
       return i; // 返回其位序
     p=p->next; // p指向下一个结点
   }
   return 0; // 满足关系的数据元素不存在
 }

 Status ListInsert(LinkList &L,int i,ElemType e)
 { // 在不设头结点的单链线性表L中第i个位置之前插入元素e
   int j=1; // 计数器初值为1
   LinkList s,p=L; // p指向第1个结点
   if(i<1) // i值不合法
     return ERROR;
   s=(LinkList)malloc(sizeof(LNode)); // 生成新结点，以下将其插入L中
   s->data=e; // 给s的data域赋值e
   if(i==1) // 插在表头
   { s->next=L; // 新结点指向原第1个结点
     L=s; // L指向新结点(改变L)
   }
   else
   { // 插在表的其余处
     while(p&&j<i-1) // 寻找第i-1个结点
     { j++; // 计数器+1
       p=p->next; // p指向下一个结点
     }
     if(!p) // i大于表长+1
       return ERROR; // 插入失败
     s->next=p->next; // 新结点指向原第i个结点
     p->next=s; // 原第i-1个结点指向新结点
   }
   return OK; // 插入成功
 }

 Status ListDelete(LinkList &L,int i,ElemType &e)
 { // 在不设头结点的单链线性表L中，删除第i个元素，并由e返回其值
   int j=1; // 计数器初值为1
   LinkList q,p=L; // p指向第1个结点
   if(!L) // 表L空
     return ERROR; // 删除失败
   else if(i==1) // 删除第1个结点
   { L=p->next; // L由第2个结点开始(改变L)
     e=p->data; // 将待删结点的值赋给e
     free(p); // 删除并释放第1个结点
   }
   else
   { while(p->next&&j<i-1) // 寻找第i个结点，并令p指向其前驱
     { j++; // 计数器+1
       p=p->next; // p指向下一个结点
     }
     if(!p->next||j>i-1) // 删除位置不合理
       return ERROR; // 删除失败
     q=p->next; // q指向待删除结点
     p->next=q->next; // 待删结点的前驱指向待删结点的后继
     e=q->data; // 将待删结点的值赋给e
     free(q); // 释放待删结点
   }
   return OK; // 删除成功
 }

 void ListTraverse(LinkList L,void(*vi)(ElemType))
 { // 初始条件：线性表L已存在。操作结果：依次对L的每个数据元素调用函数vi()
   LinkList p=L; // p指向第1个结点
   while(p) // p所指结点存在
   { vi(p->data); // 对p所指结点调用函数vi()
     p=p->next; // p指向下一个结点
   }
   printf("\n");
 }
