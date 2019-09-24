 // algo9-1.cpp 检验bo9-1.cpp的程序
 #include"c1.h"
 #include"c8-2.h" // 对两个数值型关键字比较的约定
 typedef int KeyType; // 定义关键字的类型为整型
 typedef int InfoType; // 定义其他数据项的类型为整型
 #include"c9-1.h" // 记录的数据类型
 #include"c9-2.h" // 顺序表类型的存储结构
 #include"bo9-1.cpp" // 3个顺序表插入排序的函数，包括算法10.1、10.2
 #include"func9-1.cpp" // 配套的输入输出函数

 void main()
 {
   FILE *f; // 文件指针类型
   SqList m1,m2,m3,m4; // 4个顺序表变量
   int i;
   f=fopen("f9-1.txt","r"); // 打开数据文件f9-1.txt
   fscanf(f,"%d",&m1.length); // 由数据文件输入数据元素个数给m1.length
   for(i=1;i<=m1.length;i++) // 给m1.r赋值
     InputFromFile(f,m1.r[i]); // 由数据文件输入数据元素的值并赋给m1.r[i]
   fclose(f); // 关闭数据文件
   m2=m3=m4=m1; // 复制顺序表m1到m2、m3、m4，使之与m1相同
   printf("排序前：\n");
   Print(m1); // 输出排序前的顺序表
   InsertSort(m1); // 对m1调用直接插入排序法
   printf("直接插入排序后：\n");
   Print(m1); // 输出排序后的m1
   BInsertSort(m2); // 对m2调用折半插入排序法
   printf("折半插入排序后：\n");
   Print(m2); // 输出排序后的m2
   P2_InsertSort(m3,0); // 对m3调用2-路插入排序法
   printf("2-路插入排序后：\n");
   Print(m3); // 输出排序后的m3
   P2_InsertSort(m4,1); // 对m4调用改进的2-路插入排序法
   printf("改进的2-路插入排序后：\n");
   Print(m4); // 输出排序后的m4
 }
