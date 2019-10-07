 // func7-5.cpp algo7-7.cpp和algo7-8.cpp要调用
 void FindInDegree(ALGraph G,int indegree[])
 { // 求顶点的入度，算法7.12、7.13调用
   int i;
   ArcNode *p;
   for(i=0;i<G.vexnum;i++) // 对于所有顶点
     indegree[i]=0; // 给顶点的入度赋初值0
   for(i=0;i<G.vexnum;i++) // 对于所有顶点
   { p=G.vertices[i].firstarc; // p指向顶点的邻接表的头指针
     while(p) // p不空
     { indegree[p->data.adjvex]++; // 将p所指邻接顶点的入度+1
       p=p->nextarc; // p指向下一个邻接顶点
     }
   }
 }
