 // bo2-4.cpp 不设头结点的单链表(存储结构由c2-2.h定义)的部分基本操作(2个)
 Status PriorElem(LinkList L,ElemType cur_e,ElemType &pre_e)
 { // 初始条件：线性表L已存在
   // 操作结果：若cur_e是L的数据元素，且不是第一个，则用pre_e返回它的前驱，返回OK；
   //           否则操作失败，pre_e无定义，返回ERROR
   LinkList q,p=L; // p指向第1个结点
   while(p->next) // p所指结点有后继
   { q=p->next; // q指向p的后继
     if(q->data==cur_e) // p的后继为cur_e
     { pre_e=p->data; // 将p所指元素的值赋给pre_e
       return OK; // 成功返回OK
     }
     p=q; // p的后继不为cur_e，p向后移
   }
   return ERROR; // 操作失败，返回ERROR
 }

 Status NextElem(LinkList L,ElemType cur_e,ElemType &next_e)
 { // 初始条件：线性表L已存在
   // 操作结果：若cur_e是L的数据元素，且不是最后一个，则用next_e返回它的后继，返回OK，
   //           否则操作失败，next_e无定义，返回ERROR
   LinkList p=L; // p指向第1个结点
   while(p->next) // p所指结点有后继
   { if(p->data==cur_e) // p所指结点的值为cur_e
     { next_e=p->next->data; // 将p所指结点的后继结点的值赋给next_e
       return OK; // 成功返回OK
     }
     p=p->next; // p指向下一个结点
   }
   return ERROR; // 操作失败，返回ERROR
 }
