 // algo7-9.cpp 实现算法7.15的程序。迪杰斯特拉算法的实现
 #include"c1.h"
 #include"func7-1.cpp" // 包括顶点信息类型的定义及对它的操作
 #include"func7-2.cpp" // 包括弧(边)的相关信息类型的定义及对它的操作
 #include"c7-1.h" // 图的数组(邻接矩阵)存储结构
 #include"bo7-1.cpp" // 图的数组(邻接矩阵)存储结构的基本操作
 typedef Status PathMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; // 路径矩阵，二维数组
 typedef VRType ShortPathTable[MAX_VERTEX_NUM]; // 最短距离表，一维数组

 void ShortestPath_DIJ(MGraph G,int v0,PathMatrix P,ShortPathTable D)
 { // 用Dijkstra算法求有向网G的v0顶点到其余顶点v的最短路径P[v]及带权长度D[v]。
   // 若P[v][w]为TRUE，则w是从v0到v当前求得最短路径上的顶点。
   // final[v]为TRUE当且仅当v∈S，即已经求得从v0到v的最短路径。算法7.15
   int v,w,i,j;
   VRType min;
   Status final[MAX_VERTEX_NUM];
   // 辅助矩阵，为真表示该顶点到v0的最短距离已求出，初值为假
   for(v=0;v<G.vexnum;++v)
   { final[v]=FALSE; // 设初值
     D[v]=G.arcs[v0][v].adj; // D[]存放v0到v的最短距离，初值为v0到v的直接距离
     for(w=0;w<G.vexnum;++w)
       P[v][w]=FALSE; // 设P[][]初值为FALSE，没有路径
     if(D[v]<INFINITY) // v0到v有直接路径
       P[v][v0]=P[v][v]=TRUE;
       // 一维数组p[v][]表示源点v0到v最短路径通过的顶点，目前通过v0和v两顶点
   }
   D[v0]=0; // v0到v0距离为0
   final[v0]=TRUE; // v0顶点并入S集
   for(i=1;i<G.vexnum;++i) // 对于其余G.vexnum-1个顶点
   { // 开始主循环，每次求得v0到某个顶点v的最短路径，并将v并入S集
     min=INFINITY; // 当前所知离v0顶点的最近距离，设初值为∞
     for(w=0;w<G.vexnum;++w) // 对所有顶点检查
       if(!final[w]&&D[w]<min) // 在S集之外的顶点(其final[]= FALSE)中
       { // 找离v0最近的顶点w，并将其赋给v，距离赋给min
         v=w; // 在S集之外的离v0最近的顶点序号
         min=D[w]; // 最近的距离
       }
     final[v]=TRUE; // 将v并入S集
     for(w=0;w<G.vexnum;++w) // 根据新并入的顶点，更新不在S集的顶点到v0的距离和路径数组
       if(!final[w]&&min<INFINITY&&G.arcs[v][w].adj<INFINITY&&(min+
       G.arcs[v][w].adj<D[w]))
       { // w不属于S集且v0→v→w的距离＜目前v0→w的距离
         D[w]=min+G.arcs[v][w].adj; // 更新D[w]
         for(j=0;j<G.vexnum;++j)
         // 修改P[w]，v0到w经过的顶点包括v0到v经过的顶点再加上顶点w
           P[w][j]=P[v][j];
         P[w][w]=TRUE;
       }
   }
 }

 void main()
 {
   int i,j;
   MGraph g;
   PathMatrix p; // 二维数组，路径矩阵
   ShortPathTable d; // 一维数组，最短距离表
   CreateDN(g); // 构造有向网g
   Display(g); // 输出有向网g
   ShortestPath_DIJ(g,0,p,d);
   // 以g中序号为0的顶点为源点，求其到其余各顶点的最短距离。存于d中
   printf("最短路径数组p[i][j]如下：\n");
   for(i=0;i<g.vexnum;++i)
   { for(j=0;j<g.vexnum;++j)
       printf("%2d",p[i][j]);
     printf("\n");
   }
   printf("%s到各顶点的最短路径长度为\n",g.vexs[0].name);
   for(i=0;i<g.vexnum;++i)
     if(i!=0)
       printf("%s→%s：%d\n",g.vexs[0].name,g.vexs[i].name,d[i]);
 }
