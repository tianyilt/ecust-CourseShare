 // bo9-2.cpp 快速排序的函数，包括算法10.7、10.8
 void QSort(SqList &L,int low,int high)
 { // 对顺序表L中的子序列L.r[low..high]作快速排序。算法10.7
   int pivotloc;
   if(low<high) // 子序列长度大于1
   { pivotloc=Partition(L,low,high);
     // 将L.r[low..high]按关键字一分为二，pivotloc是枢轴位置
     QSort(L,low,pivotloc-1); // 对关键字小于枢轴关键字的低子表递归快速排序
     QSort(L,pivotloc+1,high); // 对关键字大于枢轴关键字的高子表递归快速排序
   }
 }

 void QuickSort(SqList &L)
 { // 对顺序表L作快速排序。算法10.8
   QSort(L,1,L.length); // 对整个顺序表L作快速排序
 }
