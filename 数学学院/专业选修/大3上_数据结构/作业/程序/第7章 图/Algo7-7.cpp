 // algo7-7.cpp 输出有向图的一个拓扑序列。实现算法7.12的程序
 #include"c1.h"
 #include"func7-1.cpp" // 包括顶点信息类型的定义及对它的操作
 #include"func7-4.cpp" // 弧(边)的相关信息类型的定义及对它的操作
 #include"c7-2'.h" // 图的邻接表存储结构(与单链表的变量类型建立联系)
 #include"bo7-2.cpp" // 图的邻接表存储结构的基本操作
 #include"func7-5.cpp" // 求顶点入度的函数

 typedef int SElemType; // 定义栈元素类型为整型(存储顶点序号)
 #include"c3-1.h" // 顺序栈的存储结构
 #include"bo3-1.cpp" // 顺序栈的基本操作
 Status TopologicalSort(ALGraph G)
 { // 有向图G采用邻接表存储结构。若G无回路，则输出G的顶点的一个拓扑序列并返回OK；
   // 否则返回ERROR。算法7.12
   int i,k,count=0; // 已输出顶点数，初值为0
   int indegree[MAX_VERTEX_NUM]; // 入度数组，存放各顶点当前入度数
   SqStack S;
   ArcNode *p;
   FindInDegree(G,indegree); // 对G的各顶点求入度indegree[]，在func7-5.cpp中
   InitStack(S); // 初始化零入度顶点栈S
   for(i=0;i<G.vexnum;++i) // 对所有顶点i
     if(!indegree[i]) // 若其入度为0
       Push(S,i); // 将i入零入度顶点栈S
   while(!StackEmpty(S)) // 当零入度顶点栈S不空
   { Pop(S,i); // 出栈1个零入度顶点的序号，并将其赋给i
     printf("%s ",G.vertices[i].data.name); // 输出i号顶点
     ++count; // 已输出顶点数+1
     for(p=G.vertices[i].firstarc;p;p=p->nextarc) // 对i号顶点的每个邻接顶点
     { k=p->data.adjvex; // 其序号为k
       if(!(--indegree[k])) // k的入度减1，若减为0，则将k入栈S
         Push(S,k);
     }
   }
   if(count<G.vexnum) // 零入度顶点栈S已空，图G还有顶点未输出
   { printf("此有向图有回路\n");
     return ERROR;
   }
   else
   { printf("为一个拓扑序列。\n");
     return OK;
   }
 }

 void main()
 {
   ALGraph f;
   printf("请选择有向图\n");
   CreateGraph(f); // 构造有向图f，在bo7-2.cpp中
   Display(f); // 输出有向图f，在bo7-2.cpp中
   TopologicalSort(f); // 输出有向图f的1个拓扑序列
 }
