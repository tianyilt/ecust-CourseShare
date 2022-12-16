 // func5-2.cpp 稀疏矩阵的主函数，main5-2.cpp和main5-3.cpp调用
 void main()
 {
   TSMatrix A,B,C;
   printf("创建矩阵A：");
   CreateSMatrix(A); // 创建矩阵A
   PrintSMatrix(A); // 输出矩阵A
   CopySMatrix(A,B); // 由矩阵A复制矩阵B
   printf("由矩阵A复制矩阵B：\n");
   PrintSMatrix(B); // 输出矩阵B
   DestroySMatrix(B); // 销毁矩阵B
   printf("销毁矩阵B后：\n");
   PrintSMatrix(B); // 输出矩阵B
   printf("创建矩阵B2：(与矩阵A的行、列数相同，行、列分别为%d,%d)\n",A.mu,A.nu);
   CreateSMatrix(B); // 创建矩阵B
   PrintSMatrix(B); // 输出矩阵B
   AddSMatrix(A,B,C); // 矩阵相加，C=A+B
   printf("矩阵C1(A+B)：\n");
   PrintSMatrix(C); // 输出矩阵C
   SubtSMatrix(A,B,C); // 矩阵相减，C=A-B
   printf("矩阵C2(A-B)：\n");
   PrintSMatrix(C); // 输出矩阵C
   TransposeSMatrix(A,C); // 矩阵C是矩阵A的转秩矩阵
   printf("矩阵C3(A的转置)：\n");
   PrintSMatrix(C); // 输出矩阵C
   printf("创建矩阵A2：");
   CreateSMatrix(A); // 创建矩阵A
   PrintSMatrix(A); // 输出矩阵A
   printf("创建矩阵B3：(行数应与矩阵A2的列数相同=%d)\n",A.nu);
   CreateSMatrix(B); // 创建矩阵B
   PrintSMatrix(B); // 输出矩阵B
 #ifndef FLAG // 未定义FLAG
   MultSMatrix(A,B,C); // 矩阵相乘，C=A×B
 #else // 定义了FLAG
   MultSMatrix1(A,B,C); // 另一个矩阵相乘函数C=A×B，在bo5-3.cpp中
 #endif
   printf("矩阵C5(A×B)：\n");
   PrintSMatrix(C); // 输出矩阵C
 }
