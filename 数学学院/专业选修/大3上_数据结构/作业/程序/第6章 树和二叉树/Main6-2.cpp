 // main6-2.cpp 检验二叉链表基本操作的主程序
 #define CHAR 1 // 字符型。第2行
 //#define CHAR 0 // 整型(二者选一)。第3行
 #include"func6-1.cpp" // 利用条件编译，在主程序中选择结点的类型，访问树结点的函数
 #include"c6-2.h" // 二叉树的二叉链表存储结构
 #include"bo6-2.cpp" // 二叉树的二叉链表存储结构的4个基本操作，func8-4.cpp等调用
 #include"bo6-3.cpp" // 二叉树的二叉链表存储结构的18个基本操作

 void main()
 {
   int i;
   BiTree T,p,c;
   TElemType e1,e2;
   InitBiTree(T); // 初始化二叉树T
   printf("构造空二叉树后，树空否？%d(1：是 0：否)。树的深度=%d。\n",BiTreeEmpty(T),
   BiTreeDepth(T));
   e1=Root(T); // e1为二叉树T的根结点的值
   if(e1!=Nil)
     printf("二叉树的根为"form"。\n",e1);
   else
     printf("树空，无根。\n");
 #if CHAR // CHAR值为非零，结点类型为字符
   printf("请按先序输入二叉树(如：ab三个空格表示a为根结点，b为左子树的二叉树)：\n");
 #else // CHAR值为零，结点类型为整型
   printf("请按先序输入二叉树(如：1 2 0 0 0表示1为根结点，2为左子树的二叉树)：\n");
 #endif
   CreateBiTree(T); // 建立二叉树T
   printf("建立二叉树后，树空否？%d(1：是 0：否)。树的深度=%d。\n",BiTreeEmpty(T),
   BiTreeDepth(T));
   e1=Root(T); // e1为二叉树T的根结点的值
   if(e1!=Nil)
     printf("二叉树的根为"form"。\n",e1);
   else
     printf("树空，无根。\n");
   printf("中序递归遍历二叉树：\n");
   InOrderTraverse(T,visit); // 中序递归遍历二叉树T
   printf("\n后序递归遍历二叉树：\n");
   PostOrderTraverse(T,visit); // 后序递归遍历二叉树T
   printf("\n请输入一个结点的值：");
   scanf("%*c"form,&e1);
   p=Point(T,e1); // p指向为e1的指针
   printf("结点的值为"form"。\n",Value(p));
   printf("欲改变此结点的值，请输入新值：");
   scanf("%*c"form"%*c",&e2); // 后一个%*c吃掉回车符，为调用CreateBiTree()做准备
   Assign(p,e2); // 将e2的值赋给p所指结点，代替e1
   printf("层序遍历二叉树：\n");
   LevelOrderTraverse(T,visit); // 层序递归遍历二叉树T
   e1=Parent(T,e2); // 将二叉树T中结点e2的双亲的值赋给e1
   if(e1!=Nil)
     printf(form"的双亲是"form"，",e2,e1);
   else
     printf(form"没有双亲，",e2);
   e1=LeftChild(T,e2); // 将二叉树T中结点e2的左孩子的值赋给e1
   if(e1!=Nil)
     printf("左孩子是"form"，",e1);
   else
     printf("没有左孩子，");
   e1=RightChild(T,e2); // 将二叉树T中结点e2的右孩子的值赋给e1
   if(e1!=Nil)
     printf("右孩子是"form"，",e1);
   else
     printf("没有右孩子，");
   e1=LeftSibling(T,e2); // 将二叉树T中结点e2的左兄弟的值赋给e1
   if(e1!=Nil)
     printf("左兄弟是"form"，",e1);
   else
     printf("没有左兄弟，");
   e1=RightSibling(T,e2); // 将二叉树T中结点e2的右兄弟的值赋给e1
   if(e1!=Nil)
     printf("右兄弟是"form"。\n",e1);
   else
     printf("没有右兄弟。\n");
   InitBiTree(c); // 初始化二叉树c
   printf("请构造一个右子树为空的二叉树c：\n");
 #if CHAR // CHAR值为非零，结点类型为字符
   printf("请按先序输入二叉树(如：ab三个空格表示a为根结点，b为左子树的二叉树)：\n");
 #else // CHAR值为零，结点类型为整型
   printf("请按先序输入二叉树(如：1 2 0 0 0表示1为根结点，2为左子树的二叉树)：\n");
 #endif
   CreateBiTree(c); // 建立二叉树c
   printf("中序递归遍历二叉树c：\n");
   InOrderTraverse(c,visit); // 中序递归遍历二叉树c
   printf("\n树c插到树T中，请输入树T中树c的双亲结点 c为左(0)或右(1)子树：");
   scanf("%*c"form"%d",&e1,&i);
   p=Point(T,e1); // p指向二叉树T中将作为二叉树c的双亲结点的e1
   InsertChild(p,i,c); // 将树c插入到二叉树T中作为结点e1(p所指)的左(i=0)或右(i=1)子树
   printf("先序递归遍历二叉树：\n");
   PreOrderTraverse(T,visit); // 先序递归遍历二叉树T
   printf("\n删除子树，请输入待删除子树的双亲结点 左(0)或右(1)子树：");
   scanf("%*c"form"%d",&e1,&i);
   p=Point(T,e1); // p指向二叉树T中待删除子树的双亲结点e1
   DeleteChild(p,i); // 删除p所指结点(e1)的左(i=0)或右(i=1)子树
   printf("先序递归遍历二叉树：\n");
   PreOrderTraverse(T,visit); // 先序递归遍历二叉树T
   printf("\n中序非递归遍历二叉树：\n");
   InOrderTraverse1(T,visit); // 中序非递归遍历二叉树T
   printf("中序非递归遍历二叉树(另一种方法)：\n");
   InOrderTraverse2(T,visit); // 中序非递归遍历二叉树T(另一种方法)
   DestroyBiTree(T); // 销毁二叉树T
 }
