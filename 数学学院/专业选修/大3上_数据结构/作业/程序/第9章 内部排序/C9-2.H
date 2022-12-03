 // c9-2.h 顺序表类型的存储结构。在教科书第264页
 #define MAX_SIZE 20 // 一个用作示例的小顺序表的最大长度
 struct SqList // 顺序表类型
 { RedType r[MAX_SIZE+1]; // r[0]闲置或用作哨兵单元
   int length; // 顺序表长度
 };
