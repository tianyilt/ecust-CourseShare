 // c8-9.h Trie键树的存储结构。在教科书第250页
 typedef struct TrieNode // Trie树类型
 { NodeKind kind;
   union
   { struct
     { KeyType K;
       Record *infoptr;
     }lf; // 叶子结点
     struct
     { TrieNode *ptr[LENGTH]; // LENGTH为结点的最大度，在主程定义
       int num; // 分支结点的孩子数
     }bh; // 分支结点
   };
 }TrieNode,*TrieTree;
