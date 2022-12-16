 // bo7-2.cpp 图的邻接表存储(存储结构由c7-21.h定义)的基本操作(14个)
 #include"bo2-3.cpp" // 不带头结点的单链表基本操作
 #include"func2-4.cpp" // 不带头结点的单链表扩展操作
 int LocateVex(ALGraph G,VertexType u)
 { // 初始条件：图G存在，u和G中顶点有相同特征(顶点名称相同)
   // 操作结果：若G中存在顶点u，则返回该顶点在图中位置(序号)；否则返回-1
   int i;
   for(i=0;i<G.vexnum;++i) // 对于所有顶点依次查找
     if(strcmp(u.name,G.vertices[i].data.name)==0) // 顶点与给定的u的顶点名称相同
       return i; // 返回顶点序号
   return -1; // 图G中不存在与顶点u有相同名称的顶点
 }

 void CreateGraph(ALGraph &G)
 { // 采用邻接表存储结构，构造图或网G(用一个函数构造4种图)
   int i,j,k;
   VertexType v1,v2; // 顶点类型
   ElemType e; // 表结点的元素类型(存储弧的信息)
   char s[3]="边";
   printf("请输入图的类型(有向图：0 有向网：1 无向图：2 无向网：3)：");
   scanf("%d",&G.kind);
   if(G.kind<2) // 有向
     strcpy(s,"弧");
   printf("请输入图的顶点数,边数：");
   scanf("%d,%d",&G.vexnum,&G.arcnum);
   printf("请输入%d个顶点的值(名称<%d个字符)：\n",G.vexnum,MAX_NAME);
   for(i=0;i<G.vexnum;++i) // 构造顶点向量
   { Input(G.vertices[i].data); // 输入顶点信息
     G.vertices[i].firstarc=NULL; // 初始化与该顶点有关的出弧链表
   }
   printf("请输入%d条%s的",G.arcnum,s);
   switch(G.kind)
   { case  DG:printf("弧尾 弧头：\n"); // 设图没有弧(边)信息
              break;
     case  DN:printf("弧尾 弧头 弧的信息：\n");
              break;
     case UDG:printf("顶点1 顶点2：\n"); // 设图没有弧(边)信息
              break;
     case UDN:printf("顶点1 顶点2 边的信息：\n");
   }
   for(k=0;k<G.arcnum;++k) // 构造相关弧链表
   { scanf("%s%s",v1.name,v2.name); // 输入2顶点名称
     i=LocateVex(G,v1); // 弧尾
     j=LocateVex(G,v2); // 弧头
     e.info=NULL; // 给待插表结点e赋值，设图无弧(边)信息
     if(G.kind%2) // 网
       InputArc(e.info); // 动态生成存储空间，输入弧的相关信息，在func7-4.cpp中
     e.adjvex=j; // 弧头
     ListInsert(G.vertices[i].firstarc,1,e);
     // 将e插在第i个元素(出弧)的表头，在bo2-3.cpp中
     if(G.kind>=2) // 无向图或网，产生第2个表结点，并插在第j个元素(入弧)的表头
     { e.adjvex=i; // e.info不变，不必再赋值
       ListInsert(G.vertices[j].firstarc,1,e); // 插在第j个元素的表头，在bo2-3.cpp中
     }
   }
 }

 void CreateFromFile(ALGraph &G,char* filename)
 { // 采用邻接表存储结构，由文件构造图或网G(用一个函数构造4种图)
   int i,j,k;
   VertexType v1,v2; // 顶点类型
   ElemType e; // 表结点的元素类型(存储弧的信息)
   FILE *f; // 文件指针类型
   f=fopen(filename,"r"); // 以读的方式打开数据文件，并以f表示
   fscanf(f,"%d",&G.kind); // 由文件输入G的类型
   fscanf(f,"%d",&G.vexnum); // 由文件输入G的顶点数
   for(i=0;i<G.vexnum;++i) // 构造顶点向量
   { InputFromFile(f,G.vertices[i].data); // 由文件输入顶点信息
     G.vertices[i].firstarc=NULL; // 初始化与该顶点有关的出弧链表
   }
   fscanf(f,"%d",&G.arcnum); // 由文件输入G的弧(边)数
   for(k=0;k<G.arcnum;++k) // 构造相关弧链表
   { fscanf(f,"%s%s",v1.name,v2.name); // 由文件输入2顶点名称
     i=LocateVex(G,v1); // 弧尾
     j=LocateVex(G,v2); // 弧头
     e.info=NULL; // 给待插表结点e赋值，设图无弧(边)信息
     if(G.kind%2) // 网
       InputArcFromFile(f,e.info);
       // 动态生成存储空间，由文件输入弧的相关信息，在func7-4.cpp中
     e.adjvex=j; // 弧头
     ListInsert(G.vertices[i].firstarc,1,e);
     // 将e插在第i个元素(出弧)的表头，在bo2-3.cpp中
     if(G.kind>=2) // 无向图或网，产生第2个表结点，并插在第j个元素(入弧)的表头
     { e.adjvex=i; // e.info不变，不必再赋值
       ListInsert(G.vertices[j].firstarc,1,e); // 插在第j个元素的表头，在bo2-3.cpp中
     }
   }
   fclose(f); // 关闭数据文件
 }

 VertexType GetVex(ALGraph G,int v)
 { // 初始条件：图G存在，v是G中某个顶点的序号。操作结果：返回v的值
   if(v>=G.vexnum||v<0) // 图G中不存在序号为v的顶点
     exit(OVERFLOW);
   return G.vertices[v].data; // 返回该顶点的信息
 }

 Status PutVex(ALGraph &G,VertexType v,VertexType value)
 { // 初始条件：图G存在，v是G中某个顶点。操作结果：对v赋新值value
   int k=LocateVex(G,v); // k为顶点v在图G中的序号
   if(k!=-1) // v是G的顶点
   { G.vertices[k].data=value; // 将新值赋给顶点v(其序号为k)
     return OK;
   }
   return ERROR; // v不是G的顶点
 }

 int FirstAdjVex(ALGraph G,int v)
 { // 初始条件：图G存在，v是G中某个顶点的序号
   // 操作结果：返回v的第1个邻接顶点的序号。若顶点在G中没有邻接顶点，则返回-1
   ArcNode *p=G.vertices[v].firstarc; // p指向顶点v的第1个邻接顶点
   if(p) // 顶点v有邻接顶点
     return p->data.adjvex; // 返回v的第1个邻接顶点的序号
   else
     return -1; // 顶点v没有邻接顶点
 }

 Status equalvex(ElemType a,ElemType b)
 { // DeleteArc()、DeleteVex()和NextAdjVex()要调用的函数
   if(a.adjvex==b.adjvex) // 表结点的顶位置(序号)相同
     return OK;
   else
     return ERROR;
 }

 int NextAdjVex(ALGraph G,int v,int w)
 { // 初始条件：图G存在，v是G中某个顶点的序号，w是v的邻接顶点的序号
   // 操作结果：返回v的(相对于w的)下一个邻接顶点的序号。
   //           若w是v的最后一个邻接顶点，则返回-1
   LinkList p,p1; // p1在Point()中用作辅助指针，Point()在func2-4.cpp中
   ElemType e; // 表结点的元素类型(存储弧的信息)
   e.adjvex=w;
   p=Point(G.vertices[v].firstarc,e,equalvex,p1);
   // p指向顶点v的链表中邻接顶点为w的结点
   if(!p||!p->next) // 未找到w或w是最后一个邻接点
     return -1;
   else // p->data.adjvex==w
     return p->next->data.adjvex; // 返回v的(相对于w的)下一个邻接顶点的序号
 }

 void InsertVex(ALGraph &G,VertexType v)
 { // 初始条件：图G存在，v和图中顶点有相同特征
   // 操作结果：在图G中增添新顶点v(不增添与顶点相关的弧，留待InsertArc()去做)
   G.vertices[G.vexnum].data=v; // 构造新顶点向量
   G.vertices[G.vexnum].firstarc=NULL; // 没有与顶点相关的弧
   G.vexnum++; // 图G的顶点数加1
 }

 Status InsertArc(ALGraph &G,VertexType v,VertexType w)
 { // 初始条件：图G存在，v和w是G中两个顶点
   // 操作结果：在G中增添弧<v,w>，若G是无向的，则还增添对称弧<w,v>
   ElemType e; // 表结点的元素类型(存储弧的信息)
   int i,j;
   char s1[3]="边",s2[3]="—"; // 无向的情况
   if(G.kind<2) // 有向
   { strcpy(s1,"弧");
     strcpy(s2,"→");
   }
   i=LocateVex(G,v); // 弧尾或边的序号
   j=LocateVex(G,w); // 弧头或边的序号
   if(i<0||j<0) // v和w至少有1个不是G中的顶点
     return ERROR;
   G.arcnum++; // 图G的弧或边的数目加1
   e.adjvex=j; // 弧头表结点的值
   e.info=NULL; // 初值，设图无弧(边)信息
   if(G.kind%2) // 网
   { printf("请输入%s%s%s%s的信息：",s1,v.name,s2,w.name);
     InputArc(e.info); // 动态生成存储空间，输入弧的相关信息，在func7-4.cpp中
   }
   ListInsert(G.vertices[i].firstarc,1,e); // 将e插在弧尾的表头，在bo2-3.cpp中
   if(G.kind>=2) // 无向，生成另一个表结点
   { e.adjvex=i; // 弧尾表结点的值，e.info不变
     ListInsert(G.vertices[j].firstarc,1,e); // 将e插在弧头的表头
   }
   return OK;
 }

 Status DeleteArc(ALGraph &G,VertexType v,VertexType w)
 { // 初始条件：图G存在，v和w是G中两个顶点
   // 操作结果：在G中删除弧<v,w>，若G是无向的，则还删除对称弧<w,v>
   int i,j,n;
   ElemType e; // 表结点的元素类型(存储弧的信息)
   i=LocateVex(G,v); // i是顶点v(弧尾)的序号
   j=LocateVex(G,w); // j是顶点w(弧头)的序号
   if(i<0||j<0||i==j) // v和w至少有1个不是G中的顶点，或v和w是G中的同一个顶点
     return ERROR;
   e.adjvex=j; // 弧头表结点的值
   n=LocateElem(G.vertices[i].firstarc,e,equalvex);
   // 在弧尾链表中找弧头表结点，将其在链表中的位序赋给n
   if(n) // 存在该弧
   { ListDelete(G.vertices[i].firstarc,n,e); // 在弧尾链表中删除弧头表结点，并用e返回其值
     G.arcnum--; // 弧或边数减1
     if(G.kind%2) // 网，设图无弧(边)信息
       free(e.info); // 释放动态生成的弧(边)信息空间
     if(G.kind>=2) // 无向，删除对称弧<w,v>
     { e.adjvex=i; // 弧尾表结点的值
       n=LocateElem(G.vertices[j].firstarc,e,equalvex);
       // 在弧头链表中找弧尾表结点，将其在链表中的位序赋给n
       ListDelete(G.vertices[j].firstarc,n,e);
       // 在弧头链表中删除弧尾表结点，并用e返回其值
     }
     return OK;
   }
   else // 未找到待删除的弧
     return ERROR;
 }

 Status DeleteVex(ALGraph &G,VertexType v)
 { // 初始条件：图G存在，v是G中某个顶点。操作结果：删除G中顶点v及其相关的弧(边)
   int i,k;
   LinkList p; // 表结点的指针类型
   k=LocateVex(G,v); // k为待删除顶点v的序号
   if(k<0) // v不是图G的顶点
     return ERROR;
   for(i=0;i<G.vexnum;i++)
     DeleteArc(G,v,G.vertices[i].data); // 删除由顶点v发出的所有弧
   if(G.kind<2) // 有向
     for(i=0;i<G.vexnum;i++)
       DeleteArc(G,G.vertices[i].data,v); // 删除发向顶点v的所有弧
   for(i=0;i<G.vexnum;i++) // 对于adjvex域>k的结点，其序号-1
   { p=G.vertices[i].firstarc; // p指向弧结点的单链表
     while(p) // 未到表尾
     { if(p->data.adjvex>k) // adjvex域>k
         p->data.adjvex--; // 序号-1(因为前移)
       p=p->next; // p指向下一个结点
     }
   }
   for(i=k+1;i<G.vexnum;i++)
     G.vertices[i-1]=G.vertices[i]; // 顶点v后面的顶点依次前移
   G.vexnum--; // 顶点数减1
   return OK;
 }

 void DestroyGraph(ALGraph &G)
 { // 初始条件：图G存在。操作结果：销毁图G
   int i;
   for(i=G.vexnum-1;i>=0;i--) // 由大到小逐一删除顶点及与其相关的弧(边)
     DeleteVex(G,G.vertices[i].data);
 }
 
 void Display(ALGraph G)
 { // 输出图的邻接矩阵G
   int i;
   ArcNode *p;
   char s1[3]="边",s2[3]="—"; // 无向的情况
   if(G.kind<2) // 有向
   { strcpy(s1,"弧");
     strcpy(s2,"→");
   }
   switch(G.kind)
   { case  DG:printf("有向图\n");
              break;
     case  DN:printf("有向网\n");
              break;
     case UDG:printf("无向图\n");
              break;
     case UDN:printf("无向网\n");
   }
   printf("%d个顶点，依次是：",G.vexnum);
   for(i=0;i<G.vexnum;++i)
     Visit(GetVex(G,i)); // 根据顶点信息的类型，访问第i个顶点，在func7-1.cpp中
   printf("\n%d条%s：\n",G.arcnum,s1);
   for(i=0;i<G.vexnum;i++)
   { p=G.vertices[i].firstarc; // p指向序号为i的顶点的第1条弧(边)
     while(p) // p不为空
     { if(G.kind<=1||i<p->data.adjvex) // 有向或无向两次中的一次
       { printf(" %s%s%s",G.vertices[i].data.name,s2,
         G.vertices[p->data.adjvex].data.name);
         if(G.kind%2) // 网
           OutputArc(p->data.info); // 输出弧(边)信息(包括权值)，在func7-4.cpp中
       }
       p=p->nextarc; // p指向下一个表结点
     }
     printf("\n");
   }
 }
