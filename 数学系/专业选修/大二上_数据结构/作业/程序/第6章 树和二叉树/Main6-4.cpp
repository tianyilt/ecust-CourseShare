 // main6-4.cpp 检验bo6-5.cpp和bo6-6.cpp的程序
 #define CHAR 1 // 只可是字符型
 #include"func6-1.cpp" // 利用条件编译，在主程序中选择结点的类型，访问树结点的函数
 #include"c6-4.h" // 树的二叉链表(孩子-兄弟)存储结构
 #include"bo6-5.cpp" // 树的二叉链表(孩子-兄弟)基本操作
 #include"bo6-6.cpp" // 包括PreOrderTraverse()
 void main()
 {
   int i;
   CSTree T,p,q;
   TElemType e,e1;
   InitTree(T); // 构造空树T
   printf("构造空树后，树空否？%d(1：是 0：否)。树根为%c，树的深度为%d。\n",
   TreeEmpty(T),Root(T),TreeDepth(T));
   CreateTree(T); // 按层序构造树T
   printf("构造树T后，树空否？%d(1：是 0：否)。树根为%c，树的深度为%d。\n",
   TreeEmpty(T),Root(T),TreeDepth(T));
   printf("层序遍历树T：\n");
   LevelOrderTraverse(T,visit); // 层序遍历树T
   printf("请输入待修改的结点的值 新值：");
   scanf("%c%*c%c%*c",&e,&e1);
   Assign(T,e,e1); // 将树T中结点值为e的修改为e1
   printf("层序遍历修改后的树T：\n");
   LevelOrderTraverse(T,visit); // 层序遍历树T
   printf("%c的双亲是%c，长子是%c，下一个兄弟是%c。\n",e1,Parent(T,e1),
   LeftChild(T,e1),RightSibling(T,e1));
   printf("建立树p：\n");
   CreateTree(p); // 按层序构造树p
   printf("层序遍历树p：\n");
   LevelOrderTraverse(p,visit); // 层序遍历树p
   printf("将树p插到树T中，请输入T中p的双亲结点 子树序号：");
   scanf("%c%d%*c",&e,&i);
   q=Point(T,e); // 将指向树T中结点e的指针赋给q
   InsertChild(T,q,i,p); // 将树p插入树T中作为q所指结点的第i棵子树
   printf("层序遍历修改后的树T：\n");
   LevelOrderTraverse(T,visit); // 层序遍历树T
   printf("先根遍历树T：\n");
   PreOrderTraverse(T,visit); // 先根遍历树T
   printf("\n后根遍历树T：\n");
   PostOrderTraverse(T,visit); // 后根遍历树T
   printf("\n删除树T中结点e的第i棵子树，请输入e i：");
   scanf("%c%d",&e,&i);
   q=Point(T,e); // 将指向树T中结点e的指针赋给q
   DeleteChild(T,q,i); // 删除树T中q所指结点的第i棵子树
   printf("层序遍历修改后的树T：\n");
   LevelOrderTraverse(T,visit); // 层序遍历树T
   DestroyTree(T); // 销毁树T
 }
