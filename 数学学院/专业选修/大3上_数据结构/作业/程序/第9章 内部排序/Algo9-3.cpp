 // algo9-3.cpp 希尔排序，包括算法10.4、10.5
 #include<stdio.h>
 #include"c8-2.h" // 对两个数值型关键字比较的约定
 typedef int KeyType; // 定义关键字的类型为整型
 typedef int InfoType; // 定义其他数据项的类型为整型
 #include"c9-1.h" // 记录的数据类型
 #include"c9-2.h" // 顺序表类型的存储结构
 #include"func9-1.cpp" // 配套的输入输出函数

 void Print1(SqList L) // 输出顺序表L的关键字
 { int i;
   for(i=1;i<=L.length;i++)
     printf("%d ",L.r[i].key);
   printf("\n");
 }

 void ShellInsert(SqList &L,int dk)
 { // 对顺序表L作一趟希尔插入排序。本算法和一趟直接插入排序相比，作了以下修改：
   // 1.前后记录位置的增量是dk，而不是1;
   // 2.r[0]只是暂存单元，不是哨兵。当j<=0时，插入位置已找到。算法10.4
   int i,j;
   for(i=dk+1;i<=L.length;++i) // 从与第1个记录相差增量dk的记录到表尾
     if LT(L.r[i].key,L.r[i-dk].key) // 关键字小于前面记录的(按增量)
     { // 以下将L.r[i]插入有序增量子表
       L.r[0]=L.r[i]; // 当前记录暂存在L.r[0]
       for(j=i-dk;j>0&&LT(L.r[0].key,L.r[j].key);j-=dk)
         L.r[j+dk]=L.r[j]; // 记录后移，查找插入位置
       L.r[j+dk]=L.r[0]; // 插入
     }
 }

 void ShellSort(SqList &L,int dlta[],int t)
 { // 按增量序列dlta[0..t-1]对顺序表L作希尔排序。算法10.5
   int k;
   for(k=0;k<t;++k) // 对所有增量序列
   { ShellInsert(L,dlta[k]); // 一趟增量为dlta[k]的希尔插入排序
     printf("dlta[%d]=%d，第%d趟排序结果(仅输出关键字)：",k,dlta[k],k+1);
     Print1(L); // 输出顺序表L的关键字
   }
 }

 #define N 10 // 记录数组长度
 #define T 3 // 增量序列数组长度
 void main()
 {
   RedType d[N]={{49,1},{38,2},{65,3},{97,4},{76,5},{13,6},{27,7},{49,8},
   {55,9},{4,10}}; // 记录数组
   SqList m; // 顺序表
   int i,dt[T]={5,3,1}; // 增量序列数组(由大到小，最后一项的值必为1)
   for(i=0;i<N;i++) // 将数组d赋给顺序表m
     m.r[i+1]=d[i];
   m.length=N;
   printf("希尔排序前：");
   Print(m); // 输出排序前的顺序表m
   ShellSort(m,dt,T); // 按增量序列dt[0..T-1]对顺序表m作希尔排序
   printf("希尔排序后：");
   Print(m); // 输出排序后的顺序表m
 }
