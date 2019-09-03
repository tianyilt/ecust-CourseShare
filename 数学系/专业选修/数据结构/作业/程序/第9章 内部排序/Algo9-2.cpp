 // algo9-2.cpp 表插入排序，包括算法10.3
 #include"c1.h"
 typedef int KeyType; // 定义关键字的类型为整型
 typedef int InfoType; // 定义其他数据项的类型为整型
 #include"c9-1.h" // 记录的数据类型
 #include"c9-3.h" // 静态链表类型
 typedef SLinkListType SqList; // 定义算法10.18中的SqList类型为SLinkListType类型
 #include"func9-2.cpp" // 算法10.18

 void PrintL(SLinkListType L) // 按顺序结构输出静态链表的函数
 { int i;
   for(i=0;i<=L.length;i++)
     printf("i=%d key=%d ord=%d next=%d\n",i,L.r[i].rc.key,
     L.r[i].rc.otherinfo,L.r[i].next);
 }

 void InputFromFile(FILE* f,RedType &c) // 从文件输入记录的函数
 { fscanf(f,"%d%d",&c.key,&c.otherinfo);
 }

 void CreatTableFromFile(SLinkListType &SL,FILE* f)
 { // 由数据文件f建立未排序的顺序表SL(next域不起作用)
   int i;
   fscanf(f,"%d",&SL.length); // 由文件输入表长
   for(i=1;i<=SL.length;i++)
     InputFromFile(f,SL.r[i].rc); // 依次由文件输入记录到SL.r[i].rc
 }

 void MakeTableSorted(SLinkListType &SL)
 { // 使无序的顺序表SL成为有序的静态循环链表
   int i,p,q;
   SL.r[0].rc.key=INT_MAX; // 表头结点记录的关键字取最大整数(非降序循环链表的表尾)
   SL.r[0].next=0; // next域为0形成空循环链表，初始化
   for(i=1;i<=SL.length;i++) // 依次将SL中的数据插入到静态循环链表中
   { q=0; // q指向静态链表的表头元素
     p=SL.r[0].next; // p指向静态链表的第1个元素
     while(SL.r[p].rc.key<=SL.r[i].rc.key) // 静态链表向后移
     { // p所指元素的关键字不大于待插记录的关键字(上行的“=”使排序方法是稳定的)
       q=p; // q指向p所指元素
       p=SL.r[p].next; // p指向下1个元素
     } // p所指元素的关键字大于待插记录的关键字，q所指元素的关键字不大于待插记录的关键字
     SL.r[q].next=i; // 将当前记录插入静态链表(q后p前)
     SL.r[i].next=p;
   }
 }

 void Arrange(SLinkListType &SL)
 { // 根据静态链表SL中各结点的指针值调整记录位置，使得SL成为非递减有序的顺序表。算法10.3
   int i,p,q;
   SLNode t;
   p=SL.r[0].next; // p指示第1个记录的当前位置
   for(i=1;i<SL.length;++i)
   { // SL.r[1..i-1]中记录已按关键字有序排列，第i个记录在SL中的当前位置应不小于i
     while(p<i) // p所指的记录已排好序
       p=SL.r[p].next; // 继续向后找，跳出已排好序的部分
     q=SL.r[p].next; // q指示尚未调整的表尾部分
     if(p!=i) // 第i个记录不恰好在p所指的位置，需移动
     { t=SL.r[p]; // p和i交换记录，使第i个记录到位
       SL.r[p]=SL.r[i];
       SL.r[i]=t;
       SL.r[i].next=p; // 指向被移走的记录，[i]已排好序，使得以后可由while循环找回p所指记录
     }
     p=q; // p指示尚未调整的表尾部分，为找第i+1个记录作准备
   }
 }

 void main()
 {
   FILE *f; // 文件指针类型
   int *adr,i;
   SLinkListType m1,m2; // 2个静态链表变量
   f=fopen("f9-1.txt","r"); // 打开数据文件f9-1.txt
   CreatTableFromFile(m1,f); // 由数据文件f建立未排序的顺序表
   fclose(f); // 关闭数据文件
   printf("m1排序前：\n");
   PrintL(m1); // 输出排序前的顺序表m1
   MakeTableSorted(m1); // 使无序的顺序表m1成为有序的静态链表
   m2=m1; // 复制静态链表m1，使m2与m1相同
   printf("m1、m2链式有序后：\n");
   PrintL(m1); // 输出链式有序的顺序表m1
   Arrange(m1); // 将链式有序的顺序表m1重排为有序的顺序表
   printf("m1排序后：\n");
   PrintL(m1); // 输出排序后的顺序表m1
   adr=(int*)malloc((m2.length+1)*sizeof(int)); // 动态生成adr数组
   Sort(m2,adr); // 求得adr[1..m2.length]，adr[i]为静态链表m2的第i个最小记录的序号
   for(i=1;i<=m2.length;i++) // 依次输出adr[i]
   { printf("adr[%d]=%d ",i,adr[i]);
     if(i%4==0)
       printf("\n");
   }
   Rearrange(m2,adr); // 按adr[]重排m2.r，使其成为有序的顺序表
   printf("m2排序后：\n");
   PrintL(m2); // 输出排序后的顺序表m2
   free(adr); // 释放adr所指的存储空间
 }
