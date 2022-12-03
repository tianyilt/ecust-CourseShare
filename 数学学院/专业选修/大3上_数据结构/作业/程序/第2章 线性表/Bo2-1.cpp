 // bo2-1.cpp 顺序存储的线性表(存储结构由c2-1.h定义)的基本操作(12个)，包括算法2.3～2.6
 void InitList(SqList &L) // 算法2.3
 { // 操作结果：构造一个空的顺序线性表L
   L.elem=(ElemType*)malloc(LIST_INIT_SIZE*sizeof(ElemType));
   if(!L.elem) // 存储分配失败
     exit(OVERFLOW);
   L.length=0; // 空表长度为0
   L.listsize=LIST_INIT_SIZE; // 初始存储容量
 }

 void DestroyList(SqList &L)
 { // 初始条件：顺序线性表L已存在。操作结果：销毁顺序线性表L
   free(L.elem); // 释放L.elem所指的存储空间
   L.elem=NULL; // L.elem不再指向任何存储单元
   L.length=0;
   L.listsize=0;
 }

 void ClearList(SqList &L)
 { // 初始条件：顺序线性表L已存在。操作结果：将L重置为空表
   L.length=0;
 }

 Status ListEmpty(SqList L)
 { // 初始条件：顺序线性表L已存在。
   // 操作结果：若L为空表，则返回TRUE；否则返回FALSE
   if(L.length==0)
     return TRUE;
   else
     return FALSE;
 }

 int ListLength(SqList L)
 { // 初始条件：顺序线性表L已存在。操作结果：返回L中数据元素的个数
   return L.length;
 }

 Status GetElem(SqList L,int i,ElemType &e)
 { // 初始条件：顺序线性表L已存在，1≤i≤ListLength(L)
   // 操作结果：用e返回L中第i个数据元素的值
   if(i<1||i>L.length) // i不在表L的范围之内
     return ERROR;
   e=*(L.elem+i-1); // 将表L的第i个元素的值赋给e
   return OK;
 }

 int LocateElem(SqList L,ElemType e,Status(*compare)(ElemType,ElemType))
 { // 初始条件：顺序线性表L已存在，compare()是数据元素判定函数(满足为1，否则为0)
   // 操作结果：返回L中第1个与e满足关系compare()的数据元素的位序。
   //           若这样的数据元素不存在，则返回值为0。算法2.6
   int i=1; // i的初值为第1个元素的位序
   ElemType *p=L.elem; // p的初值为第1个元素的存储位置
   while(i<=L.length&&!compare(*p++,e)) // i未超出表的范围且未找到满足关系的数据元素
     ++i; // 继续向后找
   if(i<=L.length) // 找到满足关系的数据元素
     return i; // 返回其位序
   else // 未找到满足关系的数据元素
     return 0;
 }

 Status PriorElem(SqList L,ElemType cur_e,ElemType &pre_e)
 { // 初始条件：顺序线性表L已存在
   // 操作结果：若cur_e是L的数据元素，且不是第一个，则用pre_e返回它的前驱；
   //           否则操作失败，pre_e无定义
   int i=2; // 从第2个元素开始
   ElemType *p=L.elem+1; // p指向第2个元素
   while(i<=L.length&&*p!=cur_e) // i未超出表的范围且未找到值为cur_e的元素
   { p++; // p指向下一个元素
     i++; // 计数加1
   }
   if(i>L.length) // 到表结束处还未找到值为cur_e的元素
     return ERROR; // 操作失败
   else // 找到值为cur_e的元素，并由p指向其
   { pre_e=*--p; // p指向前一个元素(cur_e的前驱)，将所指元素的值赋给pre_e
     return OK; // 操作成功
   }
 }

 Status NextElem(SqList L,ElemType cur_e,ElemType &next_e)
 { // 初始条件：顺序线性表L已存在
   // 操作结果：若cur_e是L的数据元素，且不是最后一个，则用next_e返回它的后继，
   //           否则操作失败，next_e无定义
   int i=1; // 从第1个元素开始
   ElemType *p=L.elem; // p指向第1个元素
   while(i<L.length&&*p!=cur_e) // i未到表尾且未找到值为cur_e的元素
   { p++; // p指向下一个元素
     i++; // 计数加1
   }
   if(i==L.length) // 到表尾的前一个元素还未找到值为cur_e的元素
     return ERROR; // 操作失败
   else // 找到值为cur_e的元素，并由p指向其
   { next_e=*++p; // p指向下一个元素(cur_e的后继)，将所指元素的值赋给next _e
     return OK; // 操作成功
   }
 }

 Status ListInsert(SqList &L,int i,ElemType e) // 算法2.4
 { // 初始条件：顺序线性表L已存在，1≤i≤ListLength(L)+1
   // 操作结果：在L中第i个位置之前插入新的数据元素e，L的长度加1
   ElemType *newbase,*q,*p;
   if(i<1||i>L.length+1) // i值不合法
     return ERROR;
   if(L.length==L.listsize) // 当前存储空间已满，增加分配，修改
   { newbase=(ElemType*)realloc(L.elem,(L.listsize+LIST_INCREMENT)*sizeof(ElemType));
     if(!newbase) // 存储分配失败
       exit(OVERFLOW);
     L.elem=newbase; // 新基址赋给L.elem
     L.listsize+=LIST_INCREMENT; // 增加存储容量
   }
   q=L.elem+i-1; // q为插入位置
   for(p=L.elem+L.length-1;p>=q;--p) // 插入位置及之后的元素右移(由表尾元素开始移)
     *(p+1)=*p;
   *q=e; // 插入e
   ++L.length; // 表长增1
   return OK;
 }

 Status ListDelete(SqList &L,int i,ElemType &e) // 算法2.5
 { // 初始条件：顺序线性表L已存在，1≤i≤ListLength(L)
   // 操作结果：删除L的第i个数据元素，并用e返回其值，L的长度减1
   ElemType *p,*q;
   if(i<1||i>L.length) // i值不合法
     return ERROR;
   p=L.elem+i-1; // p为被删除元素的位置
   e=*p; // 被删除元素的值赋给e
   q=L.elem+L.length-1; // q为表尾元素的位置
   for(++p;p<=q;++p) // 被删除元素之后的元素左移(由被删除元素的后继元素开始移)
     *(p-1)=*p;
   L.length--; // 表长减1
   return OK;
 }

 void ListTraverse(SqList L,void(*visit)(ElemType&))
 { // 初始条件：顺序线性表L已存在
   // 操作结果：依次对L的每个数据元素调用函数visit()
   //           visit()的形参加'&'，表明可通过调用visit()改变元素的值
   ElemType *p=L.elem; // p指向第1个元素
   int i;
   for(i=1;i<=L.length;i++) // 从表L的第1个元素到最后1个元素
     visit(*p++); // 对每个数据元素调用visit()
   printf("\n");
 }
