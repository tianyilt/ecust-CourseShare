 // c8-11.h 开放定址哈希表的存储结构。在教科书第259页
 int hashsize[]={11,19,29,37}; // 哈希表容量递增表，一个合适的素数序列
 struct HashTable
 { ElemType *elem; // 数据元素存储基址，动态分配数组
   int count; // 当前数据元素个数
   int sizeindex; // hashsize[sizeindex]为当前容量
 };

 #define SUCCESS 1
 #define UNSUCCESS 0
 #define DUPLICATE -1
