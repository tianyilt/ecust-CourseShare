 // algo10-2.cpp 将无序的大文件f10-1.txt(记录个数=k*N)分成k个长度为N的有序小文件的程序
 #include"c1.h"
 #include"c8-2.h" // 对两个数值型关键字比较的约定
 typedef int KeyType; // 定义关键字的类型为整型
 typedef int InfoType; // 定义其他数据项的类型为整型
 #include"c9-1.h" // 记录的数据类型
 #include"c9-2.h" // 顺序表类型的存储结构
 #include"bo9-1.cpp" // 顺序表插入排序的函数
 #include"func9-1.cpp" // 配套的输入输出函数
 #define k 5 // k路归并
 #define N 3 // 设每个小文件最多有N个数据(可将整个文件一次读入内存的称为小文件)
 void main()
 {
   SqList m; // 顺序表，用于对小文件进行内部排序
   FILE *f,*g; // 文件指针
   char filename[3]; // 有序小文件名
   int i,j;
   f=fopen("f10-1.txt","r"); // 以读的方式打开含有k*N个记录的未排序大文件f10-1.txt
   for(i=0;i<k;i++) // 将大文件f10-1.txt的数据分成k组
   { for(j=1;j<=N;j++) // 每组N个数据
       InputFromFile(f,m.r[j]); // 由数据文件输入值并赋给m.r[j]
     m.length=N; // 顺序表的记录长度
     BInsertSort(m); // 对顺序表m作折半插入排序，使m.r成为有序表
     itoa(i,filename,10); // i作为临时的有序小文件的文件名
     g=fopen(filename,"w"); // 依次以写的方式打开文件0，1，…，k-1
     printf("有序子文件%s的数据为：",filename);
     Print(m); // 输出排序后的m
     for(j=1;j<=N;j++) // 依次将已排序的m.r[j]写入小文件0，1，…，k-1
       fprintf(g,"%d %d\n",m.r[j].key,m.r[j].otherinfo);
     fclose(g); // 依次关闭小文件0，1，…，k-1
   }
   fclose(f); // 关闭未排序的大文件f10-1.txt
 }
