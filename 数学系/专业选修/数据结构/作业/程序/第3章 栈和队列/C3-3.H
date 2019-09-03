 // c3-3.h 队列的顺序存储结构(循环队列)。在教科书第64页
 #define MAX_QSIZE 5 // 最大队列长度+1
 struct SqQueue
 { QElemType *base; // 初始化的动态分配存储空间
   int front; // 头指针，若队列不空，指向队列头元素
   int rear; // 尾指针，若队列不空，指向队列尾元素的下一个位置
 };
