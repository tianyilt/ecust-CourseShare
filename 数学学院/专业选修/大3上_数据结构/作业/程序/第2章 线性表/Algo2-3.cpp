 // algo2-3.cpp 实现算法2.11和2.12的程序
 #include"c1.h"
 typedef int ElemType; // 定义ElemType为整型
 #include"c2-2.h" // 线性表的单链表存储结构
 #include"bo2-2.cpp" // 设有头结点单链表存储结构的基本操作
 #include"func2-2.cpp" // 包括equal()、comp()、print()、print1()和print2()函数

 void CreateList(LinkList &L,int n) // 算法2.11
 { // 逆位序(结点插在表头)输入n个元素的值，建立带表头结点的单链线性表L
   int i;
   LinkList p;
   L=(LinkList)malloc(sizeof(LNode)); // 生成头结点
   L->next=NULL; // 先建立一个带头结点的空单链表
   printf("请输入%d个数据\n",n);
   for(i=n;i>0;--i)
   { p=(LinkList)malloc(sizeof(LNode)); // 生成新结点
     scanf("%d",&p->data); // 给新结点输入元素值
     p->next=L->next; // 将新结点插在表头
     L->next=p; // 头结点指向新结点
   }
 }

 void CreateList1(LinkList &L,int n)
 { // 正位序(结点插在表尾)输入n个元素的值，建立带表头结点的单链线性表L
   int i;
   LinkList p,q;
   L=(LinkList)malloc(sizeof(LNode)); // 生成头结点
   L->next=NULL; // 先建立一个带头结点的空单链表
   q=L; // q指向空表的头结点(相当于尾结点)
   printf("请输入%d个数据\n",n);
   for(i=1;i<=n;i++)
   { p=(LinkList)malloc(sizeof(LNode)); // 生成新结点
     scanf("%d",&p->data); // 给新结点输入元素值
     q->next=p; // 将新结点插在表尾
     q=q->next; // q指向尾结点
   }
   p->next=NULL; // 最后一个结点的指针域为空
 }

 void MergeList(LinkList La,LinkList &Lb,LinkList &Lc) // 算法2.12
 { // 已知单链线性表La和Lb的元素按值非递减排列。
   // 归并La和Lb得到新的单链线性表Lc，Lc的元素也按值非递减排列。(销毁Lb，Lc即新的La)
   LinkList pa=La->next,pb=Lb->next,pc; // pa、pb分别指向La、Lb的首元结点(待比较结点)
   Lc=pc=La; // 用La的头结点作为Lc的头结点，pc指向La的头结点(Lc的尾结点)
   while(pa&&pb) // La和Lb中的元素都未比较完
     if(pa->data<=pb->data) // La的当前元素不大于Lb的当前元素
     { pc->next=pa; // 将pa所指结点归并到Lc中
       pc=pa; // pc指向表Lc的最后一个结点
       pa=pa->next; // 表La的下一个结点成为待比较结点
     }
     else // Lb的当前元素小于La的当前元素
     { pc->next=pb; // 将pb所指结点归并到Lc中
       pc=pb; // pc指向表Lc的最后一个结点
       pb=pb->next; // 表Lb的下一个结点成为待比较结点
     }
   pc->next=pa?pa:pb; // 插入剩余段
   free(Lb); // 释放Lb的头结点
   Lb=NULL; // Lb不再指向任何结点
 }

 void main()
 {
   int n=5;
   LinkList La,Lb,Lc;
   printf("按非递减顺序，");
   CreateList1(La,n); // 根据输入顺序，正位序建立线性表
   printf("La="); 
   ListTraverse(La,print); // 输出链表La的内容
   printf("按非递增顺序，");
   CreateList(Lb,n); // 根据输入顺序，逆位序建立线性表
   printf("Lb="); 
   ListTraverse(Lb,print); // 输出链表Lb的内容
   MergeList(La,Lb,Lc); // 按非递减顺序归并La和Lb，得到新表Lc
   printf("Lc="); 
   ListTraverse(Lc,print); // 输出链表Lc的内容
 }
