 // func2-2.cpp 几个常用的函数
 Status equal(ElemType c1,ElemType c2)
 { // 判断是否相等的函数
   if(c1==c2)
     return TRUE;
   else
     return FALSE;
 }

 int comp(ElemType a,ElemType b)
 { // 根据a<、=或>b，分别返回-1、0或1
   if(a==b)
     return 0;
   else
     return (a-b)/abs(a-b);
 }

 void print(ElemType c)
 { // 以十进制整型的格式输出元素的值
   printf("%d ",c);
 }

 void print1(ElemType &c)
 { // 以十进制整型的格式输出元素的值(设c为引用类型)
   printf("%d ",c);
 }

 void print2(ElemType c)
 { // 以字符型的格式输出元素的值
   printf("%c ",c);
 }
