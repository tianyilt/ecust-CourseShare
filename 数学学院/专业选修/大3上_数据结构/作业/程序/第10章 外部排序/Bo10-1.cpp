 // bo10-1.cpp k-路平衡归并的函数，包括算法11.1～11.3
 void input(int i,RedType &a)
 { // 从第i个文件(归并段)读入记录到a
   fscanf(fp[i],"%d %d",&a.key,&a.otherinfo);
 }

 void output(RedType a)
 { // 将a写至全局变量fp[k]所指的文件中并输出
   static int col=0; // 静态变量，计数，换行用
   fprintf(fp[k],"%d %d\n",a.key,a.otherinfo); // 将记录a写入大文件fp[k]
   Print(a); // 输出a，新增
   if(++col%M==0)
     printf("\n"); // 换行
 }

 void Adjust(LoserTree ls,int s) // 算法11.2
 { // 沿从叶子结点全局变量b[s]到根结点全局变量ls[1]的路径调整败者树，胜者存ls[0]
   int i,t;
   t=(s+k)/2; // t是全局变量b[s]的双亲结点的序号
   while(t>0) // t还在败者树上
   { if(b[s].key>b[ls[t]].key) // b[s]的关键字大于其双亲结点的关键字(是败者)
     { i=s; // 交换s和ls[t]
       s=ls[t]; // s指示胜者，将和b[s]的双亲结点的双亲结点比较
       ls[t]=i; // b[s]的双亲结点指示败者b[s]
     }
     t=t/2; // t为b[s]的双亲结点的双亲结点的序号
   }
   ls[0]=s; // 胜者存于败者树之外的[0]
 }

 void CreateLoserTree(LoserTree ls)
 { // 已知全局变量b[0]～b[k-1]为完全二叉树全局变量ls的叶子结点，存有k个关键字，
   // 沿从序号最大的叶子到根的k条路径将ls调整成为败者树。算法11.3
   int i;
   b[k].key=MIN_KEY; // [k]中存最小关键字
   for(i=1;i<k;++i)
     ls[i]=k; // 设置ls中“败者”的初值为有最小关键字的序号(调整中必会被败者取代)
   for(i=k-1;i>=0;--i) // 依次从序号最大的叶子结点b[k-1]～b[0]出发调整败者树
     Adjust(ls,i); // 沿从叶子结点b[i]到根结点ls[1]的路径调整败者树，胜者存ls[0]
 }

 void K_Merge(LoserTree ls)
 { // 利用全局变量败者树ls将编号从[0]～[k-1]的k个输入归并段中的记录归并到输出归并段。
   // 全局变量b[0]～b[k-1]为败者树上的k个叶子结点，分别存放k个输入归并段中当前
   // 记录的关键字。修改算法11.1
   int i;
   for(i=0;i<k;++i) // 依次从k个输入归并段
   { input(i,b[i]); // 读入该段第1个记录到外结点b[i]
     if(feof(fp[i])) // 读记录失败(文件中无记录)
       b[i].key=MAX_KEY; // 设置外结点关键字的值为最大
   }
   CreateLoserTree(ls);
   // 初建败者树ls[1..k-1]，树外结点ls[0]指示b[0]～b[k-1]中关键字最小者(胜者)的序号
   while(b[ls[0]].key!=MAX_KEY) // 胜出的关键字不是最大关键字(b[ls[0]]是文件中的记录)
   { output(b[ls[0]]); // 将b[ls[0]]输出到文件
     input(ls[0],b[ls[0]]); // 从编号为ls[0]的输入归并段中读入下一个记录到b[ls[0]]
     if(feof(fp[ls[0]])) // 读记录失败(文件中已无记录)
       b[ls[0]].key=MAX_KEY; // 设置外结点关键字的值为最大
     Adjust(ls,ls[0]);
     // 沿从取得新值的叶子结点b[ls[0]]到根结点ls[1]的路径调整败者树，选出新的最小关键字
   }
 }
