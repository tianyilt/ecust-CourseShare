 // bo6-1.cpp 二叉树的顺序存储(存储结构由c6-1.h定义)的基本操作(23个)
 #define ClearBiTree InitBiTree // 在顺序存储结构中，两函数完全一样
 #define DestroyBiTree InitBiTree // 在顺序存储结构中，两函数完全一样
 void InitBiTree(SqBiTree T)
 { // 构造空二叉树T。因为T是数组名，故不需要&
   int i;
   for(i=0;i<MAX_TREE_SIZE;i++)
     T[i]=Nil; // 初值为空(Nil在主程中定义)
 }

 void CreateBiTree(SqBiTree T)
 { // 按层序次序输入二叉树中结点的值(字符型或整型)，构造顺序存储的二叉树T
   int i=0;
   InitBiTree(T); // 构造空二叉树T
 #if CHAR // CHAR值为非零，结点类型为字符
   int n;
   char s[MAX_TREE_SIZE];
   printf("请按层序输入结点的值(字符)，空格表示空结点，结点数≤%d：\n",MAX_TREE_SIZE);
   gets(s); // 输入字符串
   n=strlen(s); // 求字符串的长度
   for(;i<n;i++) // 将字符串赋值给T
     T[i]=s[i];
 #else // CHAR值为零，结点类型为整型
   printf("请按层序输入结点的值(整型)，0表示空结点，输999结束。结点数≤%d：\n",
   MAX_TREE_SIZE);
   while(1) // 永真循环
   { scanf("%d",&T[i]); // 按层序依次输入
     if(T[i]==999) // 输入结束
     { T[i]=Nil; // 恢复为空结点
       break; // 跳出循环
     }
     i++; // 计数加1
   }
 #endif
   for(i=1;i<MAX_TREE_SIZE;i++) // 从第2个(非根)结点开始检查
     if(T[i]!=Nil&&T[(i+1)/2-1]==Nil) // 此结点不空但无双亲
     { printf("出现无双亲的非根结点"form"\n",T[i]);
       exit(OVERFLOW);
     }
 }

 Status BiTreeEmpty(SqBiTree T)
 { // 初始条件：二叉树T存在。操作结果：若T为空二叉树，则返回TRUE；否则FALSE
   if(T[0]==Nil) // 根结点为空，则树空
     return TRUE;
   else
     return FALSE;
 }

 int BiTreeDepth(SqBiTree T)
 { // 初始条件：二叉树T存在。操作结果：返回T的深度
   int i;
   if(T[0]==Nil) // 根结点为空，则树空
     return 0; // 空树的深度为0
   for(i=MAX_TREE_SIZE-1;i>=0;i--) // 从数组的后面向前找起
     if(T[i]!=Nil) // 找到最后一个结点，其序号为i
       break;
   return (int)(log(i+1)/log(2)+1.1); // 序号为i的结点的深度就是树的深度
 }

 Status Root(SqBiTree T,TElemType &e)
 { // 初始条件：二叉树T存在
   // 操作结果：当T不空，用e返回T的根，返回OK；否则返回ERROR，e无定义
   if(BiTreeEmpty(T)) // T空
     return ERROR;
   else
   { e=T[0];
     return OK;
   }
 }

 TElemType Value(SqBiTree T,position e)
 { // 初始条件：二叉树T存在，e是T中某个结点(的位置)
   // 操作结果：返回处于位置e(层,本层序号)的结点的值
   return T[int(pow(2,e.level-1)+e.order-2)];
 }

 Status Assign(SqBiTree T,position e,TElemType value)
 { // 初始条件：二叉树T存在，e是T中某个结点(的位置)
   // 操作结果：给处于位置e(层,本层序号)的结点赋新值value
   int i=int(pow(2,e.level-1)+e.order-2); // 将层、本层序号转为数组的序号
   if(i!=0&&value!=Nil&&T[(i+1)/2-1]==Nil) // 不是根结点，值非空，但双亲为空
     return ERROR;
   else if(value==Nil&&(T[i*2+1]!=Nil||T[i*2+2]!=Nil)) // 给双亲赋空值但有孩子结点
     return ERROR;
   T[i]=value; // 以上2种情况之外，给结点赋新值
   return OK;
 }

 TElemType Parent(SqBiTree T,TElemType e)
 { // 初始条件：二叉树T存在，e是T中某个结点
   // 操作结果：若e是T的非根结点，则返回它的双亲；否则返回“空”
   int i;
   if(T[0]==Nil) // 空树
     return Nil; // 返回“空”
   for(i=1;i<=MAX_TREE_SIZE-1;i++) // 从二叉树的第2个结点开始查找
     if(T[i]==e) // 找到e
       return T[(i+1)/2-1]; // 返回其双亲结点的值
   return Nil; // 未找到e
 }

 TElemType LeftChild(SqBiTree T,TElemType e)
 { // 初始条件：二叉树T存在，e是T中某个结点
   // 操作结果：返回e的左孩子。若e无左孩子，则返回“空”
   int i;
   for(i=0;i<=(MAX_TREE_SIZE-2)/2;i++) // 从T的第1个结点到最后一个可能有左孩子的结点
     if(T[i]==e) // 找到e
       return T[i*2+1]; // 返回e的左孩子的值
   return Nil; // 未找到e
 }

 TElemType RightChild(SqBiTree T,TElemType e)
 { // 初始条件：二叉树T存在，e是T中某个结点
   // 操作结果：返回e的右孩子。若e无右孩子，则返回“空”
   int i;
   for(i=0;i<=(MAX_TREE_SIZE-3)/2;i++) // 从T的第1个结点到最后一个可能有右孩子的结点
     if(T[i]==e) // 找到e
       return T[i*2+2]; // 返回e的右孩子的值
   return Nil; // 未找到e
 }

 TElemType LeftSibling(SqBiTree T,TElemType e)
 { // 初始条件：二叉树T存在，e是T中某个结点
   // 操作结果：返回e的左兄弟。若e是T的左孩子或无左兄弟，则返回“空”
   int i;
   if(T[0]==Nil) // 空树
     return Nil; // 返回“空”
   for(i=1;i<=MAX_TREE_SIZE-1;i++) // 从二叉树T的第2个结点开始查找
     if(T[i]==e&&i%2==0) // 找到e且其序号为偶数(是右孩子)
       return T[i-1]; // 返回e的左兄弟的值
   return Nil; // 未找到e
 }

 TElemType RightSibling(SqBiTree T,TElemType e)
 { // 初始条件：二叉树T存在，e是T中某个结点
   // 操作结果：返回e的右兄弟。若e是T的右孩子或无右兄弟，则返回“空”
   int i;
   if(T[0]==Nil) // 空树
     return Nil; // 返回“空”
   for(i=1;i<=MAX_TREE_SIZE-2;i++) // 从二叉树T的第2个结点开始查找
     if(T[i]==e&&i%2) // 找到e且其序号为奇数(是左孩子)
       return T[i+1]; // 返回e的右兄弟的值
   return Nil; // 未找到e
 }

 void Move(SqBiTree q,int j,SqBiTree T,int i) // InsertChild()用到。新增
 { // 把从q的j结点开始的子树移为从T的i结点开始的子树
   if(i>=MAX_TREE_SIZE) // i结点超出了存储范围
     exit(OVERFLOW);
   if(q[2*j+1]!=Nil) // q的左子树不空
     Move(q,(2*j+1),T,(2*i+1)); // 把q的j结点的左子树移为T的i结点的左子树
   if(q[2*j+2]!=Nil) // q的右子树不空
     Move(q,(2*j+2),T,(2*i+2)); // 把q的j结点的右子树移为T的i结点的右子树
   T[i]=q[j]; // 把q的j结点移为T的i结点
   q[j]=Nil; // 把q的j结点置空
 }

 void InsertChild(SqBiTree T,TElemType p,int LR,SqBiTree c)
 { // 初始条件：二叉树T存在，p是T中某个结点的值，LR为0或1，
   //           非空二叉树c与T不相交且右子树为空
   // 操作结果：根据LR为0或1，插入c为T中p结点的左或右子树。
   //           p结点的原有左或右子树则成为c的右子树
   int j,k;
   for(j=0;j<int(pow(2,BiTreeDepth(T)))-1;j++) // 查找p的序号
     if(T[j]==p) // j为p的序号
       break;
   k=2*j+1+LR; // k为p的左或右孩子的序号
   if(T[k]!=Nil) // p原来的左或右孩子不空
     Move(T,k,c,2); // 把从T的k结点开始的子树移为c的右子树
   Move(c,0,T,k); // 把树c移为从T的k结点开始的子树
 }

 typedef int QElemType; // 定义队列元素类型为整型(序号)
 #include "c3-2.h" // 链队列
 #include "bo3-2.cpp" // 链队列的基本操作
 Status DeleteChild(SqBiTree T,position p,int LR)
 { // 初始条件：二叉树T存在，p指向T中某个结点，LR为0或1
   // 操作结果：根据LR为0或1，删除T中p所指结点的左或右子树
   int i;
   Status k=OK; // 队列不空的标志
   LinkQueue q;
   InitQueue(q); // 初始化队列，用于存放待删除的结点
   i=(int)pow(2,p.level-1)+p.order-2; // 将层、本层序号转为数组的序号
   if(T[i]==Nil) // 此结点空
     return ERROR;
   i=i*2+1+LR; // 待删除子树的根结点在数组中的序号
   while(k)
   { if(T[2*i+1]!=Nil) // 左结点不空
       EnQueue(q,2*i+1); // 入队左结点的序号
     if(T[2*i+2]!=Nil) // 右结点不空
       EnQueue(q,2*i+2); // 入队右结点的序号
     T[i]=Nil; // 删除此结点
     k=DeQueue(q,i); // 出队结点的序号，其值赋给i，成功(队列不空)返回OK；否则返回ERROR
   }
   return OK;
 }

 void(*VisitFunc)(TElemType); // 函数变量
 void PreTraverse(SqBiTree T,int e)
 { // 递归先序遍历二叉树T中序号为e的子树，PreOrderTraverse()调用
   VisitFunc(T[e]); // 访问树T中序号为e的结点
   if(T[2*e+1]!=Nil) // 序号为e的结点的左子树不空
     PreTraverse(T,2*e+1); // 递归先序遍历树T中序号为e的结点的左子树
   if(T[2*e+2]!=Nil) // 序号为e的结点的右子树不空
     PreTraverse(T,2*e+2); // 递归先序遍历树T中序号为e的结点的右子树
 }

 void PreOrderTraverse(SqBiTree T,void(*Visit)(TElemType))
 { // 初始条件：二叉树存在，Visit是对结点操作的应用函数
   // 操作结果：先序遍历T，对每个结点调用函数Visit一次且仅一次
   VisitFunc=Visit;
   if(!BiTreeEmpty(T)) // 树不空
     PreTraverse(T,0); // 递归先序遍历树T中序号为0的树(树T自身)
   printf("\n");
 }

 void InTraverse(SqBiTree T,int e)
 { // 递归中序遍历二叉树T中序号为e的子树，InOrderTraverse()调用
   if(T[2*e+1]!=Nil) // 序号为e的结点的左子树不空
     InTraverse(T,2*e+1); // 递归中序遍历树T中序号为e的结点的左子树
   VisitFunc(T[e]); // 访问树T中序号为e的结点
   if(T[2*e+2]!=Nil) // 序号为e的结点的右子树不空
     InTraverse(T,2*e+2); // 递归中序遍历树T中序号为e的结点的右子树
 }

 void InOrderTraverse(SqBiTree T,void(*Visit)(TElemType))
 { // 初始条件：二叉树存在，Visit是对结点操作的应用函数
   // 操作结果：中序遍历T，对每个结点调用函数Visit一次且仅一次
   VisitFunc=Visit;
   if(!BiTreeEmpty(T)) // 树不空
     InTraverse(T,0); // 递归中序遍历树T中序号为0的树(树T自身)
   printf("\n");
 }

 void PostTraverse(SqBiTree T,int e)
 { // 递归后序遍历二叉树T中序号为e的子树，PostOrderTraverse()调用
   if(T[2*e+1]!=Nil) // 序号为e的结点的左子树不空
     PostTraverse(T,2*e+1); // 递归后序遍历树T中序号为e的结点的左子树
   if(T[2*e+2]!=Nil) // 序号为e的结点的右子树不空
     PostTraverse(T,2*e+2); // 递归后序遍历树T中序号为e的结点的右子树
   VisitFunc(T[e]); // 访问树T中序号为e的结点
 }

 void PostOrderTraverse(SqBiTree T,void(*Visit)(TElemType))
 { // 初始条件：二叉树T存在，Visit是对结点操作的应用函数
   // 操作结果：后序遍历T，对每个结点调用函数Visit一次且仅一次
   VisitFunc=Visit;
   if(!BiTreeEmpty(T)) // 树不空
     PostTraverse(T,0); // 递归后序遍历树T中序号为0的树(树T自身)
   printf("\n");
 }

 void LevelOrderTraverse(SqBiTree T,void(*Visit)(TElemType))
 { // 层序遍历二叉树T
   int i=MAX_TREE_SIZE-1,j;
   while(T[i]==Nil)
     i--; // 找到最后一个非空结点的序号
   for(j=0;j<=i;j++) // 从根结点起，按层序遍历二叉树
     if(T[j]!=Nil)
       Visit(T[j]); // 只遍历非空的结点
   printf("\n");
 }

 void Print(SqBiTree T)
 { // 逐层、按本层序号输出二叉树T
   int j,k;
   position p;
   TElemType e;
   for(j=1;j<=BiTreeDepth(T);j++) // j为当前层
   { printf("第%d层：",j);
     p.level=j; // 当前结点所在层
     for(k=1;k<=pow(2,j-1);k++)
     { p.order=k; // 当前结点在本层的顺序
       e=Value(T,p); // 该结点的值赋给e
       if(e!=Nil) // e非空
         printf("%d："form" ",k,e); // 输出在本层的顺序及值
     }
     printf("\n");
   }
 }
