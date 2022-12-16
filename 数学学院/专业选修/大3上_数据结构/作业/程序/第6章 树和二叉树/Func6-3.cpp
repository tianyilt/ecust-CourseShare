 // func6-3.cpp 算法6.12的前半部分
   int m,i,s1,s2;
   unsigned c;
   HuffmanTree p;
   char *cd;
   if(n<=1) // 叶子结点数不大于n
     return;
   m=2*n-1; // n个叶子结点的赫夫曼树共有m个结点
   HT=(HuffmanTree)malloc((m+1)*sizeof(HTNode)); // 0号单元未用
   for(p=HT+1,i=1;i<=n;++i,++p,++w) // 从1号单元开始到n号单元，给叶子结点赋值
   { // p的初值指向1号单元
     (*p).weight=*w; // 赋权值
     (*p).parent=0; // 双亲域为空(是根结点)
     (*p).lchild=0; // 左右孩子为空(是叶子结点，即单结点树)
     (*p).rchild=0;
   }
   for(;i<=m;++i,++p) // i从n+1到m
     (*p).parent=0; // 其余结点的双亲域初值为0
   for(i=n+1;i<=m;++i) // 建赫夫曼树
   { // 在HT[1～i-1]中选择parent为0且weight最小的两个结点，其序号分别为s1和s2
     select(HT,i-1,s1,s2);
     HT[s1].parent=HT[s2].parent=i; // i号单元是s1和s2的双亲
     HT[i].lchild=s1; // i号单元的左右孩子分别是s1和s2
     HT[i].rchild=s2;
     HT[i].weight=HT[s1].weight+HT[s2].weight; // i号单元的权值是s1和s2的权值之和
   }
