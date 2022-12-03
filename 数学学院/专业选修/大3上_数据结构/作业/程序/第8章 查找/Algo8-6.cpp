 // algo8-6.cpp 检验bo8-4.cpp的程序
 #include"c1.h"
 #define m 3 // B_树的阶，现设为3
 int s=(m+1)/2; // s为分裂结点的中值
 typedef int KeyType; // 设关键字域为整型
 struct Others // 记录的其他部分
 { int order; // 整型变量，顺序
 };
 #include"c8-2.h" // 对两个数值型关键字比较的约定
 #define N 12 // 记录数组的数据元素个数
 #include"c8-4.h" // 记录类型
 #include"c8-5.h" // B_树的结点类型
 #include"c8-6.h" // B_树的查找结果类型
 #include"bo8-4.cpp" // B_树的基本操作，包括算法9.13和9.14
 #include"func8-6.cpp" // 包括对B_树的输入输出操作

 void main()
 {
   Record r[N]={{24,1},{45,2},{53,3},{12,4},{37,5},{50,6},{61,7},{90,8},
   {100,9},{70,10},{3,11},{37,12}}; // (记录元素存于数组中，以教科书中图9.16(a)为例)
   BTree t;
   Result u;
   KeyType j;
   int i;
   InitDSTable(t); // 构造空的B_树t
   for(i=0;i<N;i++) // 将记录数组r[N]的数据依次插入树t中
   { u=SearchBTree(t,r[i].key); // 在树t中查找是否已存在关键字为r[i].key的记录
     if(u.tag) // 在树t中已存在关键字为r[i].key的记录
       printf("树t中已存在关键字为%d的记录，故(%d,%d)无法插入。\n",r[i].key,
       r[i].key,r[i].others.order);
     else // 在树t中不存在关键字为r[i].key的记录
       InsertBTree(t,&r[i],u.pt,u.i);
       // 将r[i]的关键字和地址插入到t中结点u.pt的[u.i]和[u.i+1]之间
   }
   printf("按关键字的顺序遍历B_树t：\n");
   TraverseDSTable(t,Visit); // 按关键字的顺序遍历B_树t
   for(i=1;i<=4;i++) // 4次在树t中查找给定关键字的数据
   { printf("\n请输入待查找记录的关键字：");
     InputKey(j); // 输入关键字j
     u=SearchBTree(t,j); // 在树t中查找关键字为j的数据
     if(u.tag) // 找到
       Visit(*(u.pt),u.i); // 输出查找到的记录
     else // 未找到
       printf("未找到");
   }
   printf("\n");
   DestroyDSTable(t); // 销毁树t
 }
