 // algo8-2.cpp 检验bo8-1.cpp(有序表部分)的程序
 #include"c1.h"
 #include"func8-2.cpp" // 包括数据元素类型的定义及对它的操作
 #include"c8-1.h" // 静态查找表的顺序存储结构
 #include"c8-2.h" // 对两个数值型关键字比较的约定
 #include"bo8-1.cpp" // 静态查找表(顺序表和有序表)的基本操作(7个)

 void main()
 {
   SSTable st;
   int i;
   KeyType s;
   Creat_OrdFromFile(st,"f8-2.txt"); // 由数据文件产生非降序查找表st
   printf("有序表为 ");
   Traverse(st,Visit); // 顺序输出静态查找表st
   printf("\n");
   printf("请输入待查找数据的关键字：");
   InputKey(s); // 由键盘输入关键字s，在func8-2.cpp中
   i=Search_Bin(st,s);
   // 在有序的静态查找表st中折半查找含有关键字s的项的序号
   if(i)
     printf("%d是第%d个数据的关键字\n",st.elem[i].key,i);
   else
     printf("未找到\n");
   Destroy(st); // 销毁有序的静态查找表st
 }
