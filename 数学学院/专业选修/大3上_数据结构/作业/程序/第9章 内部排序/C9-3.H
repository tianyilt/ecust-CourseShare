 // c9-3.h 静态链表类型。在教科书第268页
 #define SIZE 100 // 静态链表容量
 struct SLNode // 表结点类型
 { RedType rc; // 记录项
   int next; // 指针项
 };

 struct SLinkListType // 静态链表类型
 { SLNode r[SIZE]; // 0号单元为表头结点
   int length; // 链表当前长度
 };
