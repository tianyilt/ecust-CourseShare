 // c5-4.h 广义表的头尾链表存储结构。在教科书第109页
 enum ElemTag{ATOM,LIST};
 // ATOM==0：原子,LIST==1：子表
 typedef struct GLNode
 { ElemTag tag; // 公共部分，用于区分原子结点和表结点
   union // 原子结点和表结点的联合部分
   { AtomType atom; // atom是原子结点的值域，AtomType由用户定义
     struct
     { GLNode *hp,*tp;
     }ptr; // ptr是表结点的指针域，prt.hp和ptr.tp分别指向表头和表尾(表头之外的其余元素)
   };
 }*GList,GLNode; // 广义表类型
