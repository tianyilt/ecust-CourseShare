 // algo9-6.cpp 调用算法10.9、10.10和10.11的程序
 #include"c1.h"
 #include"c8-2.h" // 对两个数值型关键字比较的约定
 typedef int KeyType; // 定义关键字的类型为整型
 typedef int InfoType; // 定义其他数据项的类型为整型
 #include"c9-1.h" // 记录的数据类型
 #include"c9-2.h" // 顺序表类型的存储结构
 #include"func9-1.cpp" // 配套的输入输出函数
 typedef SqList HeapType; // 定义堆为顺序表存储结构。在教科书第281页
 #include"bo9-3.cpp" // 选择排序的函数，包括算法10.9、10.10和10.11

 void main()
 {
   FILE *f; // 文件指针类型
   SqList m1,m2,m3; // 3个顺序表变量
   int i;
   f=fopen("f9-1.txt","r"); // 打开数据文件f9-1.txt
   fscanf(f,"%d",&m1.length); // 由数据文件输入数据元素个数给m1.length
   for(i=1;i<=m1.length;i++) // 给m1.r赋值
     InputFromFile(f,m1.r[i]); // 由数据文件输入数据元素的值并赋给m1.r[i]
   fclose(f); // 关闭数据文件
   m2=m3=m1; // 复制顺序表，使m2、m3与m1相同
   printf("排序前：\n");
   Print(m1); // 输出排序前的顺序表
   SelectSort(m1); // 对m1调用简单选择排序法
   printf("简单选择排序后：\n");
   Print(m1); // 输出排序后的m1
   TreeSort(m2); // 对m2调用树形选择排序法
   printf("树形选择排序后：\n");
   Print(m2); // 输出排序后的m2
   HeapSort(m3); // 对m3调用堆排序法
   printf("堆排序后：\n");
   Print(m3); // 输出排序后的m3
 }
