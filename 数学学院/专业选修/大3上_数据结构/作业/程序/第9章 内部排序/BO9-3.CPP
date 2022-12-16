 // bo9-3.cpp 选择排序算法，包括算法10.9、10.10和10.11
 int SelectMinKey(SqList L,int i)
 { // 返回在L.r[i..L.length]中key最小的记录的序号
   int j,k=i; // 初始设[i]的关键字为最小，存i于k
   KeyType min=L.r[i].key; // [i]的关键字存于min
   for(j=i+1;j<=L.length;j++) // 依次与其他记录比较
     if(L.r[j].key<min) // 找到更小的关键字
     { k=j; // 分别将更小的赋给k和min
       min=L.r[j].key;
     }
   return k; // 返回序号
 }

 void SelectSort(SqList &L)
 { // 对顺序表L作简单选择排序。算法10.9
   int i,j;
   RedType t;
   for(i=1;i<L.length;++i) // 选择第i小的记录，并交换到位
   { j=SelectMinKey(L,i); // 在L.r[i..L.length]中选择key最小的记录
     if(i!=j)
     { t=L.r[i]; // 与第i个记录交换，使得第i小的存于[i]
       L.r[i]=L.r[j];
       L.r[j]=t;
     }
   }
 }

 void TreeSort(SqList &L)
 { // 树形选择排序
   int i,n;
   RedType *t;
   t=(RedType*)malloc((2*L.length-1)*sizeof(RedType)); // 二叉树采用顺序存储结构
   for(i=1;i<=L.length;i++) // 将L.r赋给叶子结点(从上到下，从左到右)
     t[L.length-2+i]=L.r[i];
   for(i=L.length-2;i>=0;i--) // 由后向前给非叶子结点赋值
     t[i]=t[2*i+1].key<=t[2*i+2].key?t[2*i+1]:t[2*i+2];
     // 非叶子结点的值为其左右孩子中关键字小的
   for(i=0;i<L.length;i++)
   { L.r[i+1]=t[0]; // 将当前最小值赋给L.r[i]
     n=0; // 根结点序号
     do // 沿树根按层找结点t[0]在叶子中的序号n
     { n=t[2*n+1].key==t[n].key?2*n+1:2*n+2;
     }while(n<L.length-1);
     t[n].key=INT_MAX; // 将此叶子结点的关键字赋无穷大
     while(n) // n不是根结点
     { n=(n+1)/2-1; // 序号为n的结点的双亲结点序号
       t[n]=t[2*n+1].key<=t[2*n+2].key?(t[2*n+1]):(t[2*n+2]);
       // 非叶子结点的值为其左右孩子中关键字小的
     }
   }
   free(t); // 释放t所指的存储空间
 }

 void HeapAdjust(HeapType &H,int s,int m)
 { // 已知H.r[s..m]中记录的关键字除H.r[s].key之外均满足大顶堆的定义，本函数
   // 调整H.r[s]的关键字，使H.r[s..m]中记录的关键字均满足大顶堆的定义。算法10.10
   int j;
   H.r[0]=H.r[s]; // 利用H的空闲结点存储待调整记录，修改
   for(j=2*s;j<=m;j*=2) // j指向待调整记录[s]的左孩子，沿key较大的孩子结点向下筛选
   { if(j<m&&LT(H.r[j].key,H.r[j+1].key)) // 左孩子的关键字<右孩子的关键字
       ++j; // j指向[s]的右孩子
     if(!LT(H.r[0].key,H.r[j].key)) // [s]的关键字不小于[j]的关键字，修改
       break; // 不必再调整，跳出for循环
     H.r[s]=H.r[j]; // 否则，[j]为大顶，插入[s]
     s=j; // [s]的位置向下移到[j](原左或右孩子处)
   }
   H.r[s]=H.r[0]; // 将待调整的记录插入[s]，修改
 }

 void HeapSort(HeapType &H)
 { // 对顺序表H进行堆排序。算法10.11
   int i;
   for(i=H.length/2;i>0;--i) // 从最后一个非叶子结点到第1个结点
     HeapAdjust(H,i,H.length); // 调整H.r[i]，使H.r[i..H.length]成为大顶堆
   for(i=H.length;i>1;--i)
   { H.r[0]=H.r[1]; // 将堆顶记录[1]和未完全排序的H.r[1..i]中的最后一个记录[i]交换
     H.r[1]=H.r[i];
     H.r[i]=H.r[0];
     HeapAdjust(H,1,i-1); // 调整H.r[1]，使H.r[1..i-1]重新成为大顶堆
   }
}
