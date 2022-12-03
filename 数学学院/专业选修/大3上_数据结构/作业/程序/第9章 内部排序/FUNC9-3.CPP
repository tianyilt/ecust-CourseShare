 // func9-3.cpp 算法10.6(a)
 int Partition(SqList &L,int low,int high)
 { // 交换顺序表L中子表L.r[low..high]的记录，使枢轴记录到位，
   // 并返回其所在位置，此时在它之前(后)的记录均不大(小)于它。算法10.6(a)
   RedType t;
   KeyType pivotkey; // 枢轴关键字
   pivotkey=L.r[low].key; // 用子表的第1个记录作初始枢轴记录
   while(low<high) // 未分类的区间大于0
   { // 从表的两端交替地向中间扫描
     while(low<high&&L.r[high].key>=pivotkey) // 高端记录的关键字大于枢轴关键字
       --high; // 高端向低移，继续比较
     t=L.r[low]; // 将比枢轴关键字小的记录交换到低端，枢轴到高端
     L.r[low]=L.r[high];
     L.r[high]=t;
     while(low<high&&L.r[low].key<=pivotkey) // 低端记录的关键字小于枢轴关键字
       ++low; // 低端向高移，继续比较
     t=L.r[low]; // 将比枢轴关键字大的记录交换到高端，枢轴到低端
     L.r[low]=L.r[high];
     L.r[high]=t;
   }
   return low; // 返回枢轴所在位置
 }
