 // func6-1.cpp 利用条件编译，在主程序中选择结点的类型，访问树结点的函数
 #include"c1.h"
 #if CHAR // CHAR值为非零，结点类型为字符
   typedef char TElemType; // 定义树元素类型为字符型
   TElemType Nil=' '; // 设字符型以空格符为空
   #define form "%c" // 输入输出的格式为%c
 #else // CHAR值为零，结点类型为整型
   typedef int TElemType; // 定义树元素类型为整型
   TElemType Nil=0; // 设整型以0为空
   #define form "%d" // 输入输出的格式为%d
 #endif
 void visit(TElemType e)
 { printf(form" ",e); // 定义CHAR为1时，以字符格式输出；CHAR为0时，以整型格式输出
 }
