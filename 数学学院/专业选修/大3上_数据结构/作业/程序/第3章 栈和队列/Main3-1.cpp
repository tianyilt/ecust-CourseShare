 // main3-1.cpp 检验bo3-1.cpp的主程序
 #include"c1.h"
 typedef int SElemType; // 定义栈元素类型，此句要在c3-1.h的前面
 #include"c3-1.h" // 栈的顺序存储结构
 #include"bo3-1.cpp" // 顺序栈存储结构的基本操作(9个)
 #define ElemType SElemType // 将func2-2.cpp中的ElemType类型定义为SElemType类型
 #include"func2-2.cpp" // 包括equal()、comp()、print()、print1()和print2()函数

 void main()
 {
   int j;
   SqStack s;
   SElemType e;
   InitStack(s); // 初始化栈s
   for(j=1;j<=12;j++)
     Push(s,j); // 将值为j的栈元素入栈s中
   printf("栈中元素依次为");
   StackTraverse(s,print); // 从栈底到栈顶依次对栈s中每个元素调用print()函数
   Pop(s,e); // 弹出栈顶元素，其值赋给e
   printf("弹出的栈顶元素e=%d\n",e);
   printf("栈空否？%d(1:空 0:否)，",StackEmpty(s));
   GetTop(s,e); // 将新的栈顶元素赋给e
   printf("栈顶元素e=%d，栈的长度为%d\n",e,StackLength(s));
   ClearStack(s); // 清空栈s
   printf("清空栈后，栈空否？%d(1:空 0:否)\n",StackEmpty(s));
   DestroyStack(s); // 销毁栈s
   printf("销毁栈后，s.top=%u，s.base=%u，s.stacksize=%d\n",s.top,s.base,s.stacksize);
 }
