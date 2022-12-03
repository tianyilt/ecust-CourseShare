 // algo10-4.cpp 通过置换-选择排序产生不等长的初始归并段文件
 #include"c1.h"
 typedef int KeyType; // 定义关键字的类型为整型
 typedef int InfoType; // 定义其他数据项的类型为整型
 #include"c9-1.h" // 记录的数据类型
 #define MAX_KEY INT_MAX // 最大关键字
 #define w 6 // 设内存工作区可容纳的记录个数
 #define M 10 // 设输出M个数据换行
 typedef int LoserTree[w];
 // [1..w-1]是败者树的非叶子结点，[0]中是胜者，存相应叶子的序号
 typedef struct
 { RedType rec; // 记录
   int rnum; // 所属归并段的段号
 }WorkArea[w]; // 内存工作区，容量为w

 void InputFromFile(FILE* f,RedType &c)
 { // 从文件输入记录的函数
   fscanf(f,"%d%d",&c.key,&c.otherinfo);
 }

 void OutputToFile(FILE* f,RedType &c)
 { // 向文件输出记录的函数
   fprintf(f,"%d %d\n",c.key,c.otherinfo);
 }

 void Select_MiniMax(LoserTree ls,WorkArea wa,int q) // 算法11.6
 { // 从wa[q]起到败者树的根比较选择当前段的最小记录给ls[0]
   int s,p,t=(w+q)/2; // t是败者树上wa[q]的双亲结点序号
   for(p=ls[t];t>0;t=t/2,p=ls[t]) // 由wa[q]的双亲结点逐级向根结点比较
     if(wa[p].rnum<wa[q].rnum||wa[p].rnum==wa[q].rnum&&
     wa[p].rec.key<wa[q].rec.key) // wa[q]的双亲结点的段值小或段值同关键字小
     { s=q; // wa[q]作为新的败者
       q=ls[t]; // q指示新的胜利者，继续向上比较
       ls[t]=s;
     }
   ls[0]=q; // 最终胜利者的序号赋给ls[0]
 }

 void Construct_Loser(LoserTree ls,WorkArea wa,FILE *fi)
 { // 输入w个记录到内存工作区wa，建得败者树ls，选出关键字最小的记录并由s[0]指示
   // 其在wa中的位置。修改算法11.7
   int i;
   for(i=0;i<w;++i)
     wa[i].rnum=ls[i]=0; // 初始化，工作区的段值为0(最小)，败者树指示最后调整的wa[0]
   for(i=w-1;i>=0;--i) // 从后到前
   { InputFromFile(fi,wa[i].rec); // 由文件输入1个记录
     wa[i].rnum=1; // 其段号为“1”
     Select_MiniMax(ls,wa,i); // 根据新输入的记录调整败者树
   }
 }

 void get_run(LoserTree ls,WorkArea wa,int rc,int &rmax,FILE *fi,FILE *fo)
 { // 求得一个初始归并段，fi为输入文件指针，fo为输出文件指针，rc为当前段。修改算法11.5
   int q;
   KeyType minimax;
   while(wa[ls[0]].rnum==rc) // 选得的记录属当前段时
   { q=ls[0]; // q指示选得的记录在wa[]中的位置
     minimax=wa[q].rec.key; // minimax指示选得的记录的关键字
     OutputToFile(fo,wa[q].rec); // 将选得的记录写入输出文件
     printf("(%d,%d)",wa[q].rec.key,wa[q].rec.otherinfo); // 输出
     InputFromFile(fi,wa[q].rec); // 从输入文件读入下一记录，填补输出的空位
     if(feof(fi)) // 输入文件结束
       wa[q].rnum=rmax+1; // 虚设记录为下一段(属“rmax+1”段)
     else // 输入文件非空时
     { if(wa[q].rec.key<minimax)
       { // 新读入记录的关键字小于刚输出到文件的记录的关键字
         rmax=rc+1; // 设置下一段
         wa[q].rnum=rmax; // 新读入的记录属下一段
       }
       else // 新读入的记录属当前段
         wa[q].rnum=rc;
     }
     Select_MiniMax(ls,wa,q); // 从wa[q]起选择新的当段最小关键字的记录
   }
 }

 void Replace_Selection(LoserTree ls,WorkArea wa,FILE *fi)
 { // 在败者树ls和内存工作区wa上用置换-选择排序求初始归并段，
   // fi为已打开的输入文件(只读文件)指针。修改算法11.4
   int rc,rmax;
   FILE *fo; // 输出文件指针
   char filename[3]; // 有序小文件名
   Construct_Loser(ls,wa,fi); // 初建败者树
   rc=rmax=1; // rc指示当前生成的初始归并段的段号，初值为1
   do // rmax指示wa中关键字所属初始归并段的最大段号，初值为1
   { itoa(rc-1,filename,10); // rc-1作为临时的有序小文件的文件名
     fo=fopen(filename,"w"); // 以写的方式打开输出文件0，1，…
     printf("%s的内容为：",filename);
     get_run(ls,wa,rc,rmax,fi,fo); // 求得段号为rc的初始归并段文件
     printf("\n");
     fclose(fo); // 关闭输出文件
     rc=wa[ls[0]].rnum; // 设置下一段的段号
   }while(rc<=rmax); // “rc=rmax+1”标志输入文件的置换-选择排序已完成
   printf("共产生%d个初始归并段文件\n",rc-1);
 }

 void main()
 {
   FILE *fi;
   LoserTree ls;
   WorkArea wa;
   fi=fopen("f10-2.txt","r"); // 以读的方式打开无序大文件f10-2.txt
   Replace_Selection(ls,wa,fi); // 用置换-选择排序求初始归并段(有序小文件)
   fclose(fi); // 关闭无序大文件f10-2.txt
 }
