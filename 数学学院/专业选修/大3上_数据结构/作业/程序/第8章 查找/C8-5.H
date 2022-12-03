 // c8-5.h B_树的结点类型。在教科书第239页
 typedef struct BTNode
 { int keynum; // 结点中关键字个数，即结点的大小
   BTNode *parent; // 指向双亲结点
   KeyType key[m+1]; // 关键字向量，0号单元未用
   Record *recptr[m+1]; // 记录指针向量，0号单元未用
   BTNode *ptr[m+1]; // 子树指针向量
 }BTNode,*BTree; // B_树结点和B_树的类型
