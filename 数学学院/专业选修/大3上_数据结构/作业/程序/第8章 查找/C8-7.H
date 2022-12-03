 // c8-7.h 键树记录的存储结构。在教科书第248页
 #define MAX_KEY_LEN 16 // 关键字串的最大长度
 struct KeyType // 关键字串类型，类似串的定长顺序存储结构
 { char ch[MAX_KEY_LEN]; // 关键字串
   int num; // 关键字串长度
 };

 enum NodeKind{LEAF,BRANCH}; // 结点种类：{叶子,分支}
