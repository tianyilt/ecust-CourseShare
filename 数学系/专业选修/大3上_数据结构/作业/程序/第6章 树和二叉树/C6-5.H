 // c6-5.h 赫夫曼树和赫夫曼编码的存储结构
 typedef struct // 结点的结构，在教科书第147页
 { unsigned int weight; // 结点的权值
   unsigned int parent,lchild,rchild;
 }HTNode,*HuffmanTree; // 动态分配数组存储赫夫曼树
 typedef char **HuffmanCode; // 动态分配数组存储赫夫曼编码表
