 // c8-8.h 双链键树的存储结构。在教科书第248页
 typedef struct DLTNode // 双链树类型
 { char symbol; // 关键字符
   DLTNode *next; // 指向右兄弟结点的指针
   NodeKind kind; // 结点种类
   union // 共用体
   { Record *infoptr; // 叶子结点的记录指针
     DLTNode *first; // 分支结点的孩子链指针
   };
 }DLTNode,*DLTree;
