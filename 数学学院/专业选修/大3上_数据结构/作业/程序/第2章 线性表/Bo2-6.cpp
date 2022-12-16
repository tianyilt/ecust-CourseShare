 // bo2-6.cpp 设立尾指针的单循环链表(存储结构由c2-2.h定义)的12个基本操作
 void InitList(LinkList &L)
 { // 操作结果：构造一个空的线性表L
   L=(LinkList)malloc(sizeof(LNode)); // 产生头结点，并使L指向此头结点
   if(!L) // 存储分配失败
     exit(OVERFLOW);
   L->next=L; // 头结点的指针域指向头结点
 }

 void ClearList(LinkList &L) // 改变L
 { // 初始条件：线性表L已存在。操作结果：将L重置为空表
   LinkList p,q;
   L=L->next; // L指向头结点
   p=L->next; // p指向第1个结点
   while(p!=L) // 未到表尾
   { q=p->next; // q指向p的后继结点
     free(p); // 释放p所指结点
     p=q; // p指向q所指结点
   }
   L->next=L; // 头结点指针域指向自身(头结点)
 }

 void DestroyList(LinkList &L)
 { // 操作结果：销毁线性表L
   ClearList(L); // 将表L重置为空表
   free(L); // 释放L所指结点(头结点)
   L=NULL; // L不指向任何存储单元
 }

 Status ListEmpty(LinkList L)
 { // 初始条件：线性表L已存在。操作结果：若L为空表，则返回TRUE，否则返回FALSE
   if(L->next==L) // 空
     return TRUE;
   else
     return FALSE;
 }

 int ListLength(LinkList L)
 { // 初始条件：L已存在。操作结果：返回L中数据元素个数
   int i=0;
   LinkList p=L->next; // p指向头结点
   while(p!=L) // 未到表尾
   { i++; // 计数器+1
     p=p->next; // p指向下一个结点
   }
   return i;
 }

 Status GetElem(LinkList L,int i,ElemType &e)
 { // 当第i个元素存在时，其值赋给e并返回OK，否则返回ERROR
   int j=1; // 初始化，j为计数器，初值为1
   LinkList p=L->next->next; // p指向第1个结点
   if(i<=0||i>ListLength(L)) // 第i个元素不存在
     return ERROR;
   while(j<i) // 顺指针向后查找，直到p指向第i个元素
   { j++; // 计数器+1
     p=p->next; // p指向下一个结点
   }
   e=p->data; // 第i个元素赋给e
   return OK;
 }

 int LocateElem(LinkList L,ElemType e,Status(*compare)(ElemType,ElemType))
 { // 初始条件：线性表L已存在，compare()是数据元素判定函数
   // 操作结果：返回L中第1个与e满足关系compare()的数据元素的位序。
   //           若这样的数据元素不存在，则返回值为0
   int i=0; // 计数器初值为0
   LinkList p=L->next->next; // p指向第1个结点
   while(p!=L->next) // p未指向头结点
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
   LinkList q,p=L->next->next; // p指向第1个结点
   q=p->next; // q指向p的后继
   while(q!=L->next) // p未到表尾(q未指向头结点)
   { if(q->data==cur_e) // p的后继为cur_e
     { pre_e=p->data; // 将p所指元素的值赋给pre_e
       return OK; // 成功返回OK
     }
     p=q; // p的后继不为cur_e，p向后移
     q=q->next; // q指向p的后继
   }
   return ERROR; // 操作失败，返回ERROR
 }

 Status NextElem(LinkList L,ElemType cur_e,ElemType &next_e)
 { // 初始条件：线性表L已存在
   // 操作结果：若cur_e是L的数据元素，且不是最后一个，则用next_e返回它的后继，返回OK，
   //           否则操作失败，next_e无定义，返回ERROR
   LinkList p=L->next->next; // p指向第1个结点
   while(p!=L) // p未到表尾
   { if(p->data==cur_e) // p所指结点的值为cur_e
     { next_e=p->next->data; // 将p所指结点的后继结点的值赋给next_e
       return OK; // 成功返回OK
     }
     p=p->next; // p指向下一个结点
   }
   return ERROR; // 操作失败，返回ERROR
 }

 Status ListInsert(LinkList &L,int i,ElemType e)
 { // 在L的第i个位置之前插入元素e(改变L)
   LinkList p=L->next,s; // p指向头结点
   int j=0; // 计数器初值为0
   if(i<=0||i>ListLength(L)+1) // i值不合法
     return ERROR; // 插入失败
   while(j<i-1) // 寻找第i-1个结点
   { j++; // 计数器+1
     p=p->next; // p指向下一个结点
   }
   s=(LinkList)malloc(sizeof(LNode)); // 生成新结点，以下将其插入L中
   s->data=e; // 将e赋给新结点
   s->next=p->next; // 新结点指向原第i个结点
   p->next=s; // 原第i-1个结点指向新结点
   if(p==L) // 插在表尾
     L=s; // L指向新的尾结点
   return OK; // 插入成功
 }

 Status ListDelete(LinkList &L,int i,ElemType &e)
 { // 删除L的第i个元素，并由e返回其值(改变L)
   LinkList q,p=L->next; // p指向头结点
   int j=0; // 计数器初值为0
   if(i<=0||i>ListLength(L)) // 第i个元素不存在
     return ERROR; // 删除失败
   while(j<i-1) // 寻找第i-1个结点
   { j++; // 计数器+1
     p=p->next; // p指向下一个结点
   }
   q=p->next; // q指向待删除结点，p的后继
   p->next=q->next; // 待删结点的前驱指向待删结点的后继
   e=q->data; // 将待删结点的值赋给e
   if(L==q) // 删除的是表尾元素
     L=p; // L指向新的表尾元素
   free(q); // 释放待删除结点
   return OK; // 删除成功
 }

 void ListTraverse(LinkList L,void(*vi)(ElemType))
 { // 初始条件：L已存在。操作结果：依次对L的每个数据元素调用函数vi()
   LinkList p=L->next->next; // p指向首元结点
   while(p!=L->next) // p不指向头结点
   { vi(p->data); // 对p所指结点调用函数vi()
     p=p->next; // p指向下一个结点
   }
   printf("\n");
 }
