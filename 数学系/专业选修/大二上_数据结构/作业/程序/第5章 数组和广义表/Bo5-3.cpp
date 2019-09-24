 // bo5-3.cpp 三元组稀疏矩阵的基本操作(4个)，也可用于行逻辑链接结构
 void DestroySMatrix(TSMatrix &M)
 { // 销毁稀疏矩阵M
   M.mu=M.nu=M.tu=0;
 }

 void PrintSMatrix(TSMatrix M)
 { // 按矩阵形式输出M
   int i,j,k=1; // 非零元计数器，初值为1
   Triple *p=M.data+1; // p指向M的第1个非零元素
   for(i=1;i<=M.mu;i++) // 从第1行到最后一行
   { for(j=1;j<=M.nu;j++) // 从第1列到最后一列
       if(k<=M.tu&&p->i==i&&p->j==j) // p指向非零元，且p所指元素为当前循环在处理元素
       { printf("%3d",(p++)->e); // 输出p所指元素的值，p指向下一个元素
         k++; // 计数器+1
       }
       else // p所指元素不是当前循环在处理元素
         printf("%3d",0); // 输出0
     printf("\n");
   }
 }

 void CopySMatrix(TSMatrix M,TSMatrix &T)
 { // 由稀疏矩阵M复制得到T
   T=M;
 }

 Status SubtSMatrix(TSMatrix M,TSMatrix N,TSMatrix &Q)
 { // 求稀疏矩阵的差Q=M-N
   int i;
   if(M.mu!=N.mu||M.nu!=N.nu) // M、N两稀疏矩阵行或列数不同
     return ERROR;
   for(i=1;i<=N.tu;++i) // 对于N的每一元素，其值乘以-1
     N.data[i].e*=-1;
   AddSMatrix(M,N,Q); // Q=M+(-N)
   return OK;
 }

