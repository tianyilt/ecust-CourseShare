 // c5-1.h 数组的顺序存储结构。在教科书第93页
 #define MAX_ARRAY_DIM 8 // 假设数组维数的最大值为8
 struct Array
 { ElemType *base; // 数组元素基址，由InitArray分配
   int dim; // 数组维数
   int *bounds; // 数组维界基址，由InitArray分配
   int *constants; // 数组映象函数常量基址，由InitArray分配
 };
