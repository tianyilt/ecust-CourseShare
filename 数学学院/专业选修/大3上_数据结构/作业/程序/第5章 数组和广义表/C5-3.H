 // c5-3.h 稀疏矩阵的三元组行逻辑链接的顺序表存储结构
 #define MAX_SIZE 100 // 非零元个数的最大值。在教科书第100页
 #define MAX_RC 20 // 最大行数
 struct Triple // 同c5-2.h
 { int i,j; // 行下标,列下标
   ElemType e; // 非零元素值
 };
 struct RLSMatrix
 { Triple data[MAX_SIZE+1]; // 非零元三元组表，data[0]未用
   int rpos[MAX_RC+1]; // 各行第1个非零元素的位置表，比c5-2.h增加的项
   int mu,nu,tu; // 矩阵的行数,列数,非零元个数
 };
