 // main6-3.cpp 检验线索二叉树部分基本操作的程序
 #define CHAR 1 // 字符型。第2行
 //#define CHAR 0 // 整型(二者选一)。第3行
 #include"func6-1.cpp" // 利用条件编译，在主程序中选择结点的类型，访问树结点的函数
 #include"c6-3.h" // 二叉树的二叉线索存储结构
 #include"bo6-4.cpp" // 构造线索二叉树的基本操作
 #define FLAG 0 // 是否进行后序遍历的标志
 void main()
 {
   BiThrTree H,T;
   int i;
   for(i=1;i<=3;i++) // 循环3次，实现3种线索化和遍历
   {
 #if CHAR // CHAR值为非零，结点类型为字符
     printf("请按先序输入二叉树(如：ab三个空格表示a为根结点，b为左子树的二叉树)：\n");
 #else // CHAR值为零，结点类型为整型
     printf("请按先序输入二叉树(如：1 2 0 0 0表示1为根结点，2为左子树的二叉树)：\n");
 #endif
     CreateBiThrTree(T); // 按先序产生二叉树
     scanf("%*c"); // 吃掉回车符
     switch(i)
     { case 1:PreOrderThreading(H,T); // 在先序遍历的过程中，先序线索化二叉树
              printf("先序遍历(输出)线索二叉树：\n");
              PreOrderTraverse_Thr(H,visit); // 先序遍历(输出)线索二叉树
              break;
       case 2:InOrderThreading(H,T); // 在中序遍历的过程中，中序线索化二叉树
              printf("中序遍历(输出)线索二叉树：\n");
              InOrderTraverse_Thr(H,visit); // 中序遍历(输出)线索二叉树
              break;
       case 3:PostOrderThreading(H,T); // 在后序遍历的过程中，后序线索化二叉树
 #if FLAG // 当定义FLAG为1时，进行后序遍历
              printf("后序遍历(输出)线索二叉树：\n");
              PostOrderTraverse_Thr(H,visit);
 #endif
     }
     printf("\n");
     DestroyBiThrTree(H); // 销毁线索二叉树H
   }
 }
