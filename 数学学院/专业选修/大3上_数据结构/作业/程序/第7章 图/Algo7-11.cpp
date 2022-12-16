 // algo7-11.cpp 实现教科书图7.33的程序(新增孤立顶点台北)
 #include"c1.h"
 #include"func7-1.cpp" // 包括顶点信息类型的定义及对它的操作
 #include"func7-2.cpp" // 包括弧(边)的相关信息类型的定义及对它的操作
 #include"c7-1.h" // 图的数组(邻接矩阵)存储结构
 #include"bo7-1.cpp" // 图的数组(邻接矩阵)存储结构的基本操作
 typedef char PathMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM][MAX_VERTEX_NUM];
 // 三维数组，其值只可能是0或1，故用char类型以减少存储空间的浪费
 typedef VRType DistancMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; // 二维数组
#include"func7-8.cpp" // 求有向网中各对顶点之间最短距离的Floyd算法

 void path(MGraph G,PathMatrix P,int i,int j)
 { // 求由序号为i的起点城市到序号为j的终点城市最短路径沿途所经过的城市
   int k,m=i; // 起点城市序号赋给m
   printf("依次经过的城市：\n");
   while(m!=j) // 未到终点城市
   { G.arcs[m][m].adj=INFINITY; // 对角元素赋值无穷大
     for(k=0;k<G.vexnum;k++)
       if(G.arcs[m][k].adj<INFINITY&&P[m][j][k])
       { // m到k有直接通路，且k在m到j的最短路径上
         printf("%s ",G.vexs[m].name);
         G.arcs[m][k].adj=G.arcs[k][m].adj=INFINITY; // 将直接通路设为不通
         m=k; // 经过的城市序号赋给m，继续查找
         break;
       }
   }
   printf("%s\n",G.vexs[j].name); // 输出终点城市
 }

 void main()
 {
   MGraph g;
   int i,j,k,q=1;
   PathMatrix p; // 三维数组
   DistancMatrix d; // 二维数组
   char filename[8]="map.txt"; // 数据文件名
   CreateFromFile(g,filename,0); // 通过文件map.txt构造没有相关信息的无向网g
   for(i=0;i<g.vexnum;i++)
     g.arcs[i][i].adj=0;
     // ShortestPath_FLOYD()要求对角元素值为0，因为两点相同，其距离为0
   ShortestPath_FLOYD(g,p,d); // 求每对顶点间的最短路径，在func7-8.cpp中
   while(q)
   { printf("请选择：1 查询  0 结束\n");
     scanf("%d",&q);
     if(q)
     { printf("城市代码：\n");
       for(i=0;i<g.vexnum;i++)
       { printf("%2d.%-8s",i+1,g.vexs[i].name);
         if(i%7==6) // 输出7个数据就换行
           printf("\n");
       }
       printf("\n请输入要查询的起点城市代码 终点城市代码：");
       scanf("%d%d",&i,&j);
       if(d[i-1][j-1]<INFINITY) // 有通路
       { printf("%s到%s的最短距离为%d\n",g.vexs[i-1].name,g.vexs[j-1].name,
         d[i-1][j-1]);
         path(g,p,i-1,j-1); // 求最短路径上由起点城市到终点城市沿途所经过的城市
       }
       else
         printf("%s到%s没有路径可通\n",g.vexs[i-1].name,g.vexs[j-1].name);
       printf("与%s到%s有关的p矩阵：\n",g.vexs[i-1].name,g.vexs[j-1].name);
       for(k=0;k<g.vexnum;k++)
         printf("%2d",p[i-1][j-1][k]);
       printf("\n");
     }
   }
 }
