 // c9-4.h 基数排序的数据类型。在教科书第286页
 #define MAX_NUM_OF_KEY 8 // 关键字项数的最大值
 #define RADIX 10 // 关键字基数，此时是十进制整数的基数
 #define MAX_SPACE 100
 struct SLCell // 静态链表的结点类型
 { KeysType keys[MAX_NUM_OF_KEY]; // 关键字
   InfoType otheritems; // 其他数据项
   int next;
 };

 struct SLList // 静态链表类型
 { SLCell r[MAX_SPACE]; // 静态链表的可利用空间，r[0]为头结点
   int keynum; // 记录的当前关键字个数
   int recnum; // 静态链表的当前长度
 };

 typedef int ArrType[RADIX]; // 指针数组类型
