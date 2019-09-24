 // algo7-6.cpp 实现算法7.10、7.11的程序
 #include"c1.h"
 #include"func7-1.cpp" // 包括顶点信息类型的定义及对它的操作
 #include"func7-4.cpp" // 弧(边)的相关信息类型的定义及对它的操作
 #include"c7-2'.h" // 图的邻接表存储结构(与单链表的变量类型建立联系)
 #include"bo7-2.cpp" // 图的邻接表存储结构的基本操作

 int count,lowcount=1; // 全局量count对访问顺序计数,lowcount对求得low值的顺序计数
 int low[MAX_VERTEX_NUM],lowOrder[MAX_VERTEX_NUM];
 // 全局数组，low[]存顶点的low值，lowOrder存顶点求得low值的顺序
 int visited[MAX_VERTEX_NUM]; // 访问标志数组(全局量)

 void DFSArticul(ALGraph G,int v0)
 { // 从第v0个顶点出发深度优先遍历图G，查找并输出关节点。算法7.11
   int min,w;
   ArcNode *p;
   visited[v0]=min=++count; // v0是第count个访问的顶点，min的初值为v0的访问顺序
   for(p=G.vertices[v0].firstarc;p;p=p->nextarc) // 依次对v0的每个邻接顶点检查
   { w=p->data.adjvex; // w为v0的邻接顶点位置
     if(visited[w]==0) // w未曾访问，是v0的孩子
     { DFSArticul(G,w);
       // 从第w个顶点出发深度优先遍历图G，查找并输出关节点。返回前求得low[w]
       if(low[w]<min) // 如果v0的孩子结点w的low[]小，这说明孩子结点还与其他结点(祖先)相邻
         min=low[w]; // 取min值为孩子结点的low[]，则v0不是关节点
       else if(low[w]>=visited[v0]) // v0的孩子结点w只与v0相连，则v0是关节点
         printf("%d %s\n",v0,G.vertices[v0].data.name); // 输出关节点v0
     }
     else if(visited[w]<min) // w已访问，则w是v0在生成树上的祖先，它的访问顺序必小于min
       min=visited[w]; // 故取min为visited[w]
   }
   low[v0]=min; // v0的low[]值为三者中的最小值
   lowOrder[v0]=lowcount++;
   // 记录v0求得low[]值的顺序，总是在返回主调函数之前求得low[]。新增
 }

 void FindArticul(ALGraph G)
 { // 连通图G以邻接表作存储结构，查找并输出G上全部关节点。全局量count对访问计数。算法7.10
   int i,v;
   ArcNode *p;
   count=1; // 访问顺序
   visited[0]=count; // 设定邻接表上0号顶点为生成树的根，第1个被访问
   for(i=1;i<G.vexnum;++i) // 对于其余顶点
     visited[i]=0; // 其余顶点尚未访问，设初值为0
   p=G.vertices[0].firstarc; // p指向根结点的第1个邻接顶点
   v=p->data.adjvex; // v是根结点的第1个邻接顶点的序号
   DFSArticul(G,v); // 从第v顶点出发深度优先查找关节点
   if(count<G.vexnum) // 由根结点的第1个邻接顶点深度优先遍历G，访问的顶点数少于G的顶点数
   { // 说明生成树的根有至少两棵子树，则根是关节点
     printf("%d %s\n",0,G.vertices[0].data.name); // 根是关节点，输出根
     while(p->nextarc) // 根有下一个邻接点
     { p=p->nextarc; // p指向根的下一个邻接点
       v=p->data.adjvex;
       if(visited[v]==0) // 此邻接点未被访问
         DFSArticul(G,v); // 从此顶点出发深度优先查找关节点
     }
   }
 }

 void main()
 {
   int i;
   ALGraph g;
   char filename[13]; // 存储数据文件名(包括路径)
   printf("请输入数据文件名：");
   scanf("%s",filename);
   CreateFromFile(g,filename); // 由文件构造无向图g
   Display(g); // 输出无向图g
   printf("输出关节点：\n");
   FindArticul(g); // 求连通图g的关节点
   printf(" i G.vertices[i].data visited[i] low[i] lowOrder[i]\n"); // 输出辅助变量
   for(i=0;i<g.vexnum;++i)
     printf("%2d %9s %14d %8d %8d\n",i,g.vertices[i].data.name,
     visited[i],low[i],lowOrder[i]);
 }
