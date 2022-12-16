 // bo8-7.cpp 哈希函数的基本操作，包括算法9.17、9.18
 void InitHashTable(HashTable &H)
 { // 操作结果：构造一个空的哈希表
   int i;
   H.count=0; // 当前元素个数为0
   H.sizeindex=0; // 初始存储容量最小，为hashsize[0]
   m=hashsize[0]; // 哈希表表长，全局变量
   H.elem=(ElemType*)malloc(m*sizeof(ElemType));
   if(!H.elem)
     exit(OVERFLOW); // 存储分配失败
   for(i=0;i<m;i++)
     H.elem[i].key=NULL_KEY; // 未填记录的标志
 }

 void DestroyHashTable(HashTable &H)
 { // 初始条件：哈希表H存在。操作结果：销毁哈希表H
   free(H.elem); // 释放H.elem的存储空间
   H.elem=NULL;
   H.count=0;
   H.sizeindex=0;
 }

 unsigned Hash(KeyType K)
 { // 一个简单的哈希函数(m为表长，全局变量)
   return K%m;
 }

 int d(int i) // 增量序列函数，在以下3行中根据需要选取1行，其余2行作为注释
 { return i; // 线性探测再散列
 //return ((i+1)/2)*((i+1)/2)*(int)pow(-1,i-1); // 二次探测再散列
 //return rand(); // 伪随机探测再散列
 }

 void collision(KeyType K,int &p,int i)
 { p=(Hash(K)+d(i))%m; // 开放定址法处理冲突
 }

 Status SearchHash(HashTable H,KeyType K,int &p,int &c)
 { // 在开放定址哈希表H中查找关键字为K的元素，若查找成功，以p指示待查数据
   // 元素在表中位置，并返回SUCCESS；否则，以p指示插入位置，并返回UNSUCCESS
   // c用以计冲突次数，其初值置零，供建表插入时参考。修改算法9.17
   p=Hash(K); // 求得哈希地址
   while(H.elem[p].key!=NULL_KEY&&!EQ(K,H.elem[p].key))
   { // 该位置中填有记录．并且与待查找的关键字不相等
     c++; // 计冲突次数+1
     if(c<m) // 在H中有可能找到插入地址，修改
       collision(K,p,c); // 求得下一探查地址p
     else // 在H中不可能找到插入地址
       break; // 退出while循环
   }
   if EQ(K,H.elem[p].key) // 查找成功
     return SUCCESS; // p返回待查数据元素位置
   else // 查找不成功
     return UNSUCCESS; // H.elem[p].key==NULL_KEY，p返回的是插入位置
 }

 void RecreateHashTable(HashTable&); // 对函数RecreateHashTable()的声明
 Status InsertHash(HashTable &H,ElemType e)
 { // 查找不成功时插入数据元素e到开放定址哈希表H中，并返回OK；
   // 若冲突次数过大，则重建哈希表，算法9.18
   int p,c=0; // 冲突次数，初始为0
   if(SearchHash(H,e.key,p,c)) // 查找成功
     return DUPLICATE; // H中已有与e有相同关键字的元素，不再插入
   else if(c<hashsize[H.sizeindex]/2) // 未找到，冲突次数也c未达到上限，(c的阀值可调)
   { H.elem[p]=e; // 在H中插入数据元素e
     ++H.count; // H的数据元素个数+1
     return OK; // 插入成功
   }
   else // 未找到，但冲突次数c已达到上限
   { RecreateHashTable(H); // 重建哈希表
     return UNSUCCESS; // 插入不成功，需重新插入
   }
 }

 void RecreateHashTable(HashTable &H)
 { // 重建哈希表H
   int i,count=H.count; // H中原有数据个数
   ElemType *p,*elem=(ElemType*)malloc(count*sizeof(ElemType));
   // 动态生成存放哈希表H原有数据的空间
   p=elem; // p指向elem
   for(i=0;i<m;i++) // 将H原有的第1个数据到最后1个数据，保存到elem中
     if((H.elem+i)->key!=NULL_KEY) // H在该单元有数据
       *p++=*(H.elem+i); // 将数据依次存入elem
   H.count=0; // H的当前数据元素个数为0
   H.sizeindex++; // 增大存储容量为下一个序列数
   m=hashsize[H.sizeindex]; // 新的存储容量
   H.elem=(ElemType*)realloc(H.elem,m*sizeof(ElemType));
   // 以新的存储容量重新生成空哈希表H
   for(i=0;i<m;i++)
     H.elem[i].key=NULL_KEY; // 未填记录的标志(初始化)
   for(p=elem;p<elem+count;p++) // 将原有的数据按照新的表长插入到重建的哈希表中
     InsertHash(H,*p);
   free(elem); // 释放elem的存储空间
 }

 void TraverseHash(HashTable H,void(*Visit)(int,ElemType))
 { // 按哈希地址的顺序遍历哈希表H
   int i;
   printf("哈希地址0～%d\n",m-1);
   for(i=0;i<m;i++) // 对于整个哈希表H
     if(H.elem[i].key!=NULL_KEY) // H在第i个单元有数据
       Visit(i,H.elem[i]); // 访问第i个数据
 }
