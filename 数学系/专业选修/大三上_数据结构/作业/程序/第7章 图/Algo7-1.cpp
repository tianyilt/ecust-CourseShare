 // algo7-1.cpp 检验2种结构调用算法7.4～7.6(深度优先和广度优先)搜索遍历的程序
 // 如果采用ALGraph类型为图的存储结构，将下行作为注释
 #define MG // 图的存储结构为MGraph。第3行
 #include"c1.h"
 #include"func7-1.cpp" // 包括顶点信息类型的定义及对它的操作
 #ifdef MG // 图的存储结构为MGraph
   #include"func7-2.cpp" // 包括弧(边)的相关信息类型的定义及对它的操作
   #include"c7-1.h" // 图的数组(邻接矩阵)存储结构
   #include"bo7-1.cpp" // 图的数组(邻接矩阵)存储结构的基本操作
   typedef MGraph Graph; // 定义图的存储结构为邻接矩阵
 #else // 图的存储结构为ALGraph
   #include"func7-4.cpp" // 弧(边)的相关信息类型的定义及对它的操作
   #include"c7-2'.h" // 图的邻接表存储结构(与单链表的变量类型建立联系)
   #include"bo7-2.cpp" // 邻接表存储结构的基本操作
   typedef ALGraph Graph; // 定义图的存储结构为邻接表
 #endif
 #include"bo7-3.cpp" // 算法7.4～7.6

 void main()
 {
   Graph g; // 抽象的图类型g
   char filename[13]; // 存储数据文件名(包括路径)
   printf("请输入数据文件名：");
   scanf("%s",filename);
  #ifdef MG // 图的数组(邻接矩阵)存储结构
   CreateFromFile(g,filename,0); // 创建无相关信息的图
  #else // 图的邻接表存储结构
   CreateFromFile(g,filename); // 创建无相关信息的图
  #endif
   printf("深度优先搜索遍历的结果：\n");
   DFSTraverse(g,Visit);
   printf("广度优先搜索遍历的结果：\n");
   BFSTraverse(g,Visit);
 }
