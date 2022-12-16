 // algo6-1.cpp 求赫夫曼编码。实现算法6.12的程序
 #include"c1.h"
 #include"c6-5.h" // 赫夫曼树和赫夫曼编码的存储结构
 #include"func6-2.cpp" // algo6-1.cpp和algo6-2.cpp要调用的2个函数

 void HuffmanCoding(HuffmanTree &HT,HuffmanCode &HC,int* w,int n) // 算法6.12
 { // w存放n个字符的权值(均>0)，构造赫夫曼树HT，并求出n个字符的赫夫曼编码HC
   int start;
   unsigned f;
 #include"func6-3.cpp" // 算法6.12的前半部分，以下是从叶子到根逆向求每个字符的赫夫曼编码
   HC=(HuffmanCode)malloc((n+1)*sizeof(char*));
   // 分配n个字符编码的头指针向量([0]不用)
   cd=(char*)malloc(n*sizeof(char)); // 分配求编码的工作空间
   cd[n-1]='\0'; // 编码结束符
   for(i=1;i<=n;i++)
   { // 逐个字符求赫夫曼编码
     start=n-1; // 编码结束符位置
     for(c=i,f=HT[i].parent;f!=0;c=f,f=HT[f].parent) // 从叶子到根逆向求编码
       if(HT[f].lchild==c) // c是其双亲的左孩子
         cd[--start]='0'; // 由叶子向根赋值'0'
       else // c是其双亲的右孩子
         cd[--start]='1'; // 由叶子向根赋值'1'
     HC[i]=(char*)malloc((n-start)*sizeof(char)); // 为第i个字符编码分配空间
     strcpy(HC[i],&cd[start]); // 从cd复制编码(串)到HC
   }
   free(cd); // 释放工作空间
 }

 #include"func6-4.cpp" // 主函数
