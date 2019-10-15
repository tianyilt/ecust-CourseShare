 // main5-3.cpp 检验bo5-3.cpp和bo5-4.cpp的主程序
 #include"c1.h"
 typedef int ElemType; // 定义矩阵元素类型ElemType为整型
 #include"c5-3.h" // 稀疏矩阵的三元组行逻辑链接的顺序表存储结构
 #include"func5-1.cpp" // comp()函数
 #include"bo5-4.cpp" // 行逻辑链接稀疏矩阵存储结构的基本操作(4个)
 #define TSMatrix RLSMatrix // 将bo5-3.cpp和func5-2.cpp中的TSMatrix改为RLSMatrix
 #include"bo5-3.cpp" // 也可用于行逻辑链接结构三元组稀疏矩阵的基本操作(4个)
 //#define FLAG // 加此句在func5-2.cpp中调用MultSMatrix1()，不加则调用MultSMatrix()
 #include"func5-2.cpp" // 主函数
