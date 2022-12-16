 // algo5-2.cpp 实现算法5.2的程序
 #include"c1.h"
 typedef int ElemType; // 定义矩阵元素类型ElemType为整型
 #include"c5-2.h" // 稀疏矩阵的三元组顺序表存储结构
 #include"func5-1.cpp" // comp()函数
 #include"bo5-2.cpp" // 三元组稀疏矩阵的基本操作(4个)
 #include"bo5-3.cpp" // 也可用于行逻辑链接结构三元组稀疏矩阵的基本操作(4个)

 void FastTransposeSMatrix(TSMatrix M,TSMatrix &T)
 { // 快速求稀疏矩阵M的转置矩阵T。修改算法5.2
   int p,q,col,*num,*cpot;
   num=(int*)malloc((M.nu+1)*sizeof(int)); // 存M每列(T每行)非零元素个数([0]不用)
   cpot=(int*)malloc((M.nu+1)*sizeof(int)); // 存T每行下一个非零元素的位置([0]不用)
   T.mu=M.nu; // T的行数=M的列数
   T.nu=M.mu; // T的列数=M的行数
   T.tu=M.tu; // T的非零元素个数=M的非零元素个数
   if(T.tu) // T是非零矩阵
   { for(col=1;col<=M.nu;++col) // 从M的第1列到最后一列
       num[col]=0; // 计数器初值设为0
     for(p=1;p<=M.tu;++p) // 对于M的每一个非零元素
       ++num[M.data[p].j]; // 根据它所在的列进行统计
     cpot[1]=1; // T的第1行的第1个非零元在T.data中的序号为1
     for(col=2;col<=M.nu;++col) // 从M(T)的第2列(行)到最后一列(行)
       cpot[col]=cpot[col-1]+num[col-1]; // 求T的第col行第1个非零元在T.data中的序号
     for(p=1;p<=M.tu;++p) // 对于M的每一个非零元素
     { col=M.data[p].j; // 将其在M中的列数赋给col
       q=cpot[col]; // q指示M当前的元素在T中的序号
       T.data[q].i=M.data[p].j; // 将M当前的元素转秩赋给T
       T.data[q].j=M.data[p].i;
       T.data[q].e=M.data[p].e;
       ++cpot[col]; // T第col行的下1个非零元在T.data中的序号比当前元素的序号大1
     }
   }
   free(num); // 释放num和cpot所指向的动态存储空间
   free(cpot);
 }

 void main()
 {
   TSMatrix A,B;
   printf("创建矩阵A：");
   CreateSMatrix(A); // 创建矩阵A
   PrintSMatrix(A); // 输出矩阵A
   FastTransposeSMatrix(A,B); // B是A的转秩矩阵
   printf("矩阵B(A的快速转置)：\n");
   PrintSMatrix(B); // 输出矩阵B
 }
