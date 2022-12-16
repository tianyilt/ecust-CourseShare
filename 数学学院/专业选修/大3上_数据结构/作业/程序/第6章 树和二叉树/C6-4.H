 // c6-4.h 树的二叉链表(孩子-兄弟)存储结构。在教科书第136页
 typedef struct CSNode // 结点类型
 { TElemType data; // 结点的值
   CSNode *firstchild,*nextsibling;
 }CSNode,*CSTree;
