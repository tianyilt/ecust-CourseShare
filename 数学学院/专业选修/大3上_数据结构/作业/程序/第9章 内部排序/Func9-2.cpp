 // func9-2.cpp 包括算法10.18
 void Sort(SqList L,int adr[])
 { // 求得adr[1..L.length]，adr[i]为静态链表L的第i个最小记录的序号
   int i=1,p=L.r[0].next; // p指向第1个记录
   while(p) // 未到链表尾
   { adr[i++]=p; // 将p赋给adr[i]，i+1
     p=L.r[p].next; // p指向下一个记录
   }
 }

 void Rearrange(SqList &L,int adr[])
 { // adr给出静态链表L的有序次序，即L.r[adr[i]]是第i小的记录。
   // 本算法按adr重排L.r，使其有序。算法10.18
   int i,j,k;
   for(i=1;i<L.length;++i) // 从顺序表的第1个记录到倒数第2个记录
     if(adr[i]!=i) // 记录不在正确位置
     { j=i;
       L.r[0]=L.r[i]; // 暂存记录[i]到[0](空出[i]或[j]来)
       while(adr[j]!=i) // 记录不在正确位置
       { // 调整L.r[adr[j]]的记录到位，直到adr[j]=i为止
         k=adr[j];
         L.r[j]=L.r[k]; // 将[j]中应放的记录移来(因[j]空)
         adr[j]=j; // 记录处于正确位置的标志
         j=k; // 新空出的位置赋给j，以便继续循环调整
       }
       L.r[j]=L.r[0]; // 循环调整完毕，将暂存在[0]的记录赋给L.r[j]
       adr[j]=j;
     }
 }
