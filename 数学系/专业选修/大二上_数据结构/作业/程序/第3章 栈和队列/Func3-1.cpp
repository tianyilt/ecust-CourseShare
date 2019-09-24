 // func3-1.cpp algo3-5.cpp和algo3-6.cpp要调用的函数
 char Precede(SElemType t1,SElemType t2)
 { // 根据教科书表3.1，判断t1，t2两符号的优先关系('#'用'\n'代替)
   char f;
   switch(t2)
   { case '+':
     case '-':if(t1=='('||t1=='\n')
                f='<'; // t1<t2
              else
                f='>'; // t1>t2
              break;
     case '*':
     case '/':if(t1=='*'||t1=='/'||t1==')')
                f='>'; // t1>t2
              else
                f='<'; // t1<t2
              break;
     case '(':if(t1==')')
              { printf("括号不匹配\n");
                exit(OVERFLOW);
              }
              else
                f='<'; // t1<t2
              break;
     case ')':switch(t1)
              { case '(':f='='; // t1=t2
                         break;
                case'\n':printf("缺乏左括号\n");
                         exit(OVERFLOW);
                default :f='>'; // t1>t2
              }
              break;
     case'\n':switch(t1)
              { case'\n':f='='; // t1=t2
                         break;
                case '(':printf("缺乏右括号\n");
                         exit(OVERFLOW);
                default :f='>'; // t1>t2
              }
   }
   return f;
 }

 Status In(SElemType c)
 { // 判断c是否为7种运算符之一
   switch(c)
   { case '+':
     case '-':
     case '*':
     case '/':
     case '(':
     case ')':
     case'\n':return TRUE;
     default :return FALSE;
   }
 }

 SElemType Operate(SElemType a,SElemType theta,SElemType b)
 { // 做四则运算a theta b，返回运算结果
   switch(theta)
   { case'+':return a+b;
     case'-':return a-b;
     case'*':return a*b;
   }
   return a/b;
 }
