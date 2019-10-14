 // bo5-2.cpp 三元组稀疏矩阵的基本操作(4个)，包括算法5.1
 Status CreateSMatrix(TSMatrix &M)
 { // 创建稀疏矩阵M
   int i;
   Triple T;
   Status k;
   printf("请输入矩阵的行数,列数,非零元素个数：");
   scanf("%d,%d,%d",&M.mu,&M.nu,&M.tu);
   if(M.tu>MAX_SIZE) // 非零元个数太多
     return ERROR;
   M.data[0].i=0; // 为以下比较顺序做准备
   for(i=1;i<=M.tu;i++) // 依次输入M.tu个非零元素
   { do
     { printf("请按行序顺序输入第%d个非零元素所在的行(1～%d),列(1～%d),元素值：",
       i,M.mu,M.nu);
       scanf("%d,%d,%d",&T.i,&T.j,&T.e);
       k=0; // 输入值的范围正确的标志
       if(T.i<1||T.i>M.mu||T.j<1||T.j>M.nu) // 行或列超出范围
         k=1;
       if(T.i<M.data[i-1].i||T.i==M.data[i-1].i&&T.j<=M.data[i-1].j)
         k=1; // 行或列的顺序有错
     }while(k); // 输入值的范围不正确则重新输入
     M.data[i]=T; // 将输入正确的值赋给三元组结构体M的相应单元
   }
   return OK;
 }

 Status AddSMatrix(TSMatrix M,TSMatrix N,TSMatrix &Q)
 { // 求稀疏矩阵的和Q=M+N
   int m=1,n=1,q=0;
   if(M.mu!=N.mu||M.nu!=N.nu) // M、N两稀疏矩阵行或列数不同
     return ERROR;
   Q.mu=M.mu; // 设置稀疏矩阵Q的行数和列数
   Q.nu=M.nu;
   while(m<=M.tu&&n<=N.tu) // 矩阵M和N的元素都未处理完
     switch(comp(M.data[m].i,N.data[n].i)) // 比较两当前元素的行值关系
     { case -1:Q.data[++q]=M.data[m++]; // 矩阵M的行值小，将M的当前元素值赋给矩阵Q
               break;
       case  0:switch(comp(M.data[m].j,N.data[n].j))
               { // M、N矩阵当前元素的行值相等，继续比较两当前元素的列值关系
                 case -1:Q.data[++q]=M.data[m++]; // 矩阵M的列值小，将M的值赋给矩阵Q
                         break;
                 case  0: // M、N矩阵当前非零元素的行列均相等，将两元素值求和并赋给矩阵Q
                         Q.data[++q]=M.data[m++];
                         Q.data[q].e+=N.data[n++].e;
                         if(Q.data[q].e==0) // 两元素值之和为0，不存入稀疏矩阵
                           q--;
                         break;
                 case  1:Q.data[++q]=N.data[n++]; // 矩阵N的列值小，将N的值赋给矩阵Q
               }
               break;
       case  1:Q.data[++q]=N.data[n++]; // 矩阵N的行值小，将N的当前元素值赋给矩阵Q
     } // 以下2个循环最多执行1个
   while(m<=M.tu) // 矩阵N的元素已全部处理完毕，处理矩阵M的元素
     Q.data[++q]=M.data[m++];
   while(n<=N.tu) // 矩阵M的元素已全部处理完毕，处理矩阵N的元素
     Q.data[++q]=N.data[n++];
   if(q>MAX_SIZE) // 非零元素个数太多
     return ERROR;
   Q.tu=q; // 矩阵Q的非零元素个数
   return OK;
 }

 void TransposeSMatrix(TSMatrix M,TSMatrix &T)
 { // 求稀疏矩阵M的转置矩阵T。修改算法5.1
   int p,col,q=1; // q指示转置矩阵T的当前元素，初值为1
   T.mu=M.nu; // 矩阵T的行数=矩阵M的列数
   T.nu=M.mu; // 矩阵T的列数=矩阵M的行数
   T.tu=M.tu; // 矩阵T的非零元素个数=矩阵M的非零元素个数
   if(T.tu) // 矩阵非空
     for(col=1;col<=M.nu;++col) // 从矩阵T的第1行到最后一行
       for(p=1;p<=M.tu;++p) // 对于矩阵M的所有元素
         if(M.data[p].j==col) // 该元素的列数=当前矩阵T的行数
         { T.data[q].i=M.data[p].j; // 将矩阵M的值行列对调赋给T的当前元素
           T.data[q].j=M.data[p].i;
           T.data[q++].e=M.data[p].e; // 转置矩阵T的当前元素指针+1
         }
 }

 Status MultSMatrix(TSMatrix M,TSMatrix N,TSMatrix &Q)
 { // 求稀疏矩阵的乘积Q=M×N
   int i,j,q,p;
   ElemType Qs; // 矩阵单元Q[i][j]的临时存放处
   TSMatrix T; // N的转秩矩阵
   if(M.nu!=N.mu) // 矩阵M和N无法相乘
     return ERROR;
   Q.mu=M.mu; // Q的行数=M的行数
   Q.nu=N.nu; // Q的列数=N的列数
   Q.tu=0; // Q的非零元素个数的初值为0
   TransposeSMatrix(N,T); // T是N的转秩矩阵
   for(i=1;i<=Q.mu;i++) // 对于M的每一行，求Q[i][]
   { q=1; // q指向T的第1个非零元素
     for(j=1;j<=T.mu;j++) // 对于T的每一行(即N的每一列)，求Q[i][j]
     { Qs=0; // 设置Q[i][j]的初值为0
       p=1; // p指向M的第1个非零元素
       while(M.data[p].i<i) // 使p指向矩阵M的第i行的第1个非零元素
         p++;
       while(T.data[q].i<j) // 使q指向矩阵T的第j行(即矩阵N的第j列)的第1个非零元素
         q++;
       while(p<=M.tu&&q<=T.tu&&M.data[p].i==i&&T.data[q].i==j)
       // [p]仍是M的第i行的非零元素且[q]仍是T的第j行(即N的第j列)的非零元素
         switch(comp(M.data[p].j,T.data[q].j))
         { // 比较M矩阵当前元素的列值和T矩阵当前元素的列值(即N矩阵当前元素的行值)
           case -1:p++; // M矩阵当前元素的列值<T(N)矩阵当前元素的列(行)值，p向后移
                   break;
           // M当前元素的列值=T(N)当前元素的列(行)值，则两值相乘并累加到Qs，p、q均向后移
           case  0:Qs+=M.data[p++].e*T.data[q++].e;
                   break;
           case  1:q++; // M矩阵当前元素的列值>T(N)矩阵当前元素的列(行)值，q向后移
         }
       if(Qs) // Q[i][j]不为0
       { if(++Q.tu>MAX_SIZE) // Q的非零元素个数+1，如果非零元素个数太多
           return ERROR;
         Q.data[Q.tu].i=i; // 将Q[i][j]按顺序存入稀疏矩阵Q
         Q.data[Q.tu].j=j;
         Q.data[Q.tu].e=Qs;
       }
     }
   }
   return OK;
 }
