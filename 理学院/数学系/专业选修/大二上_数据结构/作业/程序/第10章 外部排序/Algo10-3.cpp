 // algo10-3.cpp 调用bo10-1.cpp的程序(运行algo10-2.cpp后运行此程序)
 #include"c1.h"
 typedef int KeyType; // 定义关键字的类型为整型
 typedef int InfoType; // 定义其他数据项的类型为整型
 #include"c9-1.h" // 记录的数据类型
 #define k 5 // k(5)路归并，以下2行取1行。第6行
 //#define k 3 // 3路归并。第7行
 FILE *fp[k+1]; // k+1个文件指针(fp[k]为大文件指针)，全局变量
 typedef int LoserTree[k];
 // [1..k-1]是败者树的非叶子结点，[0]中是胜者，存相应叶子的序号
 RedType b[k+1]; // [0..k-1]是败者树的叶子(外结点)，[k]存最小关键字
 #define MIN_KEY INT_MIN // 最小关键字
 #define MAX_KEY INT_MAX // 最大关键字
 #define M 10 // 设输出M个排序后的数据换行

 void Print(RedType t)
 { printf("(%d,%d)",t.key,t.otherinfo);
 }

 #include"bo10-1.cpp" // k路平衡归并的函数

 void main()
 {
   LoserTree ls; // 败者树，长度为k的整型数组
   int i;
   char outfile[10],filename[3]; // 大文件名,有序小文件名
   for(i=0;i<k;i++)
   { itoa(i,filename,10); // i作为临时的有序小文件的文件名
     fp[i]=fopen(filename,"r"); // 以读的方式打开已排序的小文件0，1，…，k-1
   }
   printf("请输入排序后的大文件名：");
   scanf("%s",outfile); // 输入排序后的大文件名给outfile
   fp[k]=fopen(outfile,"w"); // 以写的方式打开排序后的大文件outfile
   printf("有序大文件%s的记录为：\n",outfile);
   K_Merge(ls); // 利用败者树将k个有序小文件中的记录归并为1个有序大文件
   printf("\n"); // 换行
   for(i=0;i<=k;i++)
     fclose(fp[i]); // 关闭文件0，1，…，已排序的大文件outfile
 }
