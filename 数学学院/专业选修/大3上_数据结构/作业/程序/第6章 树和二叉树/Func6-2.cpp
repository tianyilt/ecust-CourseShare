 // func6-2.cpp 程序algo6-1.cpp和algo6-2.cpp要调用的2个函数
 #define Order // 定义Order。第2行
 int min(HuffmanTree t,int i)
 { // 返回赫夫曼树t的前i个结点中权值最小的树的根结点序号，函数select()调用
   int j,m;
   unsigned int k=UINT_MAX; // k存最小权值，初值取为不小于可能的值(无符号整型最大值)
   for(j=1;j<=i;j++) // 对于前i个结点
     if(t[j].weight<k&&t[j].parent==0) // t[j]的权值小于k，又是树的根结点
     { k=t[j].weight; // t[j]的权值赋给k
       m=j; // 序号赋给m
     }
   t[m].parent=1; // 给选中的根结点的双亲赋非零值，避免第2次查找该结点
   return m; // 返回权值最小的根结点的序号
 }

 void select(HuffmanTree t,int i,int &s1,int &s2)
 { // 在赫夫曼树t的前i个结点中选择2个权值最小的树的根结点序号，s1为其中序号(权值)较小的
 #ifdef Order // 如果在主程中定义了Order，则以下语句起作用
   int j;
 #endif
   s1=min(t,i); // 权值最小的根结点序号
   s2=min(t,i); // 权值第2小的根结点序号
 #ifdef Order // 如果在主程中定义了Order，则执行下面一段程序
   if(s1>s2) // s1的序号大于s2的
   { // 交换
     j=s1;
     s1=s2; // s1是权值最小的2个中序号较小的
     s2=j; // s2是权值最小的2个中序号较小的
   }
 #endif
 }
