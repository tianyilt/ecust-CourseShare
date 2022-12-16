 // algo3-6.cpp 表达式求值(范围为int类型，输入负数要用(0-正数)表示)
 typedef int SElemType; // 定义栈元素类型为整型，修改algo3-5.cpp
 #include"c1.h"
 #include"c3-1.h" // 顺序栈的存储结构
 #include"bo3-1.cpp" // 顺序栈的基本操作
 #include"func3-1.cpp" // 包括Precede()、In()和Operate()函数

 SElemType EvaluateExpression()
 { // 算术表达式求值的算符优先算法。设OPTR和OPND分别为运算符栈和运算数栈
   SqStack OPTR,OPND;
   SElemType a,b,d,x; // 修改algo3-5.cpp
   char c; // 存放由键盘接收的字符，修改algo3-5.cpp
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
     else if(c>='0'&&c<='9') // c是操作数，此语句修改algo3-5.cpp
     { d=0;
       while(c>='0'&&c<='9') // 是连续数字
       { d=d*10+c-'0';
         c=getchar();
       }
       Push(OPND,d); // 将d压入运算数栈OPND
     }
     else // c是非法字符，以下同algo3-5.cpp
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
   printf("请输入算术表达式，负数要用(0-正数)表示\n");
   printf("%d\n",EvaluateExpression());
 }
