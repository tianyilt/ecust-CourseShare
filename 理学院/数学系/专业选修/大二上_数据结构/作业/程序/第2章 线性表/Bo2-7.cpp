 // bo2-7.cpp 带头结点的双向循环链表(存储结构由c2-4.h定义)的基本操作(14个)
 // 包括算法2.18，2.19
 void InitList(DuLinkList &L)
 { // 产生空的双向循环链表L
   L=(DuLinkList)malloc(sizeof(DuLNode));
   if(L)
     L->next=L->prior=L;
   else
     exit(OVERFLOW);
 }

 void ClearList(DuLinkList L) // 不改变L
 { // 初始条件：L已存在。操作结果：将L重置为空表
   DuLinkList p=L->next; // p指向第1个结点
   while(p!=L) // p未指向头结点
   { p=p->next; // p指向下一个结点
     free(p->prior); // 释放p的前驱结点
   }
   L->next=L->prior=L; // 头结点的两个指针域均指向自身
 }

 void DestroyList(DuLinkList &L)
 { // 操作结果：销毁双向循环链表L
   ClearList(L); // 将L重置为空表
   free(L); // 释放头结点
   L=NULL; // L不指向任何存储单元
 }

 Status ListEmpty(DuLinkList L)
 { // 初始条件：线性表L已存在。操作结果：若L为空表，则返回TRUE，否则返回FALSE
   if(L->next==L&&L->prior==L)
     return TRUE;
   else
     return FALSE;
 }

 int ListLength(DuLinkList L)
 { // 初始条件：L已存在。操作结果：返回L中数据元素个数
   int i=0; // 计数器初值为0
   DuLinkList p=L->next; // p指向第1个结点
   while(p!=L) // p未指向头结点
   { i++; // 计数器+1
     p=p->next; // p指向下一个结点
   }
   return i;
 }

 Status GetElem(DuLinkList L,int i,ElemType &e)
 { // 当第i个元素存在时，其值赋给e并返回OK；否则返回ERROR
   int j=1; // 计数器初值为1
   DuLinkList p=L->next; // p指向第1个结点
   while(p!=L&&j<i) // 顺指针向后查找，直到p指向第i个元素或p指向头结点
   { j++; // 计数器+1
     p=p->next; // p指向下一个结点
   }
   if(p==L||j>i) // 第i个元素不存在
     return ERROR; // 查找失败
   e=p->data; // 取第i个元素赋给e
   return OK; // 查找成功
 }

 int LocateElem(DuLinkList L,ElemType e,Status(*compare)(ElemType,ElemType))
 { // 初始条件：L已存在，compare()是数据元素判定函数
   // 操作结果：返回L中第1个与e满足关系compare()的数据元素的位序。
   //           若这样的数据元素不存在，则返回值为0
   int i=0; // 计数器初值为0
   DuLinkList p=L->next; // p指向第1个元素
   while(p!=L) // p未指向头结点
   { i++; // 计数器+1
     if(compare(p->data,e)) // 找到这样的数据元素
       return i; // 返回其位序
     p=p->next; // p指向下一个结点
   }
   return 0; // 满足关系的数据元素不存在
 }

 Status PriorElem(DuLinkList L,ElemType cur_e,ElemType &pre_e)
 { // 操作结果：若cur_e是L的数据元素，且不是第一个，则用pre_e返回它的前驱，返回OK；
   //           否则操作失败，pre_e无定义，返回ERROR
   DuLinkList p=L->next->next; // p指向第2个元素
   while(p!=L) // p未指向头结点
   { if(p->data==cur_e) // p指向值为cur_e的结点
     { pre_e=p->prior->data; // 将p的前驱结点的值赋给pre_e
       return OK; // 成功返回OK
     }
     p=p->next; // p指向下一个结点
   }
   return ERROR; // 操作失败，返回ERROR
 }

 Status NextElem(DuLinkList L,ElemType cur_e,ElemType &next_e)
 { // 操作结果：若cur_e是L的数据元素，且不是最后一个，则用next_e返回它的后继，返回OK，
   //           否则操作失败，next_e无定义，返回ERROR
   DuLinkList p=L->next->next; // p指向第2个元素
   while(p!=L) // p未指向头结点
   { if(p->prior->data==cur_e) // p所指结点的前驱的值为cur_e
     { next_e=p->data; // 将p所指结点(cur_e的后继)的值赋给next_e
       return OK; // 成功返回OK
     }
     p=p->next; // p指向下一个结点
   }
   return ERROR; // 操作失败，返回ERROR
 }

 DuLinkList GetElemP(DuLinkList L,int i) // 新增
 { // 在双向链表L中返回第i个元素的地址。i为0，返回头结点的地址。若第i个元素不存在，
   // 返回NULL(算法2.18、2.19要调用的函数)
   int j;
   DuLinkList p=L; // p指向头结点
   if(i<0||i>ListLength(L)) // i值不合法
     return NULL;
   for(j=1;j<=i;j++) // p指向第i个结点
     p=p->next; // p指向下一个结点
   return p;
 }

 Status ListInsert(DuLinkList L,int i,ElemType e)
 { // 在带头结点的双链循环线性表L中第i个位置之前插入元素e，i的合法值为1≤i≤表长+1
   // 改进算法2.18，否则无法在第表长+1个结点之前插入元素
   DuLinkList p,s;
   if(i<1||i>ListLength(L)+1) // i值不合法
     return ERROR; // 失败返回ERROR
   p=GetElemP(L,i-1); // 在L中确定第i个结点前驱的位置指针p
   if(!p) // p=NULL，即第i个结点的前驱不存在(设头结点为第1个结点的前驱)
     return ERROR; // 失败返回ERROR
   s=(DuLinkList)malloc(sizeof(DuLNode)); // 生成新结点
   if(!s)
     return ERROR; // 生成新结点失败返回ERROR
   s->data=e; // 将e赋给新结点
   s->prior=p; // 新结点的前驱为第i-1个结点
   s->next=p->next; // 新结点的后继为第i个结点
   p->next->prior=s; // 第i个结点的前驱指向新结点
   p->next=s; // 第i-1个结点的后继指向新结点
   return OK; // 成功返回OK
 }

 Status ListDelete(DuLinkList L,int i,ElemType &e) // 算法2.19
 { // 删除带头结点的双链循环线性表L的第i个元素，i的合法值为1≤i≤表长
   DuLinkList p;
   if(i<1) // i值不合法
     return ERROR; // 删除失败
   p=GetElemP(L,i); // 在L中确定第i个元素的位置指针p
   if(!p) // p=NULL，即第i个元素不存在
     return ERROR; // 删除失败
   e=p->data; // 将第i个元素的值赋给e
   p->prior->next=p->next; // 第i-1个结点的后继指向原第i+1个结点
   p->next->prior=p->prior; // 原第i+1个结点的前驱指向第i-1个结点
   free(p); // 释放第i个结点
   return OK; // 删除成功
 }

 void ListTraverse(DuLinkList L,void(*visit)(ElemType))
 { // 由双链循环线性表L的头结点出发，正序对每个数据元素调用函数visit()
   DuLinkList p=L->next; // p指向首元结点
   while(p!=L) // p未指向头结点
   { visit(p->data); // 对p所指结点调用函数visit()
     p=p->next; // p指向下一个结点
   }
   printf("\n");
 }

 void ListTraverseBack(DuLinkList L,void(*visit)(ElemType))
 { // 由双链循环线性表L的头结点出发，逆序对每个数据元素调用函数visit()。新增
   DuLinkList p=L->prior; // p指向尾结点
   while(p!=L) // p未指向头结点
   { visit(p->data); // 对p所指结点调用函数visit()
     p=p->prior; // p指向前一个结点
   }
   printf("\n");
 }
