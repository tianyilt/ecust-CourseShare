 // algo8-3.cpp 静态查找表(静态树表)的操作，包括算法9.3和9.4
 #include"c1.h"
 #include"func8-3.cpp" // 包括数据元素类型的定义及对它的操作
 #include"c8-1.h" // 静态查找表的顺序存储结构
 #include"c8-2.h" // 对两个数值型关键字比较的约定
 #include"bo8-1.cpp" // 静态查找表(顺序表和有序表)的基本操作(7个)
 typedef ElemType TElemType; // 定义二叉树的元素类型为数据元素类型
 #include"c6-2.h" // 二叉链表的存储结构
 #include"bo6-2.cpp" // 包括InitBiTree()，DestroyBiTree()和InOrderTraverse()函数
 #define N 100 // 静态查找表的最大表长，设置sw[]数组用到
 Status SecondOptimal(BiTree &T,ElemType R[],int sw[],int low,int high)
 { // 由有序表R[low..high]及其累计权值表sw(其中sw[0]==0)递归构造次优查找树T。算法9.3
   int j,i=low; // 有最小△Pi值的序号，初值设为当low==high(有序表仅1个元素)时的值
   double dw=sw[high]+sw[low-1]; // 教科书式9-13中的固定项
   double min=fabs(sw[high]-sw[low]); // △Pi的最小值，初值设为当low==high时的值
   for(j=low+1;j<=high;++j) // 当low≠high时，选择最小的△Pi值
     if(fabs(dw-sw[j]-sw[j-1])<min) // 找到小于min的值
     { i=j; // 更新有最小△Pi值的序号
       min=fabs(dw-sw[j]-sw[j-1]); // 更新△Pi的最小值
     }
   if(!(T=(BiTree)malloc(sizeof(BiTNode)))) // 生成结点失败
     return ERROR;
   T->data=R[i]; // 将有最小△Pi值的数据元素赋给树结点的数据域
   if(i==low) // 有最小△Pi值的序号是最小序号
     T->lchild=NULL; // 设左子树空
   else // 有最小△Pi值的序号不是最小序号
     SecondOptimal(T->lchild,R,sw,low,i-1); // 递归构造次优查找左子树
   if(i==high) // 有最小△Pi值的序号是最大序号
     T->rchild=NULL; // 设右子树空
   else // 有最小△Pi值的序号不是最大序号
     SecondOptimal(T->rchild,R,sw,i+1,high); // 递归构造次优查找右子树
   return OK;
 }

 void FindSW(int sw[],SSTable ST)
 { // 按照有序表ST中各数据元素的Weight域求累计权值数组sw，CreateSOSTree()调用
   int i;
   sw[0]=0; // 置边界值
   printf("\nsw=0 ");
   for(i=1;i<=ST.length;i++) // 由小到大计算累计权值sw[i]并输出
   { sw[i]=sw[i-1]+ST.elem[i].weight; // 累计权值[i]=累计权值[i-1]+[i]项权值
     printf("%5d",sw[i]);
   }
 }

 typedef BiTree SOSTree; // 次优查找树采用二叉链表的存储结构
 void CreateSOSTree(SOSTree &T,SSTable ST)
 { // 由有序表ST构造一棵次优查找树T。ST的数据元素含有权域weight。算法9.4
   int sw[N+1]; // 累计权值数组
   if(ST.length==0) // ST是空表
     T=NULL; // 次优查找树T为空
   else // ST不空
   { FindSW(sw,ST); // 按照有序表ST中各数据元素的weight域求累计权值表sw
     SecondOptimal(T,ST.elem,sw,1,ST.length);
     // 由有序表ST[1..ST.length]及其累计权值表sw(其中sw[0]==0)递归构造次优查找树T
   }
 }

 Status Search_SOSTree(SOSTree &T,KeyType key)
 { // 在次优查找树T中查找主关键字等于key的元素。找到则返回OK，T指向该元素；否则返回FALSE
   while(T) // T非空
     if(T->data.key==key) // 树T根结点关键字域的值等于key
       return OK; // 找到，返回OK
     else if(T->data.key>key) // 树T根结点关键字域的值大于key
       T=T->lchild; // T指向T的左子树，继续查找
     else // 树T根结点关键字域的值小于key
       T=T->rchild; // T指向T的右子树，继续查找
   return FALSE; // 次优查找树T中不存在待查元素
 }

 void main()
 {
   SSTable st;
   SOSTree t;
   Status i;
   KeyType s;
   Creat_OrdFromFile(st,"f8-3.txt"); // 由数据文件产生非降序静态查找表st
   printf("       ");
   Traverse(st,Visit); // 顺序输出非降序静态查找表st
   CreateSOSTree(t,st); // 由有序表st构造次优查找树t
   printf("\n请输入待查找的字符：");
   InputKey(s); // 由键盘输入关键字s，在func8-3.cpp中
   i=Search_SOSTree(t,s); // 在次优查找树t中查找主关键字等于s的元素
   if(i) // 找到，返回OK，t指向该元素
     printf("%c的权值是%d\n",s,t->data.weight);
   else // 未找到，返回FALSE
     printf("表中不存在此字符\n");
   DestroyBiTree(t); // 查找完毕，销毁次优查找树t
 }
