 // bo9-1.cpp 顺序表插入排序的函数(3个)，包括算法10.1和算法10.2
 void InsertSort(SqList &L)
 { // 对顺序表L作直接插入排序。算法10.1
   int i,j;
   for(i=2;i<=L.length;++i) // 从第2个记录到最后一个记录
     if LT(L.r[i].key,L.r[i-1].key) // 当前记录<前一个记录
     { // 将L.r[i]插入[1..i-1]的有序子表中
       L.r[0]=L.r[i]; // 将当前记录复制为哨兵(存入[0]中)
       for(j=i-1;LT(L.r[0].key,L.r[j].key);--j) // 有序子表从后到前，若哨兵小于记录
         L.r[j+1]=L.r[j]; // 记录后移1个单元
       L.r[j+1]=L.r[0]; // 将哨兵(当前记录)插入到正确位置
     }
 }

 void BInsertSort(SqList &L)
 { // 对顺序表L作折半插入排序。修改算法10.2
   int i,j,m,low,high;
   for(i=2;i<=L.length;++i) // 从第2个记录到最后一个记录
     if LT(L.r[i].key,L.r[i-1].key) // 当前记录<前一个记录，加此句
     { // 将L.r[i]插入[1..i-1]的有序子表中
       L.r[0]=L.r[i]; // 将L.r[i]暂存到L.r[0]
       low=1; // 插入区间的低端
       high=i-1; // 插入区间的高端
       while(low<=high) // 在r[low..high]中折半查找有序插入的位置
       { m=(low+high)/2; // 折半(中点位置m)
         if LT(L.r[0].key,L.r[m].key) // 关键字小于中点关键字
           high=m-1; // 插入点在低半区
         else // 关键字大于等于中点关键字
           low=m+1; // 插入点在高半区
       } // low>high，退出while循环，[high+1]是插入位置
       for(j=i-1;j>=high+1;--j) // 有序子表从后到前
         L.r[j+1]=L.r[j]; // 记录后移
       L.r[high+1]=L.r[0]; // 插入到[high+1]
     }
 }

 void P2_InsertSort(SqList &L,int flag)
 { // 2-路插入排序(flag=0)和改进的2-路插入排序(flag=1，当L.r[1]是待排序记录中关键字
   // 最小或最大的记录时，仍有优越性)
   int i,j,first,final,mid=0;
   RedType *d;
   d=(RedType*)malloc(L.length*sizeof(RedType)); // 生成L.length个记录的临时空间
   d[0]=L.r[1]; // 设L的第1个记录为d中排好序的记录(在位置[0])
   first=final=0; // first、final分别指示d中排好序的记录的第1个和最后1个记录的位置
   for(i=2;i<=L.length;++i) // 依次将L的第2个～最后1个记录插入d中
   { if(flag) // 改进的2-路插入排序，每次插入前都求mid
     { if(first>final)
         j=L.length; // j是调整系数
       else
         j=0;
       mid=(first+final+j)/2%L.length; // d的中间记录的位置
     }
     if(L.r[i].key<d[mid].key) // 待插记录将插在d的前半部分中(flag=0时，mid=0)
     { j=first; // j指向d的第1个记录
       first=(first-1+L.length)%L.length; // first前移
       while(L.r[i].key>d[j].key) // 待插记录大于j所指记录
       { d[(j-1+L.length)%L.length]=d[j]; // j所指记录前移
         j=(j+1)%L.length; // j指向下1个记录
       }
       d[(j-1+L.length)%L.length]=L.r[i]; // 移动结束，待插记录插在[j]前
     }
     else // 待插记录将插在后半部分中
     { j=final++; // j指向当前的最后1个记录，final指向插入后的最后1个记录
       while(L.r[i].key<d[j].key) // 待插记录小于j所指记录
       { d[(j+1)%L.length]=d[j]; // j所指记录后移，flag=0时不必求余
         j=(j-1+L.length)%L.length; // j指向上1个记录，flag=0时不必求余
       }
       d[(j+1)%L.length]=L.r[i];
       // 待插记录不小于j所指记录，插在j后，flag=0时不必求余
     }
   }
   for(i=1;i<=L.length;i++) // 把在d中排好序的记录依次赋给L.r
     L.r[i]=d[(first+i-1)%L.length]; // 线性关系
   free(d); // 释放d所指的存储空间
 }
