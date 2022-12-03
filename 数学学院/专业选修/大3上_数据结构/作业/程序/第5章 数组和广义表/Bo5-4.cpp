 // bo5-4.cpp 行逻辑链接稀疏矩阵(存储结构由c5-3.h定义)的基本操作(4个)，包括算法5.3
 Status CreateSMatrix(RLSMatrix &M)
 { // 创建稀疏矩阵M
   int i,j;
   Triple T;
   Status k;
   printf("请输入矩阵的行数,列数,非零元素个数：");
   scanf("%d,%d,%d",&M.mu,&M.nu,&M.tu);
   if(M.tu>MAX_SIZE||M.mu>MAX_RC) // 矩阵M的非零元个数太多或行数太多
     return ERROR;
   M.data[0].i=0; // 为以下比较做准备
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
     M.data[i]=T; // 将输入正确的值赋给M的相应存储单元
   }
   for(i=1;i<=M.mu;i++) // 给rpos[]赋初值1(每行第1个非零元素的初始位置)
     M.rpos[i]=1;
   for(i=1;i<=M.tu;i++) // 对于每个非零元素，按行统计，并记入rpos[]
     for(j=M.data[i].i+1;j<=M.mu;j++) // 从非零元素所在行的下一行起
       M.rpos[j]++; // 每行第1个非零元素的位置+1
   return OK;
 }

 Status AddSMatrix(RLSMatrix M,RLSMatrix N,RLSMatrix &Q)
 { // 求稀疏矩阵的和Q=M+N
   int k,p,q,up,uq;
   if(M.mu!=N.mu||M.nu!=N.nu) // M、N两稀疏矩阵行或列数不同
     return ERROR;
   Q.mu=M.mu; // 设置稀疏矩阵Q的行数和列数
   Q.nu=M.nu;
   Q.tu=0; // 矩阵Q非零元素个数初值
   for(k=1;k<=M.mu;++k) // 对于每一行，k指示行号
   { Q.rpos[k]=Q.tu+1; // 矩阵Q第k行的第1个元素的位置
     p=M.rpos[k]; // p指示矩阵M第k行当前元素的序号
     q=N.rpos[k]; // q指示矩阵N第k行当前元素的序号
     if(k<M.mu) // 不是最后一行
     { up=M.rpos[k+1]; // 下一行的第1个元素的位置是本行元素的上界
       uq=N.rpos[k+1];
     }
     else // 是最后一行
     { up=M.tu+1; // 给最后1行设上界
       uq=N.tu+1;
     }
     while(p<up&&q<uq) // 矩阵M、N均有第k行元素未处理
       switch(comp(M.data[p].j,N.data[q].j)) // 比较两当前元素的列值关系
       { // 矩阵M当前元素的列<矩阵N当前元素的列，将M的当前元素值赋给矩阵Q，p向后移
         case -1:Q.data[++Q.tu]=M.data[p++];
                 break;
         case  0:if(M.data[p].e+N.data[q].e!=0)
                 { // 矩阵M当前元素的列=矩阵N当前元素的列，如果和不为0
                   Q.data[++Q.tu]=M.data[p]; // 将M的当前元素值赋给矩阵Q
                   Q.data[Q.tu].e+=N.data[q].e; // 将N的当前元素值中成员e的值加入其中
                 }
                 p++; // p、q均向后移，无论和是否为0
                 q++;
                 break;
         // 矩阵M当前元素的列>矩阵N当前元素的列，将N的当前元素值赋给矩阵Q，q向后移
         case  1:Q.data[++Q.tu]=N.data[q++];
       } // 以下2个循环最多执行1个
     while(p<M.rpos[k+1]&&p<=M.tu) // N的第k行元素已全部处理，M还有第k行的元素未处理
       Q.data[++Q.tu]=M.data[p++]; // 将M的当前值赋给Q，p向后移
     while(q<N.rpos[k+1]&&q<=N.tu) // M的第k行元素已全部处理，N还有第k行的元素未处理
       Q.data[++Q.tu]=N.data[q++]; // 将N的当前值赋给Q，q向后移
   }
   if(Q.tu>MAX_SIZE) // 非零元素个数太多
     return ERROR;
   else
     return OK;
 }

 void TransposeSMatrix(RLSMatrix M,RLSMatrix &T)
 { // 求稀疏矩阵M的转置矩阵T
   int i,j,k,num[MAX_RC+1]; // [0]不用
   T.mu=M.nu; // 矩阵T的行数=矩阵M的列数
   T.nu=M.mu; // 矩阵T的列数=矩阵M的行数
   T.tu=M.tu; // 矩阵T的非零元素个数=矩阵M的非零元素个数
   if(T.tu) // 矩阵非空
   { for(i=1;i<=T.mu;++i) // 从矩阵T的第1行到最后一行
       num[i]=0; // 矩阵T每行非零元素个数，初值设置为0
     for(i=1;i<=M.tu;++i) // 对于M中的每一个非零元素，按列统计
       ++num[M.data[i].j]; // num[]=T的每行(M的每列)非零元素个数
     T.rpos[1]=1; // 矩阵T中第1行的第1个非零元素的序号是1
     for(i=2;i<=T.mu;++i) // 从矩阵T的第2行到最后一行
       T.rpos[i]=T.rpos[i-1]+num[i-1]; // 求T中第i行的第1个非零元素的序号
     for(i=1;i<=T.mu;++i)
       num[i]=T.rpos[i]; // num[]=M的当前非零元素在T中应存放的位置
     for(i=1;i<=M.tu;++i) // 对于M中的每一个非零元素
     { j=M.data[i].j; // 在矩阵T中的行数
       k=num[j]++; // 在矩阵T中的序号，num[j]+1
       T.data[k].i=M.data[i].j; // 将M.data[i]行列对调赋给T.data[k]
       T.data[k].j=M.data[i].i;
       T.data[k].e=M.data[i].e;
     }
   }
 }

 Status MultSMatrix(RLSMatrix M,RLSMatrix N,RLSMatrix &Q)
 { // 求稀疏矩阵乘积Q=M×N。算法5.3
   int arow,brow,p,q,ccol,ctemp[MAX_RC+1],t,tp;
   if(M.nu!=N.mu) // 矩阵M和N无法相乘
     return ERROR;
   Q.mu=M.mu; // Q的行数=M的行数
   Q.nu=N.nu; // Q的列数=N的列数
   Q.tu=0; // Q的非零元素个数的初值为0
   if(M.tu*N.tu!=0) // Q是非零矩阵
     for(arow=1;arow<=M.mu;++arow) // 对M的每一行，arow是M的当前行
     { for(ccol=1;ccol<=Q.nu;++ccol) // 从Q的第1列到最后一列
         ctemp[ccol]=0; // Q的当前行的各列元素累加器清零
       Q.rpos[arow]=Q.tu+1; // Q当前行的第1个元素位于上一行最后1个元素之后
       if(arow<M.mu) // 不是最后一行
         tp=M.rpos[arow+1]; // 下一行的第1个元素的位置是本行元素的上界
       else // 是最后一行
         tp=M.tu+1; // 给最后一行设上界
       for(p=M.rpos[arow];p<tp;++p) // 对M当前行中每一个非零元
       { brow=M.data[p].j; // 找到对应元在N中的行号(M当前元的列号)
         if(brow<N.mu) // 不是最后一行
           t=N.rpos[brow+1]; // 下一行的第1个元素的位置是本行元素的上界
         else // 不是最后一行
           t=N.tu+1; // 给最后一行设上界
         for(q=N.rpos[brow];q<t;++q) // 对N当前行中每一个非零元
         { ccol=N.data[q].j; // 乘积元素在Q中的列号
           ctemp[ccol]+=M.data[p].e*N.data[q].e; // 将乘积累加到Q的arow行ccol列中
         }
       } // 求得Q中第arow行的所有列的元素值，存于ctemp[]中
       for(ccol=1;ccol<=Q.nu;++ccol) // 对于第arow行的所有列，只存储其中的非零元
         if(ctemp[ccol]) // 该列的值不为0
         { if(++Q.tu>MAX_SIZE) // Q的非零元素个数+1，如果非零元个数太多
             return ERROR;
           Q.data[Q.tu].i=arow; // 将Q[i][j]按顺序存入稀疏矩阵Q
           Q.data[Q.tu].j=ccol;
           Q.data[Q.tu].e=ctemp[ccol];
         }
     }
   return OK;
 }

 Status MultSMatrix1(RLSMatrix M,RLSMatrix N,RLSMatrix &Q)
 { // 另一种求稀疏矩阵乘积Q=M×N的方法(不使用临时数组，利用N的转秩矩阵T)
   int i,j,q,p,up,uq;
   ElemType Qs; // 矩阵单元Q[i][j]的临时存放处
   RLSMatrix T; // N的转秩矩阵
   if(M.nu!=N.mu) // 矩阵M和N无法相乘
     return ERROR;
   Q.mu=M.mu; // Q的行数=M的行数
   Q.nu=N.nu; // Q的列数=N的列数
   Q.tu=0; // Q的非零元素个数的初值为0
   TransposeSMatrix(N,T); // T是N的转秩矩阵
   for(i=1;i<=Q.mu;i++) // 对于Q的每一行
     for(j=1;j<=Q.nu;j++) // 对于Q的每一列，求Q[i][j]
     { Qs=0; // Q[i][j]的初值为0
       p=M.rpos[i]; // p指示矩阵M在i行的第1个非零元素的位置
       q=T.rpos[j]; // q指示矩阵T在j行(N在j列)的第1个非零元素的位置
       if(i<M.mu) // 不是最后一行
         up=M.rpos[i+1]; // 下一行的第1个元素的位置是本行元素的上界
       else // 是最后一行
         up=M.tu+1; // 给最后一行设上界
       if(j<T.mu) // 不是最后一行
         uq=T.rpos[j+1]; // 下一行的第1个元素的位置是本行元素的上界
       else // 是最后一行
         uq=T.tu+1; // 给最后一行设上界
       while(p<up&&q<uq) // p、q分别指示矩阵M、T中第i、j行元素
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
       { if(++Q.tu>MAX_SIZE) // Q的非零元素个数+1，如果非零元个数太多
           return ERROR;
         Q.data[Q.tu].i=i; // 将Q[i][j]按顺序存入稀疏矩阵Q
         Q.data[Q.tu].j=j;
         Q.data[Q.tu].e=Qs;
       }
     }
   return OK;
 }
