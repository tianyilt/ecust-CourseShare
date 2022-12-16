 // algo7-5.cpp 克鲁斯卡尔算法求无向连通网的最小生成树的程序
 #include"c1.h"
 #include"func7-1.cpp" // 包括顶点信息类型的定义及对它的操作
 #include"func7-2.cpp" // 包括弧(边)的相关信息类型的定义及对它的操作
 #include"c7-1.h" // 图的数组(邻接矩阵)存储结构
 #include"bo7-1.cpp" // 图的数组(邻接矩阵)存储结构的基本操作
 struct side // 图的边信息存储结构
 { int a,b; // 边的2顶点的序号
   VRType weight; // 边的权值
 };
 void Kruskal(MGraph G)
 { // 克鲁斯卡尔算法求无向连通网G的最小生成树
   int set[MAX_VERTEX_NUM],senumber=0,sb,i,j,k;
   side se[MAX_VERTEX_NUM*(MAX_VERTEX_NUM-1)/2]; // 存储边信息的一维数组
   for(i=0;i<G.vexnum;++i) // 查找所有的边，并根据权值升序插到se中
     for(j=i+1;j<G.vexnum;++j) // 无向网，只在上三角查找
       if(G.arcs[i][j].adj<INFINITY) // 顶点[i][j]之间有边
       { k=senumber-1; // k指向se的最后一条边
         while(k>=0) // k仍指向se的边
           if(se[k].weight>G.arcs[i][j].adj)
           { // k所指边的权值大于刚找到的边的权值
             se[k+1]=se[k]; // k所指的边向后移
             k--; // k指向前一条边
           }
           else // k所指边的权值不大于刚找到的边的权值
             break; // 跳出while循环
         se[k+1].a=i; // 将刚找到的边的信息按权值升序插入se
         se[k+1].b=j;
         se[k+1].weight=G.arcs[i][j].adj;
         senumber++; // se的边数+1
       }
   printf("i se[i].a se[i].b se[i].weight\n");
   for(i=0;i<senumber;i++)
     printf("%d %4d %7d %9d\n",i,se[i].a,se[i].b,se[i].weight);
   for(i=0;i<G.vexnum;i++) // 对于所有顶点
     set[i]=i; // 设置初态，各顶点分别属于各个集合
   printf("最小代价生成树的各条边为\n");
   j=0; // j指示se当前要并入最小生成树的边的序号，初值为0
   k=0; // k指示当前构成最小生成树的边数
   while(k<G.vexnum-1) // 最小生成树应有G.vexnum-1条边
   { if(set[se[j].a]!=set[se[j].b]) // j所指边的2顶点不属于同一个集合
     { printf("(%s-%s)\n",G.vexs[se[j].a].name,G.vexs[se[j].b].name); // 输出该边
       sb=set[se[j].b]; // 将该边的顶点se[j].b当前所在的集合赋给sb
       for(i=0;i<G.vexnum;i++) // 对于所有顶点
         if(set[i]==sb) // 与顶点se[j].b在同一个集合中
           set[i]=set[se[j].a]; // 将此顶点并入顶点se[j].a所在的集合中
       k++; // 当前构成最小生成树的边数+1
     }
     j++; // j指示se下一条要并入最小生成树的边的序号
   }
 }

 void main()
 {
   MGraph g;
   char filename[13]; // 存储数据文件名(包括路径)
   printf("请输入数据文件名：");
   scanf("%s",filename);
   CreateFromFile(g,filename,0); // 创建无相关信息的网
   Display(g); // 输出无向网g
   Kruskal(g); // 用克鲁斯卡尔算法输出g的最小生成树的各条边
 }
