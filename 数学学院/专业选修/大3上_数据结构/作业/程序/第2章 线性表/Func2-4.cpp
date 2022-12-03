 // func2-4.cpp 不设头结点的单链表(存储结构由c2-2.h定义)的扩展操作(1个)，bo7-2.cpp用到
 LinkList Point(LinkList L,ElemType e,Status(*equal)(ElemType,ElemType),LinkList &p)
 { // 查找表L中与e满足equal()条件的结点。如找到，返回指向该结点的指针，p指向该结点的前驱
   // (若该结点是首元结点，则p=NULL)。如表L中无满足条件的结点，则返回NULL，p无定义。
   int j,i=LocateElem(L,e,equal); // 查找表L中与e满足equal()条件的结点
   if(i) // 找到
   { if(i==1) // 是首元结点
     { p=NULL;
       return L;
     }
     p=L; // 不是首元结点，则p指向第1个结点
     for(j=2;j<i;j++) // p指向所找结点的前驱
       p=p->next;
     return p->next; // 返回所找结点的指针
   }
   return NULL; // 未找到
 }
