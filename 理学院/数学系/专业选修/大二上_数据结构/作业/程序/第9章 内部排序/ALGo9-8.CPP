 // alg9-8.cpp 链式基数排序，包括算法10.15～10.17
 #include"c1.h"
 typedef char KeysType; // 定义关键字类型为字符串型
 typedef int InfoType; // 定义其他数据项为整型
 #include"c9-4.h" // 基数排序的数据类型
 typedef SLList SqList; // 定义SqList为SLList类型，以便利用func9-2.cpp中的函数
 #define length recnum // 定义length为recnum类型，以便利用func9-2.cpp中的函数
 #include"func9-2.cpp" // 算法10.18

 void MadeListFromFile(SLList &L,FILE* f)
 { // 通过文件f建立顺序表L
   int i;
   fscanf(f,"%d",&L.recnum); // 由数据文件输入表长给L.recnum
   for(i=1;i<=L.recnum;i++) // 依次输入结点的值(除next域)
     fscanf(f,"%s%d",&L.r[i].keys,&L.r[i].otheritems);
   L.keynum=strlen(L.r[1].keys); // 将关键字的长度赋给L.keynum(设关键字等长)
 }
 
 int ord(char c)
 { // 返回关键字c的序号
   return c-'0';
 }

 void Distribute(SLCell r[],int i,ArrType f,ArrType e)
 { // 静态链表L的r域中记录已按(keys[i-1]，…，keys[0])有序。本算法按第i个关键字
   // keys[i](keys[0]是最低位关键字)建立RADIX个子表，使同一子表中记录的keys[i]相同。
   // f[0..RADIX-1]和e[0..RADIX-1]分别指向各子表中第一个和最后一个记录。算法10.15
   int j,p;
   for(j=0;j<RADIX;++j)
     f[j]=0; // 各子表初始化为空表
   for(p=r[0].next;p;p=r[p].next) // p按链式结构依次指向静态链表的记录
   { j=ord(r[p].keys[i]); // 当前记录的第i位关键字的序号，以下将当前记录按序号插入子表
     if(!f[j]) // 子表[j]空
       f[j]=p; // 表头指向当前记录
     else // 子表[j]不空
       r[e[j]].next=p; // 修改原子表[j]的表尾记录的next域指向当前记录
     e[j]=p; // 设置表尾指针指向p所指的新表尾记录
   }
   printf("\nf[j]="); // 以下输出表头指针f[]和表尾指针e[]，新增
   for(j=0;j<RADIX;++j)
     printf("%3d",f[j]);
   printf("\ne[j]=");
   for(j=0;j<RADIX;++j)
     if(f[j])
       printf("%3d",e[j]);
     else
       printf("%3d",0);
   printf("\n");
 }

 int succ(int i)
 { // 求后继函数
   return ++i;
 }

 void Collect(SLCell r[],ArrType f,ArrType e)
 { // 本算法按keys[i]自小至大地将f[0..RADIX-1]所指各子表依次链接成一个链表，
   // e[0..RADIX-1]为各子表的尾指针。算法10.16
   int j,t;
   for(j=0;!f[j];j=succ(j)); // 找第1个非空子表[j]，succ为求后继函数
   r[0].next=f[j]; // r[0].next指向第1个非空子表[j]的第1个元素
   t=e[j]; // t指向第1个非空子表[j]的表尾元素
   while(j<RADIX-1) // 未到最后一位关键字
   { for(j=succ(j);j<RADIX-1&&!f[j];j=succ(j)); // 找下一个非空子表
     if(f[j]) // 子表不空
     { r[t].next=f[j]; // 链接两个非空子表
       t=e[j]; // t指向新的表尾元素
     }
   }
   r[t].next=0; // 表尾
 }

 void Print2(SLList L)
 { // 按数组序号输出静态链表
   int i=0;
   printf("keynum=%d recnum=%d i=%d next=%d\n",L.keynum,L.recnum,i,
   L.r[i].next);
   for(i=1;i<=L.recnum;i++)
     printf("i=%d keys=%s otheritems=%d next=%d\n",i,L.r[i].keys,
     L.r[i].otheritems,L.r[i].next);
 }

 void PrintLL(SLList L)
 { // 按链表顺序输出静态链表L
   int i=L.r[0].next;
   while(i)
   { printf("%s ",L.r[i].keys);
     i=L.r[i].next;
   }
 }

 void RadixSort(SLList &L)
 { // L是采用静态链表表示的顺序表。对L作基数排序，使得L成为按关键字
   // 自小到大的有序静态链表，L.r[0]为头结点。算法10.17
   int i,j=1;
   ArrType f,e;
   for(i=0;i<L.recnum;++i) // 将L改造为静态链表
     L.r[i].next=i+1;
   L.r[L.recnum].next=0;
   for(i=L.keynum-1;i>=0;--i,++j) // 按最低位优先依次对各关键字进行分配和收集，修改
   { Distribute(L.r,i,f,e); // 第i趟分配
     printf("第%d趟分配后：\n",j);
     Print2(L); // 按序号输出排序前的静态链表m
     Collect(L.r,f,e); // 第i趟收集
     printf("第%d趟收集后：\n",j);
     Print2(L); // 按序号输出静态链表L
     PrintLL(L); // 按链表顺序输出静态链表L
   }
 }

 void main()
 {
   FILE *f; // 文件指针类型
   SLList m; // 静态链表变量
   int *adr;
   f=fopen("f9-4.txt","r"); // 打开数据文件f9-4.txt
   MadeListFromFile(m,f); // 通过文件f建立静态链表m
   fclose(f); // 关闭数据文件
   printf("排序前(next域还未赋值)：\n");
   Print2(m); // 按序号输出排序前的静态链表m
   RadixSort(m); // 对m调用基数排序法，使得m成为有序静态链表
   adr=(int*)malloc((m.recnum+1)*sizeof(int)); // 动态生成adr数组
   Sort(m,adr); // 求得adr[1..m.length]，adr[i]为静态链表m的第i个最小记录的序号
   Rearrange(m,adr); // 按adr[]重排m.r，使其成为有序的顺序表
   free(adr); // 释放adr所指的存储空间
   printf("\n重排记录后(next域不起作用)：\n");
   Print2(m); // 按序号输出重新排序后的静态链表m
 }
