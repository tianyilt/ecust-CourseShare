 // c5-5.h 广义表的扩展线性链表存储结构。在教科书第110页
 enum ElemTag{ATOM,LIST}; // ATOM==0：原子，LIST==1：子表
 typedef struct GLNode1
 { ElemTag tag; // 公共部分，用于区分原子结点
                // 和表结点
   union // 原子结点和表结点的联合部分
   { AtomType atom; // 原子结点的值域
     GLNode1 *hp; // 表结点的表头指针
   };
   GLNode1 *tp; // 相当于线性链表的next，指向下一个元素结点
 }*GList1,GLNode1; // 广义表类型GList1是一种扩展的线性链表
