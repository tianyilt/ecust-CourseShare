 // c6-2.h 二叉树的二叉链表存储结构。在教科书第127页
 typedef struct BiTNode
 { TElemType data; // 结点的值
   BiTNode *lchild,*rchild; // 左右孩子指针
 }BiTNode,*BiTree;
