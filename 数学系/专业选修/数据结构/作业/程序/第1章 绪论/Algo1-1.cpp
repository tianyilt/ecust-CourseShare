 // algo1-1.cpp 变量的引用类型和非引用类型的区别
 #include"c1.h"
 void fa(int a) // 在函数中改变a，将不会带回主调函数(主调函数中的a仍是原值)
 { a++;
   printf("在函数fa中：a=%d\n",a);
 }

 void fb(int &a) // 由于a为引用类型，在函数中改变a，其值将带回主调函数
 { a++;
   printf("在函数fb中：a=%d\n",a);
 }

 void main()
 {
   int n=1;
   printf("在主程中，调用函数fa之前：n=%d\n",n);
   fa(n);
   printf("在主程中，调用函数fa之后，调用函数fb之前：n=%d\n",n);
   fb(n);
   printf("在主程中，调用函数fb之后：n=%d\n",n);
 }
