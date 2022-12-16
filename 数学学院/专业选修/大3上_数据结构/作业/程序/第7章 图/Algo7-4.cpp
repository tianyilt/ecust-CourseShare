 // algo7-4.cpp 实现算法7.9的程序
 #include"c1.h"
 #include"func7-1.cpp" // 包括顶点信息类型的定义及对它的操作
 #include"func7-2.cpp" // 包括弧(边)的相关信息类型的定义及对它的操作
 #include"c7-1.h" // 图的数组(邻接矩阵)存储结构
 #include"bo7-1.cpp" // 图的数组(邻接矩阵)存储结构的基本操作

 typedef struct
 { // 记录从顶点集U到V-U的代价最小的边的辅助数组定义
   int adjvex; // 顶点集U中到该点为最小权值的那个顶点的序号
   VRType lowcost; // 那个顶点到该点的权值(最小权值)
 }minside[MAX_VERTEX_NUM];

 int minimum(minside SZ,MGraph G)
 { // 求SZ.lowcost的最小正值，并返回其在SZ中的序号
   int i=0,j,k,min;
   while(!SZ[i].lowcost) // 找第1个值不为0的SZ[i].lowcost的序号
     i++;
   min=SZ[i].lowcost; // min标记第1个不为0的值
   k=i; // k标记该值的序号
   for(j=i+1;j<G.vexnum;j++) // 继续向后找
     if(SZ[j].lowcost>0&&SZ[j].lowcost<min) // 找到新的更小的正值
     { min=SZ[j].lowcost; // min标记此正值
       k=j; // k标记此正值的序号
     }
   return k; // 返回当前最小正值在SZ中的序号
 }

 void MiniSpanTree_PRIM(MGraph G,VertexType u)
 { // 用普里姆算法从顶点u出发构造网G的最小生成树T，输出T的各条边。算法7.9
   int i,j,k;
   minside closedge;
   k=LocateVex(G,u); // 顶点u的序号
   for(j=0;j<G.vexnum;++j) // 辅助数组初始化
   { closedge[j].adjvex=k; // 顶点u的序号赋给closedge[j].adjvex
     closedge[j].lowcost=G.arcs[k][j].adj; // 顶点u到该点的权值
   }
   closedge[k].lowcost=0; // 初始，U={u}。U中的顶点到集合U的权值为0
   printf("最小代价生成树的各条边为\n");
   for(i=1;i<G.vexnum;++i) // 选择其余G.vexnum-1个顶点(i仅计数)
   { k=minimum(closedge,G); // 求出最小生成树T的下一个结点：第k顶点
     printf("(%s-%s)\n",G.vexs[closedge[k].adjvex].name,G.vexs[k].name);
     // 输出最小生成树T的边
     closedge[k].lowcost=0; // 第k顶点并入U集
     for(j=0;j<G.vexnum;++j)
       if(G.arcs[k][j].adj<closedge[j].lowcost) // 新顶点并入U集后重新选择最小边
       { closedge[j].adjvex=k;
         closedge[j].lowcost=G.arcs[k][j].adj;
       }
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
   MiniSpanTree_PRIM(g,g.vexs[0]);
   // 用普里姆算法从第1个顶点出发输出g的最小生成树的各条边
 }
