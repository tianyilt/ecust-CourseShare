 // c2-4.h 线性表的双向链表存储结构。在教科书第35页
 typedef struct DuLNode
 { ElemType data;
   DuLNode *prior,*next;
 }DuLNode,*DuLinkList;
