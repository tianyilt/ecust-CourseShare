 // algo7-8.cpp 求关键路径。实现算法7.13、7.14的程序
 #include"c1.h"
 #include"func7-6.cpp" // 包括顶点信息类型的定义及对它的操作
 #include"func7-7.cpp" // 弧的相关信息类型的定义及对它的操作
 #include"c7-2'.h" // 图的邻接表存储结构(与单链表的变量类型建立联系)
 #include"bo7-2.cpp" // 图的邻接表存储结构的基本操作
 #include"func7-5.cpp" // 求顶点入度的函数
 typedef int SElemType; // 定义栈元素类型为整型(存储顶点序号)
 #include"c3-1.h" // 顺序栈的存储结构
 #include"bo3-1.cpp" // 顺序栈的基本操作
 Status TopologicalOrder(ALGraph &G,SqStack &T)
 { // 有向网G采用邻接表存储结构，求各顶点事件的最早发生时间ve(存储在G中)。修改算法7.13
   // T为拓扑序列顶点栈，S为零入度顶点栈。若G无回路，则用栈T返回G的一个拓扑序列，
   // 且函数值为OK；否则为ERROR
   int i,k,count=0; // 已入栈顶点数，初值为0
   int indegree[MAX_VERTEX_NUM]; // 入度数组，存放各顶点当前入度数
   SqStack S;
   ArcNode *p;
   FindInDegree(G,indegree); // 对各顶点求入度indegree[]，在func7-5.cpp中
   InitStack(S); // 初始化零入度顶点栈S
   printf("拓扑序列：");
   for(i=0;i<G.vexnum;++i) // 对所有顶点i
     if(!indegree[i]) // 若其入度为0
       Push(S,i); // 将i入零入度顶点栈S
   InitStack(T); // 初始化拓扑序列顶点栈
   for(i=0;i<G.vexnum;++i) // 初始化ve=0(最小值，先假定每个事件都不受其他事件约束)
     G.vertices[i].data.ve=0;
   while(!StackEmpty(S)) // 当零入度顶点栈S不空
   { Pop(S,i); // 从栈S将已拓扑排序的顶点弹出，并赋给i
     Visit(G.vertices[i].data); // 输出该顶点的名称
     Push(T,i); // j号顶点入逆拓扑排序栈T(栈底元素为拓扑排序的第1个元素)
     ++count; // 对入栈T的顶点计数
     for(p=G.vertices[i].firstarc;p;p=p->nextarc)
     { // 对i号顶点的每个邻接顶点
       k=p->data.adjvex; // 其序号为k
       if(--indegree[k]==0) // k的入度减1，若减为0，则将k入栈S
         Push(S,k);
       if(G.vertices[i].data.ve+p->data.info->weight>G.vertices[k].data.ve)
       // 顶点i事件的最早发生时间+<i,k>的权值>顶点k事件的最早发生时间
         G.vertices[k].data.ve=G.vertices[i].data.ve+p->data.info->weight;
         // 顶点k事件的最早发生时间=顶点i事件的最早发生时间+<i,k>的权值
     }   // 由于i已拓扑有序，故G.vertices[i].data.ve不再改变
   }
   if(count<G.vexnum)
   { printf("此有向网有回路\n");
     return ERROR;
   }
   else
     return OK;
 }

 Status CriticalPath(ALGraph &G)
 { // G为有向网，输出G的各项关键活动。修改算法7.14
   SqStack T;
   int i,j,k;
   ArcNode *p;
   if(!TopologicalOrder(G,T)) // 产生有向环
     return ERROR;
   j=G.vertices[0].data.ve; // j的初值
   for(i=1;i<G.vexnum;i++) // 在所有顶点中，找ve的最大值
     if(G.vertices[i].data.ve>j)
       j=G.vertices[i].data.ve; // j=Max(ve) 完成点的最早发生时间
   for(i=0;i<G.vexnum;i++) // 初始化顶点事件的最迟发生时间
     G.vertices[i].data.vl=j; // 为完成点的最早发生时间(最大值)
   while(!StackEmpty(T)) // 按拓扑逆序求各顶点的vl值
     for(Pop(T,j),p=G.vertices[j].firstarc;p;p=p->nextarc)
     { // 弹出栈T的元素，赋给j，p指向顶点j的后继事件(出弧)顶点k，
       // 事件k的最迟发生时间已确定(因为是逆拓扑排序)
       k=p->data.adjvex; // 后继事件顶点的序号
       if(G.vertices[k].data.vl-p->data.info->weight<G.vertices[j].data.vl)
       // 事件j的最迟发生时间>其直接后继事件k的最迟发生时间-<j,k>的权值
         G.vertices[j].data.vl=G.vertices[k].data.vl-p->data.info->weight;
         // 事件j的最迟发生时间=事件k的最迟发生时间-<j,k>的权值
     }   // 由于k已逆拓扑有序，故G.vertices[k].data.vl不再改变
   printf("\ni  ve  vl\n");
   for(i=0;i<G.vexnum;i++) // 对于每个顶点
   { printf("%d ",i); // 输出序号
     Visitel(G.vertices[i].data); // 输出ve、vl值，在func7-6.cpp中
     if(G.vertices[i].data.ve==G.vertices[i].data.vl)
     // 事件(顶点)的最早发生时间=最迟发生时间
       printf(" 关键路径经过的顶点");
     printf("\n");
   }
   printf("j   k  权值  ee  el\n"); // 以下求ee，el和关键活动
   for(j=0;j<G.vexnum;++j) // 对于每个顶点j
     for(p=G.vertices[j].firstarc;p;p=p->nextarc)
     { // p依次指向其邻接顶点(直接后继事件)
       k=p->data.adjvex; // 邻接顶点(直接后继事件)序号
       p->data.info->ee=G.vertices[j].data.ve;
       // ee(活动<j,k>的最早开始时间)=(顶点j)事件最早发生时间
       p->data.info->el=G.vertices[k].data.vl-p->data.info->weight;
       // el(活动<j,k>的最迟开始时间)=(顶点k)事件最迟发生时间-<j,k>的权值
       printf("%s→%s",G.vertices[j].data.name,G.vertices[k].data.name); // 输出弧
       OutputArcwel(p->data.info); // 输出弧的权值、ee和el，在func7-7.cpp中
       if(p->data.info->ee==p->data.info->el)
       // 活动(弧)的最早开始时间=活动的最迟开始时间
         printf("关键活动");
       printf("\n");
     }
   return OK;
 }

 void main()
 {
   ALGraph h;
   printf("请选择有向网\n");
   CreateGraph(h); // 构造有向网h，在bo7-2.cpp中
   Display(h); // 输出有向网h，在bo7-2.cpp中
   CriticalPath(h); // 求h的关键路径
 }
