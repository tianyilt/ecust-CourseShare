 // bo8-4.cpp B_树的基本操作，包括算法9.13和9.14
 void InitDSTable(BTree &DT)
 { // 操作结果：构造一个空的B_树DT
   DT=NULL;
 }

 void DestroyDSTable(BTree &DT)
 { // 初始条件：B_树DT存在。操作结果：销毁DT
   int i;
   if(DT) // 非空树
   { for(i=0;i<=DT->keynum;i++) // 由第0棵到第keynum棵
       DestroyDSTable(DT->ptr[i]); // 依次递归销毁第i棵子树
     free(DT); // 释放根结点
     DT=NULL; // 空指针赋0
   }
 }

 void TraverseDSTable(BTree DT,void(*Visit)(BTNode,int))
 { // 初始条件：B_树DT存在，Visit是对结点操作的应用函数
   // 操作结果：按关键字的顺序对DT的每个结点调用函数Visit()一次且至多一次
   int i;
   if(DT) // 非空树
     for(i=0;i<=DT->keynum;i++) // 对于DT的所有关键字和子树
     { if(i>0) // 有关键字
         Visit(*DT,i); // 访问DT的第i个关键字及记录指针
       if(DT->ptr[i]) // DT有第i棵子树
         TraverseDSTable(DT->ptr[i],Visit);
         // 对DT的第i棵子树，递归调用TraverseDSTable()
     }
 }

 int Search(BTNode* p,KeyType K)
 { // 采用折半查找法在p->key[1..keynum]中查找i，使得p->key[i]≤K＜p->key[i+1]
   int mid,low=1,high=p->keynum; // 置区间初值
   if LT(K,p->key[low]) // 关键字太小，p->key[1..keynum]中不存在K
     return 0; // 返回0
   while(low<high) // 当查找范围大于1
   { mid=(low+high+1)/2; // 中值(取偏大)
     if EQ(K,p->key[mid]) // 中值是K
       return mid; // 返回其序号
     if LT(K,p->key[mid]) // K小于中值
       high=mid-1; // 继续在前半区间进行查找
     else // K大于中值
       low=mid; // 继续在包括[mid]的后半区间进行查找
   }
   return low; // low=high，查找范围等于1且p->key[1..keynum]中不存在K
 }

 Result SearchBTree(BTree T,KeyType K)
 { // 在m阶B_树T上查找关键字K，返回结果(pt,i,tag)。若查找成功，则特征值
   // tag=1，指针pt所指结点中第i个关键字等于K；否则特征值tag=0，等于K的
   // 关键字应插入在指针Pt所指结点中第i和第i+1个关键字之间。算法9.13
   BTree p=T,q=NULL; // 初始化，p指向待查结点，q指向p的双亲
   Status found=FALSE; // 查找成功标志，初值为未成功
   int i=0;
   Result r; // 查找结果存于此变量，以便返回
   while(p&&!found) // 待查结点*p不为空且未找到K
   { i=Search(p,K); // 在结点*p中查找关键字K
     if(i>0&&p->key[i]==K) // 找到
       found=TRUE; // 置查找成功标志为真
     else // 未找到
     { q=p; // 继续向下找，当前结点成为新的双亲结点
       p=p->ptr[i]; // p指向继续查找的结点
     }
   }
   if(found) // 查找成功
   { r.pt=p; // r.pt指向关键字K所处的结点
     r.tag=1; // 查找成功标志
   }
   else // 查找不成功，返回K的插入位置信息
   { r.pt=q; // r.pt指向关键字K应插入的结点
     r.tag=0; // 查找不成功标志
   }
   r.i=i; // r.i指示r.pt所指结点中关键字K所在(找到)或应在其后插入(未找到)的序号
   return r; // 返回结果(pt,i,tag)
 }

 void split(BTree q,BTree &ap)
 { // 将结点*q分裂成两个结点，前一半保留在*q，后一半移入新生结点*ap
   int i;
   ap=(BTree)malloc(sizeof(BTNode)); // 生成新结点*ap
   ap->ptr[0]=q->ptr[s]; // 结点*q的后一半移入结点*ap
   if(ap->ptr[0]) // ap->ptr[0]不为空
     ap->ptr[0]->parent=ap; // 给ap->ptr[0]的双亲域赋值ap
   for(i=s+1;i<=m;i++) // 对于*q中后一半数据
   { ap->key[i-s]=q->key[i]; // 3个成员均移结点*ap
     ap->recptr[i-s]=q->recptr[i];
     ap->ptr[i-s]=q->ptr[i];
     if(ap->ptr[i-s]) // ap->ptr[i-s]不为空
       ap->ptr[i-s]->parent=ap; // 给ap->ptr[i-s]的双亲域赋值ap
   }
   ap->keynum=m-s; // 新结点*ap的关键字个数
   q->keynum=s-1; // *q的前一半保留，修改*q的关键字个数
 }

 void Insert(BTree q,int i,Record* r,BTree ap)
 { // 将记录地址r和r->key分别赋给q->recptr[i+1]和q->key[i+1]，q->ptr[i+1]指向结点*ap
   int j;
   for(j=q->keynum;j>i;j--) // 由后到前，空出(*q)[i+1]
   { q->key[j+1]=q->key[j]; // 3个成员均向后移
     q->recptr[j+1]=q->recptr[j];
     q->ptr[j+1]=q->ptr[j];
   }
   q->key[i+1]=r->key; // 将r->key赋给q->key[i+1]
   q->recptr[i+1]=r; // 将记录地址r赋给q->recptr[i+1]
   q->ptr[i+1]=ap; // q->ptr[i+1]指向结点*ap(ap是r的右孩子)
   if(ap) // ap不空
     ap->parent=q; // q是ap的双亲所在的结点
   q->keynum++; // 结点*q的关键字数量加1
 }

 void NewRoot(BTree &T,Record* r,BTree ap)
 { // 生成含信息(T,r,ap)的新的根结点*T，原根结点T和ap为其子树指针
   BTree p=(BTree)malloc(sizeof(BTNode)); // 动态生成新根结点
   p->parent=NULL; // 新根结点的双亲为空
   p->keynum=1; // 新根结点有1个关键字
   p->key[1]=r->key; // 这个关键字是记录r的关键字
   p->recptr[1]=r; // 指向记录r
   p->ptr[0]=T; // 原根结点T为新根结点的第1棵子树
   if(T) // 原根结点T不空
     T->parent=p; // 新根结点是原根结点T的双亲
   p->ptr[1]=ap; // 结点*ap为新根结点的第2棵子树
   if(ap) // ap不空
     ap->parent=p; // 新根结点是ap的双亲
   T=p; // T指向新根结点
 }

 void InsertBTree(BTree &T,Record* r,BTree q,int i)
 { // 在m阶B_树T上结点*q的key[i]与key[i+1]之间插入关键字r->k和地址r。若引起
   // 结点过大，则沿双亲链进行必要的结点分裂调整，使T仍是m阶B_树。修改算法9.14
   BTree ap=NULL; // 空结点
   Status finished=FALSE; // 插入完成标志，初始为未完成
   while(q&&!finished) // q不空且未完成插入
   { Insert(q,i,r,ap); // 将r->key和记录地址r分别赋给q->key[i+1]和q->recptr[i+1]，
                       // q->ptr[i+1]指向结点*ap
     if(q->keynum<m) // 关键字未超出结点的容量
       finished=TRUE; // 插入完成
     else // 关键字超出了结点的容量，分裂结点*q
     { r=q->recptr[s]; // 分裂点的记录地址赋给r
       split(q,ap); // 将q->key[s+1..m]，q->recptr[s+1..m]和q->ptr[s..m]移入结点*ap
       // 结点*q中仅保留q->key[1..s-1]，q->recptr[1..s-1]和q->ptr[0..s-1]
       q=q->parent; // 当前结点为被分裂结点的双亲结点
       if(q) // 被分裂结点的双亲结点存在
         i=Search(q,r->key); // 在被分裂结点的双亲结点*q中查找r->key的插入位置
     }
   }
   if(!finished) // T是空树(参数q初值为NULL)或根结点已分裂为结点*q和*ap
     NewRoot(T,r,ap); // 生成含信息(T,r,ap)的新的根结点*T，原T和ap为子树指针
 }
