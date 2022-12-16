 // main2-4.cpp 检验bo2-5.cpp的主程序
 #include"c1.h"
 typedef int ElemType; // 定义ElemType为整型
 #include"c2-3.h" // 静态单链表的存储结构
 #include"bo2-5.cpp" // 静态链表的基本操作(13个)，包括算法2.13、2.15和2.16
 #include"func2-2.cpp" // 包括equal()、comp()、print()、print1()和print2()函数
 typedef SLinkList LinkList; // 定义func2-3.cpp中的LinkList类型为SLinkList类型
 #define SLL // 定义了SLL(静态链表标志)，使func2-3.cpp选择执行静态链表特有的函数
 #include"func2-3.cpp" // 主函数
