 // bo8-6.cpp Trie树的基本操作，包括算法9.16
 void InitDSTable(TrieTree &T)
 { // 操作结果：构造一个空的Trie树T
   T=NULL;
 }

 void DestroyDSTable(TrieTree &T)
 { // 初始条件：Trie树T存在。操作结果：销毁T
   int i,j=0; // 已处理的结点数
   if(T) // 非空树
   { for(i=0;j<T->bh.num&&i<LENGTH;i++)
       if(T->kind==BRANCH&&T->bh.ptr[i]) // T是分支结点且第i个结点不空
       { if(T->bh.ptr[i]->kind==BRANCH) // 第i个结点是分支结点
           DestroyDSTable(T->bh.ptr[i]); // 递归销毁第i个结点子树
         else // 第i个结点是叶子结点
           free(T->bh.ptr[i]); // 释放叶子结点
         j++; // 已处理的结点数+1
       }
     free(T); // 释放根结点
     T=NULL; // 空指针赋0
   }
 }

 Record* SearchTrie(TrieTree T,KeyType K)
 { // 在Trie树T中查找关键字等于K的记录。修改算法9.16
   TrieTree p=T;
   int i;
   for(i=0;p&&p->kind==BRANCH&&i<=K.num;p=p->bh.ptr[ord(K.ch[i++])]);
   // 对K的每个字符逐个查找，*p为分支结点，ord()求字符在字母表中序号
   if(p&&p->kind==LEAF&&EQ(p->lf.K.ch,K.ch)) // 查找成功
     return p->lf.infoptr; // 返回关键字等于K的记录的地址
   else // 查找不成功
     return NULL; // 返回空
 }

 void InsertTrie(TrieTree &T,Record* r)
 { // 初始条件：Trie树T存在，r为待插入的数据元素的指针
   // 操作结果：若T中不存在其关键字等于r->key.ch的数据元素，则按关键字顺序插r到T中
   TrieTree p=T,q,ap;
   int i,j,k,n;
   if(!T) // 空树
   { T=(TrieTree)malloc(sizeof(TrieNode)); // 动态生成Trie树结点
     T->kind=BRANCH; // 结点类型为分支
     for(i=0;i<LENGTH;i++) // 指针数组赋初值NULL
       T->bh.ptr[i]=NULL;
     T->bh.num=1; // 分支结点的孩子数赋值1
     p=T->bh.ptr[ord(r->key.ch[0])]=(TrieTree)malloc(sizeof(TrieNode));
     // 在关键字首字符对应的指针处动态生成叶子结点
     p->kind=LEAF; // 结点类型为叶子
     p->lf.K=r->key; // 结点关键字为数据元素的关键字
     p->lf.infoptr=r; // 结点指针指向数据元素的地址
   }
   else // 非空树
   { for(i=0;p&&p->kind==BRANCH&&i<=r->key.num;++i) // 在分支结点中查找插入位置
     { q=p; // q指向p所指结点
       p=p->bh.ptr[ord(r->key.ch[i])]; // p指向第i个关键字所在的结点
     }
     if(!p) // 分支空
     { p=q->bh.ptr[ord(r->key.ch[i-1])]=(TrieTree)malloc(sizeof(TrieNode));
       // 动态生成Trie树结点
       q->bh.num++; // 结点的双亲的孩子数+1
       p->kind=LEAF; // 结点类型为叶子
       p->lf.K=r->key; // 结点关键字为数据元素的关键字
       p->lf.infoptr=r; // 结点指针指向数据元素的地址
     }
     else // p->kind!=BRANCH
     { if(EQ(p->lf.K.ch,r->key.ch)) // T中存在该关键字
         return; // 不插入返回
       else // 有关键字部分相同的叶子
       { for(n=0;r->key.ch[n]==p->lf.K.ch[n];n++); // n为相同的关键字符数
         n=n-i;
         for(k=0;k<=n;k++)
         { ap=q=q->bh.ptr[ord(r->key.ch[i++-1])]=(TrieTree)malloc(sizeof
           (TrieNode)); // 动态生成Trie树结点
           ap->kind=BRANCH; // 结点类型为分支
           for(j=0;j<LENGTH;j++)
             ap->bh.ptr[j]=NULL; // 指针数组赋初值NULL
           ap->bh.num=1; // 分支结点的孩子数赋值1
         }
         ap->bh.num++; // 分支结点的孩子数加1
         ap->bh.ptr[ord(p->lf.K.ch[i-1])]=p; // 将*p接入Trie树中
         q=ap->bh.ptr[ord(r->key.ch[i-1])]=(TrieTree)malloc(sizeof(TrieNode));
         // 动态生成Trie树结点
         q->kind=LEAF; // 结点类型为叶子
         q->lf.K=r->key; // 结点关键字为数据元素的关键字
         q->lf.infoptr=r; // 结点指针指向数据元素的地址
       }
     }
   }
 }

 void TraverseDSTable(TrieTree T,void(*Visit)(Record*))
 { // 初始条件：Trie树T存在，Visit是对记录指针操作的应用函数
   // 操作结果：按关键字的顺序输出关键字及其对应的记录
   TrieTree p;
   int i,n=9; // 输出n个元素后换行
   if(T) // 树T不空
     for(i=0;i<LENGTH;i++) // 对T的所有的孩子
     { p=T->bh.ptr[i]; // p指向T的第i个孩子
       if(p&&p->kind==LEAF) // T的第i个孩子是叶子
       { Visit(p->lf.infoptr); // 访问该结点所指的记录
         count++;
         if(count%n==0)
           printf("\n"); // 输出n个元素后换行
       }
       else if(p&&p->kind==BRANCH) // T的第i个孩子是分支
         TraverseDSTable(p,Visit); // 对T的第i个孩子递归调用TraverseDSTable()
     }
 }
