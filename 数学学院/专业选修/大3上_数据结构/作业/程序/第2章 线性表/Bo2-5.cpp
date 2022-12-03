 // bo2-5.cpp 静态链表(数据结构由c2-3.h定义)的基本操作(13个)
 // 包括算法2.13、2.15和2.16
 #define DestroyList ClearList // DestroyList()和ClearList()的操作是一样的
 int Malloc(SLinkList space) // 算法2.15
 { // 若备用链表非空，则返回分配的结点下标(备用链表的第1个结点)，否则返回0
   int i=space[0].cur; // 备用链表第1个结点的位置
   if(i) // 备用链表非空
     space[0].cur=space[i].cur; // 备用链表的头结点指向原备用链表的第2个结点
   return i; // 返回新开辟结点的坐标
 }

 void Free(SLinkList space,int k) // 算法2.16
 { // 将下标为k的空闲结点回收到备用链表中(成为备用链表的第1个结点)
   space[k].cur=space[0].cur; // 回收结点的“游标”指向备用链表的第1个结点
   space[0].cur=k; // 备用链表的头结点指向新回收的结点
 }

 void InitList(SLinkList L)
 { // 构造一个空的链表L，表头为L的最后一个单元L[MAX_SIZE-1]，其余单元链成
   // 一个备用链表，表头为L的第一个单元L[0]，“0”表示空指针
   int i;
   L[MAX_SIZE-1].cur=0; // L的最后一个单元为空链表的表头
   for(i=0;i<MAX_SIZE-2;i++) // 将其余单元链接成以L[0]为表头的备用链表
     L[i].cur=i+1;
   L[MAX_SIZE-2].cur=0;
 }

 void ClearList(SLinkList L)
 { // 初始条件：线性表L已存在。操作结果：将L重置为空表
   int j,k,i=L[MAX_SIZE-1].cur; // i指示链表第1个结点的位序
   L[MAX_SIZE-1].cur=0; // 链表空
   k=L[0].cur; // 备用链表第1个结点的位置
   L[0].cur=i; // 把链表的结点连到备用链表的表头
   while(i) // 未到链表尾
   { j=i; // j指示当前结点的位序
     i=L[i].cur; // i指向下一个结点的位序
   }
   L[j].cur=k; // 备用链表的第1个结点接到链表的尾部
 }

 Status ListEmpty(SLinkList L)
 { // 若L是空表，返回TRUE，否则返回FALSE
   if(L[MAX_SIZE-1].cur==0) // 空表(表头结点的cur域为0)
     return TRUE;
   else
     return FALSE;
 }

 int ListLength(SLinkList L)
 { // 返回L中数据元素个数
   int j=0,i=L[MAX_SIZE-1].cur; // i指示链表的第1个结点的位序
   while(i) // 未到静态链表尾
   { i=L[i].cur; // i指向下一个结点
     j++; // 计数器+1
   }
   return j;
 }

 Status GetElem(SLinkList L,int i,ElemType &e)
 { // 用e返回L中第i个元素的值
   int m,k=MAX_SIZE-1; // k指示表头结点的位序
   if(i<1||i>ListLength(L)) // 不存在第i个元素
     return ERROR;
   for(m=1;m<=i;m++) // k向后移动到第i个元素处
     k=L[k].cur; // 指向下一个元素
   e=L[k].data; // 将第i个元素的值赋给e
   return OK;
 }

 int LocateElem(SLinkList L,ElemType e) // 算法2.13(有改动)
 { // 在静态单链线性表L中查找第1个值为e的元素。若找到，则返回它在L中的位序，否则返回0
   // (与其他LocateElem()的定义不同)
   int i=L[MAX_SIZE-1].cur; // i指示表中第1个结点的位序
   while(i&&L[i].data!=e) // 在表中顺链查找(e不能是字符串)，找到或已到表尾，结束循环
     i=L[i].cur; // 指向下一个元素
   return i;
 }

 Status PriorElem(SLinkList L,ElemType cur_e,ElemType &pre_e)
 { // 初始条件：线性表L已存在
   // 操作结果：若cur_e是L的数据元素，且不是第一个，则用pre_e返回它的前驱；
   //           否则操作失败，pre_e无定义
   int j,i=L[MAX_SIZE-1].cur; // i指示链表第1个结点的位置
   do // 向后移动结点
   { j=i; // j指向i所指元素
     i=L[i].cur; // i指向下一个元素
   }while(i&&cur_e!=L[i].data); // i所指元素存在且其值不是cur_e，继续循环
   if(i) // 找到该元素
   { pre_e=L[j].data; // j所指元素是i所指元素的前驱元素，赋给pre_e
     return OK;
   }
   return ERROR; // 未找到该元素，或其无前驱
 }

 Status NextElem(SLinkList L,ElemType cur_e,ElemType &next_e)
 { // 初始条件：线性表L已存在
   // 操作结果：若cur_e是L的数据元素，且不是最后一个，则用next_e返回它的后继；
   //           否则操作失败，next_e无定义
   int j,i=LocateElem(L,cur_e); // 在L中查找第1个值为cur_e的元素的位置
   if(i) // L中存在元素cur_e
   { j=L[i].cur; // j指示cur_e的后继的位置
     if(j) // cur_e有后继
     { next_e=L[j].data; // 将cur_e的后继赋给next_e
       return OK; // cur_e元素有后继
     }
   }
   return ERROR; // L不存在cur_e元素，或cur_e元素无后继
 }

 Status ListInsert(SLinkList L,int i,ElemType e)
 { // 在L中第i个元素之前插入新的数据元素e
   int m,j,k=MAX_SIZE-1; // k指示表头结点的位序
   if(i<1||i>ListLength(L)+1) // i值不合法
     return ERROR;
   j=Malloc(L); // 申请新单元
   if(j) // 申请成功
   { L[j].data=e; // 将e赋值给新单元
     for(m=1;m<i;m++) // k向后移动i-1个结点，使k指示第i-1个结点
       k=L[k].cur; // 指向下一个结点
     L[j].cur=L[k].cur; // 新单元指向第i-1个元素后面的元素(第i个元素)
     L[k].cur=j; // 第i-1个元素指向新单元
     return OK;
   }
   return ERROR;
 }

 Status ListDelete(SLinkList L,int i,ElemType &e)
 { // 删除在L中第i个数据元素e，并返回其值
   int j,k=MAX_SIZE-1; // k指示表头结点的位序
   if(i<1||i>ListLength(L)) // i值不合法
     return ERROR;
   for(j=1;j<i;j++) // 移动i-1个元素，使k指向第i-1个元素
     k=L[k].cur; // 指向下一个元素
   j=L[k].cur; // 待删除元素(第i个元素)的位置赋给j
   L[k].cur=L[j].cur; // 使第i-1个元素指向待删除元素的后继元素
   e=L[j].data; // 待删除元素的值赋给e
   Free(L,j); // 释放待删除结点(回收到备用链表中)
   return OK;
 }

 void ListTraverse(SLinkList L,void(*visit)(ElemType))
 { // 初始条件：线性表L已存在。操作结果：依次对L的每个数据元素调用函数visit()
   int i=L[MAX_SIZE-1].cur; // i指示第1个元素的位序
   while(i) // 未到静态链表尾
   { visit(L[i].data); // 对当前元素调用visit()
     i=L[i].cur; // 指向下一个元素
   }
   printf("\n");
 }
