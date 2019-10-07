 // alg9-7.cpp 归并排序，包括算法10.12～10.14
 #include"c1.h"
 #include"c8-2.h" // 对两个数值型关键字比较的约定
 typedef int KeyType; // 定义关键字的类型为整型
 typedef int InfoType; // 定义其他数据项的类型为整型
 #include"c9-1.h" // 记录的数据类型
 #include"c9-2.h" // 顺序表类型的存储结构
 #include"func9-1.cpp" // 配套的输入输出函数

 void Merge(RedType SR[],RedType TR[],int i,int m,int n)
 { // 将有序的SR[i..m]和SR[m+1..n]归并为有序的TR[i..n]。算法10.12
   int j,k,p;
   for(j=m+1,k=i;i<=m&&j<=n;++k) // 将SR中记录由小到大地并入TR
     if LQ(SR[i].key,SR[j].key)
       TR[k]=SR[i++];
     else
       TR[k]=SR[j++];
   if(i<=m)
     for(p=0;p<=m-i;p++)
       TR[k+p]=SR[i+p]; // 将剩余的SR[i..m]复制到TR
   if(j<=n)
     for(p=0;p<=n-j;p++)
       TR[k+p]=SR[j+p]; // 将剩余的SR[j..n]复制到TR
 }

 void MSort(RedType SR[],RedType TR1[],int s, int t)
 { // 将SR[s..t]归并排序为TR1[s..t]。算法10.13
   int m;
   RedType TR2[MAX_SIZE+1];
   if(s==t) // 只有1个元素待归并
     TR1[s]=SR[s]; // 直接赋值
   else // 有多个元素待归并
   { m=(s+t)/2; // 将SR[s..t]平分为SR[s..m]和SR[m+1..t]
     MSort(SR,TR2,s,m); // 递归地将SR[s..m]归并为有序的TR2[s..m]
     MSort(SR,TR2,m+1,t); // 递归地将SR[m+1..t]归并为有序的TR2[m+1..t]
     Merge(TR2,TR1,s,m,t); // 将TR2[s..m]和TR2[m+1..t]归并到TR1[s..t]
   }
 }

 void MergeSort(SqList &L)
 { // 对顺序表L作归并排序。算法10.14
   MSort(L.r,L.r,1,L.length);
   // 将顺序表L.r[1..L.length]归并排序为有序的顺序表L.r[1..L.length]
 }

 void main()
 {
   FILE *f; // 文件指针类型
   SqList m; // 顺序表变量
   int i;
   f=fopen("f9-3.txt","r"); // 打开数据文件f9-3.txt
   fscanf(f,"%d",&m.length); // 由数据文件输入数据元素个数给m.length
   for(i=1;i<=m.length;i++) // 给m.r赋值
     InputFromFile(f,m.r[i]); // 由数据文件输入数据元素的值并赋给m1.r[i]
   fclose(f); // 关闭数据文件
   printf("排序前：\n");
   Print(m); // 输出排序前的顺序表m
   MergeSort(m); // 对m调用归并排序法
   printf("排序后：\n");
   Print(m); // 输出排序后的顺序表m
 }
