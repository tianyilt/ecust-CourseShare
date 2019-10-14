 // main5-1.cpp 检验bo5-1.cpp的主程序
 #include"c1.h"
 typedef int ElemType; // 定义数组元素类型ElemType为整型
 #include"c5-1.h" // 数组的动态顺序存储结构
 #include"bo5-1.cpp" // 顺序数组存储结构的基本操作(5个)

 void main()
 {
   Array A;
   int i,j,k,dim=3,bound1=3,bound2=4,bound3=2; // A[3][4][2]数组
   ElemType e;
   InitArray(A,dim,bound1,bound2,bound3); // 构造3×4×2的三维数组A
   printf("A.bounds=");
   for(i=0;i<dim;i++) // 顺序输出A.bounds
     printf("%d ",*(A.bounds+i));
   printf("\nA.constants=");
   for(i=0;i<dim;i++) // 顺序输出A.constants
     printf("%d ",*(A.constants+i));
   printf("\n%d页%d行%d列矩阵元素如下:\n",bound1,bound2,bound3);
   for(i=0;i<bound1;i++)
   { for(j=0;j<bound2;j++)
     { for(k=0;k<bound3;k++)
       { Assign(A,i*100+j*10+k,i,j,k); // 将i×100+j×10+k赋值给A[i][j][k]
         Value(e,A,i,j,k); // 将A[i][j][k]的值赋给e
         printf("A[%d][%d][%d]=%2d ",i,j,k,e); // 输出A[i][j][k]
       }
       printf("\n");
     }
     printf("\n");
   }
   printf("A.base=\n");
   for(i=0;i<bound1*bound2*bound3;i++) // 顺序输出A.base
   { printf("%4d",*(A.base+i));
     if(i%(bound2*bound3)==bound2*bound3-1)
       printf("\n");
   }
   printf("A.dim=%d\n",A.dim);
   DestroyArray(A);
}

