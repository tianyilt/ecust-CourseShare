 // algo7-2.cpp 邻接表存储结构的深度优先和广度优先搜索遍历
 #include"c1.h"
 #include"func7-1.cpp" // 包括顶点信息类型的定义及对它的操作
 #include"func7-4.cpp" // 弧(边)的相关信息类型的定义及对它的操作
 #include"c7-2'.h" // 图的邻接表存储结构(与单链表的变量类型建立联系)
 #include"bo7-2.cpp" // 图的邻接表存储结构的基本操作
 Boolean visited[MAX_VERTEX_NUM]; // 访问标志数组(全局量)
 void DFS(ALGraph G,int v,void(*Visit)(VertexType))
 { // 从第v个顶点出发递归地深度优先遍历图G。修改算法7.5，仅适用于邻接表存储结构
   ArcNode *p; // p指向表结点
   visited[v]=TRUE; // 设置访问标志为TRUE(已访问)
   Visit(G.vertices[v].data); // 访问第v个顶点
   for(p=G.vertices[v].firstarc;p;p=p->next) // p依次指向v的邻接顶点
     if(!visited[p->data.adjvex]) // 如果该邻接顶点尚未被访问
       DFS(G,p->data.adjvex,Visit); // 对v的尚未访问的邻接点递归调用DFS
 }

 void DFSTraverse(ALGraph G,void(*Visit)(VertexType))
 { // 对图G作深度优先遍历。DFS设函数指针参数，修改算法7.4，仅适用于邻接表存储结构
   int v;
   for(v=0;v<G.vexnum;v++) // 对于所有顶点
     visited[v]=FALSE; // 访问标志数组初始化，置初值为未被访问
   for(v=0;v<G.vexnum;v++) // 如果是连通图，只v=0就遍历全图
     if(!visited[v]) // v尚未被访问
       DFS(G,v,Visit); // 对v调用DFS
   printf("\n");
 }

 typedef int QElemType; // 定义队列元素类型为整型(存储顶点序号)
 #include"c3-2.h" // 链队列的结构，BFSTraverse()用
 #include"bo3-2.cpp" // 链队列的基本操作，BFSTraverse()用
 void BFSTraverse(ALGraph G,void(*Visit)(VertexType)) // 修改算法7.6，仅适用于邻接表结构
 { // 按广度优先非递归遍历图G。使用辅助队列Q和访问标志数组visited
   int v,u;
   ArcNode *p; // 表结点指针类型
   LinkQueue Q; // 链队列类型
   for(v=0;v<G.vexnum;++v) // 对于所有顶点
     visited[v]=FALSE; // 置初值为未被访问
   InitQueue(Q); // 初始化辅助队列Q
   for(v=0;v<G.vexnum;v++) // 如果是连通图，只v=0就遍历全图
     if(!visited[v]) // v尚未被访问
     { visited[v]=TRUE; // 设v为已被访问
       Visit(G.vertices[v].data); // 访问v
       EnQueue(Q,v); // v入队列Q
       while(!QueueEmpty(Q)) // 队列Q不空
       { DeQueue(Q,u); // 队头元素出队并赋给u
         for(p=G.vertices[u].firstarc;p;p=p->next) // p依次指向u的邻接顶点
           if(!visited[p->data.adjvex]) // u的邻接顶点尚未被访问
           { visited[p->data.adjvex]=TRUE; // 设该邻接顶点为已被访问
             Visit(G.vertices[p->data.adjvex].data); // 访问该邻接顶点
             EnQueue(Q,p->data.adjvex); // 入队该邻接顶点序号
           }
       }
     }
   printf("\n");
 }

 void main()
 {
   ALGraph g;
   char filename[13]; // 存储数据文件名(包括路径)
   printf("请输入数据文件名：");
   scanf("%s",filename);
   CreateFromFile(g,filename); // 利用数据文件创建无相关信息的图
   printf("深度优先搜索遍历的结果：\n");
   DFSTraverse(g,Visit);
   printf("广度优先搜索遍历的结果：\n");
   BFSTraverse(g,Visit);
 }
