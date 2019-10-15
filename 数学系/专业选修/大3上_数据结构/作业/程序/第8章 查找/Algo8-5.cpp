 // algo8-5.cpp 检验bo8-3.cpp的程序
 #include"c1.h"
 #include"func8-5.cpp" // 包括数据元素类型的定义及对它的操作
 #include"c8-2.h" // 对两个数值型关键字比较的约定
 typedef ElemType TElemType; // 定义二叉树的元素类型为数据元素类型
 #include"c8-3.h" // 平衡二叉树的存储结构
 typedef BSTree BiTree; // 定义二叉树的指针类型为平衡二叉树的指针类型
 #include"func8-4.cpp" // 包括算法9.5(a)和bo6-11.cpp
 //#define FLAG // 加此句在bo8-3.cpp中直接做RL和LR平衡处理。第9行
 #include"bo8-3.cpp" // 平衡二叉树的基本操作
 void main()
 {
   BSTree dt,p;
   int i,n;
   KeyType j;
   ElemType r;
   Boolean flag;
   Status k;
   FILE *f; // 文件指针类型
   f=fopen("f8-4.txt","r"); // 打开数据文件f8-4.txt
   fscanf(f,"%d",&n); // 由数据文件输入数据元素个数
   InitDSTable(dt); // 初始化空平衡二叉树dt
   for(i=0;i<n;i++) // 依次在平衡二叉树dt中插入n个数据元素
   { InputFromFile(f,r); // 由数据文件输入数据元素的值并赋给r，在func8-5.cpp中
     k=InsertAVL(dt,r,flag); // 在平衡二叉树dt中插入数据元素r，使仍为平衡二叉树
     if(k) // 插入数据元素r成功
     { printf("插入关键字为%d的结点后，按关键字顺序(中序)遍历平衡二叉树dt\n",r.key);
       TraverseDSTable(dt,Visit); // 按关键字顺序(中序)遍历二叉树dt，确定dt是否排序
       printf("\n先序遍历平衡二叉树dt\n");
       PreOrderTraverse(dt,Visit); // 先序遍历平衡二叉树dt，确定dt的形态
       printf("\n");
     }
     else // 插入数据元素r失败
       printf("平衡二叉树dt中已存在关键字为%d的数据，故(%d,%d)无法插入到dt中。\n",
       r.key,r.key,r.others);
   }
   fclose(f); // 关闭数据文件
   printf("请输入待查找的关键字的值：");
   InputKey(j); // 由键盘输入关键字j，在func8-5.cpp中
   p=SearchBST(dt,j); // 在平衡二叉树dt中递归地查找关键字等于j的结点
   if(p) // 找到，p指向该结点
    printf("dt中存在关键字为%d的结点，其值为(%d,%d)。\n",j,p->data.key,
    p->data.others);
   else
     printf("dt中不存在关键字为%d的结点。\n",j);
   DestroyDSTable(dt); // 销毁平衡二叉树dt
 }
