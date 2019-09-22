 // algo3-5.cpp 表达式求值(输入的值在0～9之间，中间结果和输出的值在-128～127之间)，
 // 算法3.4
 typedef char SElemType; // 定义栈元素为字符型
 #include"c1.h"
 #include"c3-1.h" // 栈的顺序存储结构
 #include"bo3-1.cpp" // 顺序栈存储结构的基本操作(9个)
 #include"func3-1.cpp" // 包括Precede()、In()和Operate()函数

 SElemType EvaluateExpression() // 算法3.4，有改动
 { // 算术表达式求值的算符优先算法。设OPTR和OPND分别为运算符栈和运算数栈
   SqStack OPTR,OPND;
   SElemType a,b,c,x;
   InitStack(OPTR); // 初始化运算符栈OPTR和运算数栈OPND
   InitStack(OPND);
   Push(OPTR,'\n'); // 将换行符压入运算符栈OPTR的栈底。修改
   c=getchar(); // 由键盘读入1个字符到c
   GetTop(OPTR,x); // 将运算符栈OPTR的栈顶元素赋给x
   while(c!='\n'||x!='\n') // c和x不都是换行符
   { if(In(c)) // c是7种运算符之一
       switch(Precede(x,c)) // 判断x和c的优先权
       { case'<':Push(OPTR,c); // 运算符栈OPTR的栈顶元素x的优先权低，入栈c
                 c=getchar(); // 由键盘读入下一个字符到c
                 break;
         case'=':Pop(OPTR,x); // x='('且c=')'情况，弹出'('给x(后又扔掉)
                 c=getchar(); // 由键盘读入下一个字符到c(扔掉c原有的')')
                 break;
         case'>':Pop(OPTR,x); // 栈顶元素x的优先权高，弹出运算符栈OPTR的栈顶元素给x。修改
                 Pop(OPND,b); // 依次弹出运算数栈OPND的栈顶元素给b，a
                 Pop(OPND,a);
                 Push(OPND,Operate(a,x,b)); // 做运算a x b，并将运算结果入运算数栈
       }
     else if(c>='0'&&c<='9') // c是操作数
     { Push(OPND,c-48); // 将该操作数的值(不是ASCII码)压入运算数栈OPND
       c=getchar(); // 由键盘读入下一个字符到c
     }
     else // c是非法字符
     { printf("出现非法字符\n");
       exit(OVERFLOW);
     }
     GetTop(OPTR,x); // 将运算符栈OPTR的栈顶元素赋给x
   }
   Pop(OPND,x); // 弹出运算数栈OPND的栈顶元素(运算结果)给x(修改此处)
   if(!StackEmpty(OPND)) // 运算数栈OPND不空(运算符栈OPTR仅剩'\n')
   { printf("表达式不正确\n");
     exit(OVERFLOW);
   }
   return x;
 }

 void main()
 {
   printf("请输入算术表达式(输入的值要在0～9之间、");
   printf("中间运算值和输出结果在-128～127之间)\n");
   printf("%d\n",EvaluateExpression()); // 返回值(8位二进制，1个字节)按整型格式输出
 }
