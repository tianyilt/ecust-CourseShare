 // algo6-2.cpp 实现算法6.13的程序
 #include"c1.h"
 #include"c6-5.h" // 赫夫曼树和赫夫曼编码的存储结构
 #include"func6-2.cpp" // algo6-1.cpp和algo6-2.cpp要调用的2个函数

 void HuffmanCoding(HuffmanTree &HT,HuffmanCode &HC,int* w,int n)
 // 前半部分为算法6.12的前半部分
 { // w存放n个字符的权值(均>0)，构造赫夫曼树HT，并求出n个字符的赫夫曼编码HC
   unsigned cdlen;
 #include"func6-3.cpp" // 算法6.12的前半部分
   // 以下为算法6.13，无栈非递归遍历赫夫曼树，求赫夫曼编码
   HC=(HuffmanCode)malloc((n+1)*sizeof(char*));
   // 分配n个字符编码的头指针向量([0]不用)
   cd=(char*)malloc(n*sizeof(char)); // 分配求编码的工作空间
   c=m; // m=2×n-1，从最后一个结点(根)开始
   cdlen=0; // 码长的初值为0
   for(i=1;i<=m;++i)
     HT[i].weight=0; // 求编码不再需要权值域，改作结点状态标志，0表示其左右孩子都不曾被访问
   while(c) // 未到叶子结点的孩子域
   { if(HT[c].weight==0) // 左右孩子都不曾被访问
     { // 向左
       HT[c].weight=1; // 左孩子被访问过，右孩子不曾被访问的标志
       if(HT[c].lchild!=0) // 有左孩子(不是叶子结点)
       { c=HT[c].lchild; // 置c为其左孩子序号(向叶子方向走一步)
         cd[cdlen++]='0'; // 左分支编码为0
       }
       else if(HT[c].rchild==0) // 序号c为叶子结点(既没有左孩子，也没有右孩子)
       { // 登记叶子结点的字符的编码
         HC[c]=(char*)malloc((cdlen+1)*sizeof(char)); // 生成编码空间
         cd[cdlen]='\0'; // 最后一个位置赋0(串结束符)
         strcpy(HC[c],cd); // 复制编码(串)
       }
     }
     else if(HT[c].weight==1) // 左孩子被访问过，右孩子不曾被访问
     { // 向右
       HT[c].weight=2; // 左右孩子均被访问过的标志
       if(HT[c].rchild!=0) // 有右孩子(不是叶子结点)
       { c=HT[c].rchild; // 置c为其右孩子序号(向叶子方向走一步)
         cd[cdlen++]='1'; // 右分支编码为1
       }
     }
     else // 左右孩子均被访问过(HT[c].weight==2)，向根结点方向退一步
     { c=HT[c].parent; // 置c为其双亲序号(向根方向退一步)
       --cdlen; // 退到父结点，编码长度减1
     }
   }
   free(cd); // 释放求编码的空间
 }

 #include"func6-4.cpp" // 主函数
