 // algo8-8.cpp 检验bo8-6.cpp的程序
 #include"c1.h"
 #define N 20 // 数组可容纳的数据元素个数
 #define LENGTH 27 // 结点的最大度(0+大写英文字母)
 struct Others // 记录的其他部分
 { int order; // 整型变量，顺序
 };
 #define Nil 0 // 定义串结束符为0
 static int count=0; // 调用TraverseDSTable()的次数，初始为0
 #include"c8-7.h" // 键树记录的存储结构
 #include"c8-4.h" // 记录类型
 #include"c8-9.h" // Trie键树的存储结构
 #include"c8-10.h" // 对两个字符串型关键字的比较约定

 int ord(char c)
 { if(c==Nil)
     return 0; // 遇字符串结束符返回0
   else
     return toupper(c)-'A'+1; // 英文字母返回其在字母表中的序号(此处不分大小写)
 }

 #include"bo8-6.cpp" // Trie树的基本操作，包括算法9.16
 #include"func8-7.cpp" // 包括对键树的输入输出操作

 void main()
 {
   TrieTree t;
   int i,j=0; // 数据个数，初始为0
   KeyType k;
   Record *p,r[N]; // 记录数组
   FILE *f; // 文件指针类型
   InitDSTable(t); // 构造空的Trie树t
   f=fopen("f8-5.txt","r"); // 打开数据文件f8-5.txt
   do // 将数据文件中的记录依次读入r并插入Trie树t中
   { i=fscanf(f,"%s%d",&r[j].key.ch,&r[j].others.order); // 由文件输入数据给r[j]
     if(i!=-1) // 输入数据成功
     { r[j].key.num=strlen(r[j].key.ch); // 给r[j].key.num域赋值
       p=SearchTrie(t,r[j].key); // 在Trie树t中查找关键字串等于r[j].key的记录
       if(!p) // t中不存在关键字为r[j].key的项
         InsertTrie(t,&r[j++]);
         // 将r[j]的地址及关键字串插入Trie树t中，记录数组的数据个数+1
       else // 在树t中已存在关键字为r[j].key的项
         printf("树t中已存在关键字为%s的记录，故(%s,%d)无法插入。\n",
         r[j].key.ch,r[j].key.ch,r[j].others.order);
     }
   }while(!feof(f)&&j<N); // 未到数据文件的结尾且记录数组未满
   fclose(f); // 关闭数据文件
   printf("按关键字符串的顺序遍历树t：\n");
   TraverseDSTable(t,Visit); // 按关键字符串的顺序遍历Trie树t
   printf("\n请输入待查找记录的关键字符串：");
   InputKey(k.ch); // 输入待查找记录的关键字符串给k.ch
   k.num=strlen(k.ch); // 给k.num赋值
   p=SearchTrie(t,k); // 在Trie树t查找关键字等于k的记录
   if(p) // 存在该记录
     Visit(p); // 输出该记录
   else // 不存在该记录
     printf("未找到"); // 输出未找到信息
   printf("\n");
   DestroyDSTable(t); // 销毁Trie树t
 }
