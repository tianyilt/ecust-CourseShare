 // bo7-3.cpp 算法7.4～7.6
 Boolean visite[MAX_VERTEX_NUM]; // 访问标志数组(全局量)
 void(*VisitFunc)(VertexType); // 函数变量
 void DFS(Graph G,int v)
 { // 从第v个顶点出发递归地深度优先遍历图G。算法7.5
   int w;
   visite[v]=TRUE; // 设置访问标志为TRUE(已访问)
   VisitFunc(GetVex(G,v)); // 访问第v个顶点
   for(w=FirstAdjVex(G,v);w>=0;w=NextAdjVex(G,v,w)) // 从顶点v的第1个邻接顶点w开始
     if(!visite[w]) // 邻接顶点w尚未被访问
       DFS(G,w); // 对v的尚未访问的序号为w的邻接顶点递归调用DFS(访问w)
 }

 void DFSTraverse(Graph G,void(*Visit)(VertexType))
 { // 初始条件：图G存在，Visit是顶点的应用函数。算法7.4
   // 操作结果：从第1个顶点起，深度优先遍历图G，并对每个顶点调用函数Visit一次且仅一次
   int v;
   VisitFunc=Visit; // 使用全局变量VisitFunc，使DFS不必设函数指针参数
   for(v=0;v<G.vexnum;v++) // 对图G的所有顶点
     visite[v]=FALSE; // 访问标志数组初始化(未被访问)
   for(v=0;v<G.vexnum;v++) // 对图G的所有顶点
     if(!visite[v]) // 顶点v尚未被访问
       DFS(G,v); // 对尚未访问的序号为v的顶点调用DFS
   printf("\n");
 }

 typedef int QElemType; // 定义队列元素类型为整型(存储顶点序号)
 #include"c3-2.h" // 链队列的结构，BFSTraverse()用
 #include"bo3-2.cpp" // 链队列的基本操作，BFSTraverse()用
 void BFSTraverse(Graph G,void(*Visit)(VertexType))
 { // 初始条件：图G存在，Visit是顶点的应用函数。算法7.6
   // 操作结果：从第1个顶点起，按广度优先非递归遍历图G，
   //           并对每个顶点调用函数Visit一次且仅一次
   int v,u,w;
   LinkQueue Q; // 使用辅助队列Q和访问标志数组visite
   for(v=0;v<G.vexnum;v++) // 对图G的所有顶点
     visite[v]=FALSE; // 访问标志数组初始化(未被访问)
   InitQueue(Q); // 初始化辅助队列Q
   for(v=0;v<G.vexnum;v++) // 对图G的所有顶点
     if(!visite[v]) // 顶点v尚未被访问
     { visite[v]=TRUE; // 设置访问标志为TRUE(已访问)
       Visit(GetVex(G,v)); // 访问顶点v，在func7-1.cpp中
       EnQueue(Q,v); // v入队列Q
       while(!QueueEmpty(Q)) // 队列Q不空
       { DeQueue(Q,u); // 队头元素出队并置为u
         for(w=FirstAdjVex(G,u);w>=0;w=NextAdjVex(G,u,w)) // 从u的第1个邻接顶点w起
           if(!visite[w]) // w为u的尚未访问的邻接顶点
           { visite[w]=TRUE; // 设置访问标志为TRUE(已访问)
             Visit(GetVex(G,w)); // 访问顶点w
             EnQueue(Q,w); // w入队列Q
           }
       }
     }
   printf("\n");
 }
