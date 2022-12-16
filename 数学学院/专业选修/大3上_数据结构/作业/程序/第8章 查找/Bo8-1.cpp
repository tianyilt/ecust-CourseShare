 // bo8-1.cpp 静态查找表(顺序表和有序表)的基本操作(7个)，包括算法9.1和9.2
 void Creat_SeqFromFile(SSTable &ST,char* filename)
 { // 操作结果：由数据文件构造静态顺序查找表ST
   int i;
   FILE *f; // 文件指针类型
   f=fopen(filename,"r"); // 打开数据文件，并以f表示
   fscanf(f,"%d",&ST.length); // 由文件输入数据元素个数
   ST.elem=(ElemType*)calloc(ST.length+1,sizeof(ElemType));
   // 动态生成ST.length+1个数据元素空间(0号单元不用)
   if(!ST.elem) // 生成失败
     exit(OVERFLOW);
   for(i=1;i<=ST.length;i++)
     InputFromFile(f,ST.elem[i]);
     // 由文件依次输入静态顺序查找表ST的数据元素，在func8-1.cpp中
   fclose(f); // 关闭数据文件
 }

 void Ascend(SSTable &ST)
 { // 重建静态查找表为按关键字非降序排序
   int i,j,k;
   for(i=1;i<ST.length;i++)
   { k=i; // k存当前关键字最小值的序号
     ST.elem[0]=ST.elem[i]; // 待比较值存[0]单元
     for(j=i+1;j<=ST.length;j++) // 从元素[i]之后比起
       if LT(ST.elem[j].key,ST.elem[0].key) // 当前元素的关键字小于待比较元素的关键字
       { k=j; // 将当前元素的序号存于k
         ST.elem[0]=ST.elem[j]; // 将当前元素的值存[0]单元
       }
     if(k!=i) // 有比[i]更小的值则交换
     { ST.elem[k]=ST.elem[i];
       ST.elem[i]=ST.elem[0];
     }
   }
 }

 void Creat_OrdFromFile(SSTable &ST,char* filename)
 { // 操作结果：由含n个数据元素的数组r构造按关键字非降序查找表ST
   Creat_SeqFromFile(ST,filename); // 建立无序的查找表ST
   Ascend(ST); // 将无序的查找表ST重建为按关键字非降序查找表
 }

 Status Destroy(SSTable &ST)
 { // 初始条件：静态查找表ST存在。操作结果：销毁表ST
   free(ST.elem); // 释放动态存储空间
   ST.elem=NULL; // 指针域置空
   ST.length=0; // 表长为0
   return OK;
 }

 int Search_Seq(SSTable ST,KeyType key)
 { // 在顺序表ST中顺序查找其主关键字等于key的数据元素。
   // 若找到，则返回该元素在表中的位置，否则返回0。算法9.1
   int i;
   ST.elem[0].key=key; // 哨兵，关键字存[0]单元
   for(i=ST.length;!EQ(ST.elem[i].key,key);--i); // 从后往前找
   return i; // 找不到时，i为0
 }

 int Search_Bin(SSTable ST,KeyType key)
 { // 在有序表ST中折半查找其主关键字等于key的数据元素。
   // 若找到，则返回该元素在表中的位置，否则返回0。算法9.2
   int mid,low=1,high=ST.length; // 置区间初值
   while(low<=high) // 查找范围大于0
   { mid=(low+high)/2; // 中值
     if EQ(key,ST.elem[mid].key) // 中值是待查找元素
       return mid; // 返回其序号
     else if LT(key,ST.elem[mid].key) // 关键字小于中值
       high=mid-1; // 继续在前半区间进行查找
     else
       low=mid+1; // 继续在后半区间进行查找
   }
   return 0; // 顺序表中不存在待查找元素
 }

 void Traverse(SSTable ST,void(*Visit)(ElemType))
 { // 初始条件：静态查找表ST存在，Visit()是对元素操作的应用函数
   // 操作结果：按顺序对ST的每个元素调用函数Visit()1次且仅1次
   int i;
   ElemType *p=++ST.elem; // p指向第1个元素
   for(i=1;i<=ST.length;i++) // 依次对所有元素
     Visit(*p++); // 调用函数Visit()，p指向下一个元素
 }
