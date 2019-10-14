 // algo9-5.cpp 调用算法10.7、10.8、10.6(a)和10.6(b)的程序
 #include<stdio.h>
 typedef int KeyType; // 定义关键字的类型为整型
 typedef int InfoType; // 定义其他数据项的类型为整型
 #include"c9-1.h" // 记录的数据类型
 #include"c9-2.h" // 顺序表类型的存储结构
 #include"func9-1.cpp" // 配套的输入输出函数
 #include"func9-3.cpp" // 算法10.6(a)，函数Partition()，此2行任取1行，运行结果相同
 //#include"func9-4.cpp" // 算法10.6(b)，函数Partition()
 #include"bo9-2.cpp" // 快速排序的函数，包括算法10.7和10.8

 void main()
 {
   FILE *f; // 文件指针类型
   SqList m; // 顺序表变量
   int i;
   f=fopen("f9-1.txt","r"); // 打开数据文件f9-1.txt
   fscanf(f,"%d",&m.length); // 由数据文件输入数据元素个数给m.length
   for(i=1;i<=m.length;i++) // 给m.r赋值
     InputFromFile(f,m.r[i]); // 由数据文件输入数据元素的值并赋给m.r[i]
   fclose(f); // 关闭数据文件
   printf("排序前：\n");
   Print(m); // 输出排序前的顺序表m
   QuickSort(m); // 对m调用快速排序法
   printf("排序后：\n");
   Print(m); // 输出排序后的顺序表m
 }
