 // algo7-10.cpp 实现算法7.16的程序
 #include"c1.h"
 #include"func7-1.cpp" // 包括顶点信息类型的定义及对它的操作
 #include"func7-2.cpp" // 包括弧(边)的相关信息类型的定义及对它的操作
 #include"c7-1.h" // 图的数组(邻接矩阵)存储结构
 #include"bo7-1.cpp" // 图的数组(邻接矩阵)存储结构的基本操作
 typedef char PathMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM][MAX_VERTEX_NUM];
 // 三维数组，其值只可能是0或1，故用char类型以减少存储空间的浪费
 typedef VRType DistancMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; // 二维数组
 #include"func7-8.cpp" // 求有向网中各对顶点之间最短距离的Floyd算法

 void main()
 {
   MGraph g;
   int i,j,k;
   PathMatrix p; // 三维数组
   DistancMatrix d; // 二维数组
   CreateDN(g); // 构造有向网g
   for(i=0;i<g.vexnum;i++)
     g.arcs[i][i].adj=0;
     // ShortestPath_FLOYD()要求对角元素值为0，因为两点相同，其距离为0
   Display(g); // 输出有向网g
   ShortestPath_FLOYD(g,p,d); // 求每对顶点间的最短路径。在func7-8.cpp中
   printf("d矩阵：\n");
   for(i=0;i<g.vexnum;i++)
   { for(j=0;j<g.vexnum;j++)
       printf("%6d",d[i][j]);
     printf("\n");
   }
   printf("p矩阵：\n");
   for(i=0;i<g.vexnum;i++)
     for(j=0;j<g.vexnum;j++)
       if(i!=j)
       { printf("由%s到%s经过：",g.vexs[i].name,g.vexs[j].name);
         for(k=0;k<g.vexnum;k++)
           if(p[i][j][k]==1)
             printf("%s ",g.vexs[k].name);
         printf("\n");
       }
 }
