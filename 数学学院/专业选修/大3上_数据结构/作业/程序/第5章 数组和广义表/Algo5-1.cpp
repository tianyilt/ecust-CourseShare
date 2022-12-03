 // algo5-1.cpp 变长参数表(函数的实参个数可变)编程示例
 #include"c1.h"
 typedef int ElemType; // 定义ElemType为整型
 ElemType Max(int num,...) // 函数功能：返回num个数中的最大值
 { // “...”表示变长参数表，位于形参表的最后，前面必须至少有一个固定参数
   va_list ap; // 定义ap是变长参数表类型(C语言的数据类型)，在stdarg.h中
   int i;
   ElemType m,n;
   if(num<1)
     exit(OVERFLOW);
   va_start(ap,num); // ap指向固定参数num后面的实参表
   m=va_arg(ap,ElemType); // 读取ap所指的实参，其类型为ElemType，将其赋给m，ap向后移
   for(i=1;i<num;++i) // 从第2个数到最后一个数
   { n=va_arg(ap,ElemType); // 依次读取ap所指的实参，将其赋给n，ap向后移
     if(m<n)
       m=n; // m中存放最大值
   }
   va_end(ap); // 与va_start()配对，结束对变长参数表的读取，ap不再指向变长参数表
   return m; // 将最大值返回
 }

 void main()
 {
  printf("1.最大值为%d\n",Max(4,7,9,5,8)); // 在4个数中求最大值，ap最初指向7
  printf("2.最大值为%d\n",Max(3,17,36,25)); // 在3个数中求最大值，ap最初指向17
 }
