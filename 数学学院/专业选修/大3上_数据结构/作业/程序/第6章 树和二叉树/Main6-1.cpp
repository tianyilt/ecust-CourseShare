 // main6-1.cpp 检验bo6-1.cpp的主程序，利用条件编译选择数据类型为char或int
 // #define CHAR 1 // 字符型。第2行
 #define CHAR 0 // 整型(二者选一)。第3行
 #include"func6-1.cpp" // 利用条件编译，在主程序中选择结点的类型，访问树结点的函数
 #include"c6-1.h" // 二叉树的顺序存储结构
 #include"bo6-1.cpp" // 二叉树顺序存储结构的基本操作 

 void main()
 {
   Status i;
   int j;
   position p;
   TElemType e;
   SqBiTree T,s;
   InitBiTree(T); // 初始化二叉树T
   CreateBiTree(T); // 建立二叉树T
   printf("建立二叉树后，树空否？%d(1：是 0：否)。树的深度=%d。\n",BiTreeEmpty(T),
   BiTreeDepth(T));
   i=Root(T,e); // 将二叉树T的根的值赋给e
   if(i) // 二叉树T非空
     printf("二叉树的根为"form"。\n",e);
   else
     printf("树空，无根。\n");
   printf("层序遍历二叉树：\n");
   LevelOrderTraverse(T,visit); // 层序遍历二叉树T
   printf("中序遍历二叉树：\n");
   InOrderTraverse(T,visit); // 中序遍历二叉树T
   printf("后序遍历二叉树：\n");
   PostOrderTraverse(T,visit); // 后序遍历二叉树T
   printf("请输入待修改结点的层号 本层序号：");
   scanf("%d%d",&p.level,&p.order);
   e=Value(T,p); // 将二叉树T中位置p的结点的值赋给e
   printf("待修改结点的原值为"form"，请输入新值：",e);
   scanf("%*c"form"%*c",&e);
   Assign(T,p,e); // 将e的值赋给二叉树T中位置p的结点
   printf("先序遍历二叉树：\n");
   PreOrderTraverse(T,visit); // 先序遍历二叉树T
   printf("结点"form"的双亲为"form"，左右孩子分别为",e,Parent(T,e));
   printf(form"、"form"，左右兄弟分别为",LeftChild(T,e),RightChild(T,e));
   printf(form"、"form"。\n",LeftSibling(T,e),RightSibling(T,e));
   InitBiTree(s); // 初始化二叉树s
   printf("建立右子树为空的树s：\n");
   CreateBiTree(s); // 建立二叉树s
   printf("树s插到树T中，请输入树T中树s的双亲结点 s为左(0)或右(1)子树：");
   scanf(form"%d",&e,&j);
   InsertChild(T,e,j,s);
   // 将树s插到树T中，结点e作为树s的双亲结点，根据j的值确定树s是e的左或右子树
   Print(T); // 逐层、按本层序号输出二叉树T
   printf("删除子树，请输入其根结点的双亲的层号 本层序号 其为双亲的左(0)或右(1)子树：");
   scanf("%d%d%d",&p.level,&p.order,&j);
   DeleteChild(T,p,j); // 删除二叉树T中位置p结点的左(j=0)或右(j=1)子树
   Print(T); // 逐层、按本层序号输出二叉树T
   ClearBiTree(T); // 清空二叉树T
   printf("清空二叉树后，树空否？%d(1：是 0：否)。树的深度=%d。\n",BiTreeEmpty(T),
   BiTreeDepth(T));
   i=Root(T,e); // 将二叉树T的根的值赋给e
   if(i) // 二叉树T非空
     printf("二叉树的根为"form"。\n",e);
   else // 二叉树T为空
     printf("树空，无根。\n");
 }
