 // algo8-4.cpp 检验bo8-2.cpp的程序
 #include"c1.h"
 #include"func8-5.cpp" // 包括数据元素类型的定义及对它的操作
 #include"c8-2.h" // 对两个数值型关键字比较的约定
 typedef ElemType TElemType; // 定义二叉树的元素类型为数据元素类型
 #include"c6-2.h" // 二叉链表的存储结构
 #include"func8-4.cpp" // 包括算法9.5(a)和bo6-2.cpp
 #include"bo8-2.cpp" // 二叉排序树的基本操作(4个)，包括算法9.5(b)、9.6～9.8
 void main()
 {
   BiTree dt,p;
   int i,n;
   KeyType j;
   ElemType r;
   Status k;
   FILE *f; // 文件指针类型
   f=fopen("f8-4.txt","r"); // 打开数据文件f8-4.txt
   fscanf(f,"%d",&n); // 由数据文件输入数据元素个数
   InitDSTable(dt); // 构造空二叉排序树dt
   for(i=0;i<n;i++) // 依次在二叉排序树dt中插入n个数据元素
   { InputFromFile(f,r); // 由数据文件输入数据元素的值并赋给r，在func8-5.cpp中
     k=InsertBST(dt,r); // 依次将数据元素r插入二叉排序树dt中
     if(!k) // 插入数据元素r失败
       printf("二叉排序树dt中已存在关键字为%d的数据，故(%d,%d)无法插入到dt中。\n",
       r.key,r.key,r.others);
   }
   fclose(f); // 关闭数据文件
   printf("中序遍历二叉排序树dt：\n");
   TraverseDSTable(dt,Visit); // 中序遍历二叉排序树dt，确定dt是否排序
   printf("\n先序遍历二叉排序树dt：\n");
   PreOrderTraverse(dt,Visit); // 先序遍历二叉排序树dt，确定dt的形态
   printf("\n请输入待查找的关键字的值：");
   InputKey(j); // 由键盘输入关键字j，在func8-5.cpp中
   p=SearchBST(dt,j); // 在dt中递归地查找关键字等于j的结点
   if(p) // 找到，p指向该结点
   { printf("dt中存在关键字为%d的结点。",j);
     DeleteBST(dt,j); // 在dt中删除关键字等于j的结点
     printf("删除此结点后，中序遍历二叉排序树dt：\n");
     TraverseDSTable(dt,Visit); // 中序遍历二叉排序树dt，确定dt是否排序
     printf("\n先序遍历二叉排序树dt：\n");
     PreOrderTraverse(dt,Visit); // 先序遍历二叉排序树dt，确定dt的形态
     printf("\n");
   }
   else // 未找到，p为空
     printf("dt中不存在关键字为%d的结点。\n",j);
   DestroyDSTable(dt); // 销毁二叉排序树dt
 }
