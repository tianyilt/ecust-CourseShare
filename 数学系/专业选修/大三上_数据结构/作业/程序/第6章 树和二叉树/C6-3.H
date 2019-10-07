 // c6-3.h 二叉树的二叉线索存储结构。在教科书第133页
 enum PointerTag // 枚举
 {Link,Thread}; // Link(0)：指针，Thread(1)：线索
 struct BiThrNode
 { TElemType data; // 结点的值
   BiThrNode *lchild,*rchild; // 左右孩子指针
   PointerTag LTag:2; // 左标志，占2bit，修改
   PointerTag RTag:2; // 右标志，占2bit，修改
 };
 typedef BiThrNode *BiThrTree;
