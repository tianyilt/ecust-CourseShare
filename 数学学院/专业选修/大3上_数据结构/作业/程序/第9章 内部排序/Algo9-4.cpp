 // algo9-4.cpp 调用起泡排序的程序
 #include"c1.h"
 #define N 20 // 数组长度
 void bubble_sort(int a[],int n)
 { // 将a中n个整数重新排列成自小至大的有序序列(在教科书第16页)
   int i,j,t;
   Status change; // 调整的标志
   for(i=n-1,change=TRUE;i>=1&&change;--i) // 由后到前调整，change=FALSE时终止循环
   { change=FALSE; // 本次循环未调整的标志
     for(j=0;j<i;++j) // 从第1个到倒数第2个
       if(a[j]>a[j+1]) // 前面的大于后面的
       { t=a[j]; // 前后交换
         a[j]=a[j+1];
         a[j+1]=t;
         change=TRUE; // 设置调整的标志
       }
   }
 }

 void Print2(int r[],int n)
 { // 输出数组r的前n个数
   int i;
   for(i=0;i<n;i++)
     printf("%d ",r[i]);
   printf("\n");
 }

 void main()
 {
   FILE *f; // 文件指针类型
   int i=0,j,d[N];
   f=fopen("f9-2.txt","r"); // 打开数据文件f9-2.txt
   do
   { j=fscanf(f,"%d",&d[i++]); // 将文件f9-2.txt中的整数依次赋给d[i]
   }while(j!=EOF); // 未到文件尾
   fclose(f); // 关闭f所指的文件，f不再指向f9-2.txt文件
   i--; // i为读入的数据个数
   printf("排序前：\n");
   Print2(d,i); // 输出数组d排序前的前i个数
   bubble_sort(d,i); // 对数组d的前i个数调用起泡排序法
   printf("排序后：\n");
   Print2(d,i); // 输出数组d排序后的前i个数
 }
