 // algo7-3.cpp 调用算法7.7和7.8
 #include"c1.h"
 #include"func7-1.cpp" // 包括顶点信息类型的定义及对它的操作
 #include"func7-4.cpp" // 弧(边)的相关信息类型的定义及对它的操作
 typedef VertexType TElemType; // 定义树的元素类型为图的顶点类型
 #include"c6-4.h" // 孩子-兄弟二叉链表存储结构
 #include"bo6-6.cpp" // 孩子-兄弟二叉链表存储结构的先根遍历操作
 #include"c7-2'.h" // 图的邻接表存储结构(与单链表的变量类型建立联系)
 Boolean visited[MAX_VERTEX_NUM]; // 访问标志数组(全局量)
 #include"bo7-2.cpp" // 图的邻接表的基本操作
 typedef ALGraph Graph; // 定义图的存储结构为邻接表

 void DFSTree(Graph G,int v,CSTree &T)
 { // 从第v个顶点出发深度优先遍历图G，建立以T为根的生成树。算法7.8
   Boolean first=TRUE; // 树T还没有第1个孩子结点的标志
   int w;
   CSTree p,q; // 孩子-兄弟二叉链表结点的指针类型
   visited[v]=TRUE; // 顶点v已被访问的标志
   for(w=FirstAdjVex(G,v);w>=0;w=NextAdjVex(G,v,w)) // w依次为v的邻接顶点
     if(!visited[w]) // 顶点w尚未被访问
     { p=(CSTree)malloc(sizeof(CSNode)); // 分配孩子结点给p
       p->data=GetVex(G,w); // 将顶点w的值赋给孩子结点的data域
       p->firstchild=NULL; // 孩子结点的firstchild域和nextsibling域赋空
       p->nextsibling=NULL;
       if(first) // 顶点w是顶点v的第1个未被访问的邻接顶点
       { T->firstchild=p; // 顶点w是根的第1个孩子结点
         first=FALSE; // 树T有第1个孩子结点的标志
       }
       else // 顶点w是顶点v的其他未被访问的邻接顶点
         q->nextsibling=p; // 是上一邻接顶点的兄弟姐妹结点
                           // for循环的第1次不通过此处，以后q已赋值
       q=p; // q指向p所指结点
       DFSTree(G,w,q); // 从第w个顶点出发深度优先遍历图G，建立子生成树q
     }
 }

 void DFSForest(Graph G,CSTree &T)
 { // 建立无向图G的深度优先生成森林的(最左)孩子(下一个)兄弟链表T。算法7.7
   CSTree p,q; // 孩子-兄弟二叉链表结点的指针类型
   int v;
   T=NULL; // 初始化生成森林的根结点为空
   for(v=0;v<G.vexnum;++v) // 对于所有顶点
     visited[v]=FALSE; // 赋初值
   for(v=0;v<G.vexnum;++v) // 对所有顶点v
     if(!visited[v]) // 第v个顶点不曾被访问
     { // 第v个顶点为新的生成树的根结点
       p=(CSTree)malloc(sizeof(CSNode)); // 动态生成根结点
       p->data=GetVex(G,v); // 给根结点赋值
       p->firstchild=NULL; // 结点的firstchild域和nextsibling域赋空
       p->nextsibling=NULL; // 以下将p所指结点插到树T中
       if(!T) // p所指结点是第1棵生成树T的根结点
         T=p; // T指向p所指结点
       else // p是其他生成树的根(前一棵树根的“兄弟”)
         q->nextsibling=p; // for循环的第1次，T=NULL，不通过此处，以后q已由下句赋值
       q=p; // q指示当前生成树的根
       DFSTree(G,v,p); // 建立以p为根的生成树
     }
 }

 void main()
 {
   Graph g;
   CSTree t;
   printf("请选择无向图\n");
   CreateGraph(g); // 构造无向图g
   Display(g); // 输出无向图g
   DFSForest(g,t); // 建立无向图g的深度优先生成森林的孩子-兄弟链表t
   printf("先序遍历生成森林：\n");
   PreOrderTraverse(t,Visit); // 先序遍历生成森林的孩子-兄弟链表t
   printf("\n");
 }
