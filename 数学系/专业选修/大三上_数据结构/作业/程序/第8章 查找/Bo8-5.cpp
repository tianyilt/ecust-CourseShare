 // bo8-5.cpp 双链键树的基本操作，包括算法9.15
 void InitDSTable(DLTree &DT)
 { // 操作结果：构造一个空的双链键树DT
   DT=NULL;
 }

 void DestroyDSTable(DLTree &DT)
 { // 初始条件：双链键树DT存在。操作结果：销毁DT
   if(DT) // 非空树
   { if(DT->kind==BRANCH) // *DT是分支结点
       DestroyDSTable(DT->first); // 递归销毁孩子子树
     DestroyDSTable(DT->next); // 递归销毁兄弟子树
     free(DT); // 释放根结点
     DT=NULL; // 空指针赋0
   }
 }

 Record* SearchDLTree(DLTree T,KeyType K)
 { // 在双链键树T中查找关键字串等于K的记录，若存在，
   // 则返回指向该记录的指针；否则返回空指针。修改算法9.15
   DLTree p=T; // 初始化
   int i=0;
   if(T) // 树不空
   { while(p&&i<K.num) // *p不空且未到最后一个字符
     { while(p&&p->symbol!=K.ch[i]) // 查找关键字的第i位
         p=p->next; // 顺序在右兄弟结点中查找
       if(p&&i<K.num) // 准备查找下一位
         p=p->first; // p指向孩子结点
       ++i; // 关键字向后移一位
     } // 查找结束
     if(!p) // 查找不成功
       return NULL;
     else // 查找成功
       return p->infoptr; // 返回指向该记录的指针
   }
   else // 树空
     return NULL;
 }

 void InsertDSTable(DLTree &DT,Record* r)
 { // 初始条件：双链键树DT存在，r为待插入的数据元素的指针
   // 操作结果：若DT中不存在其关键字串等于(*r).key.ch的数据元素，则按关键字顺序插r到DT中
   DLTree p=NULL,q,ap;
   int i=0;
   KeyType K=r->key;
   if(!DT&&K.num) // 空树且关键字符串非空
   { DT=ap=(DLTree)malloc(sizeof(DLTNode)); // 动态生成根结点
     for(;i<K.num;i++) // 插入分支结点
     { if(p) // p不空(不是第一次生成结点)
         p->first=ap; // p的孩子指针指向新生成的结点
       ap->next=NULL; // 右兄弟为空
       ap->symbol=K.ch[i]; // 关键字符为当前位关键字
       ap->kind=BRANCH; // 结点种类为分支
       p=ap; // p指向ap
       ap=(DLTree)malloc(sizeof(DLTNode)); // 动态生成孩子结点
     }
     p->first=ap; // 插入叶子结点
     ap->next=NULL; // 叶子结点的右兄弟为空
     ap->symbol=Nil; // 叶子结点的关键字符为空
     ap->kind=LEAF; // 结点种类为叶子
     ap->infoptr=r; // 记录指针指向关键字串所在记录
   }
   else // 非空树
   { p=DT; // 指向根结点
     while(p&&i<K.num) // *p不空且i小于关键字串的长度
     { while(p&&p->symbol<K.ch[i]) // 沿右兄弟结点查找当前关键字符
       { q=p; // q指向当前结点
         p=p->next; // p指向当前结点的右兄弟结点
       }
       if(p&&p->symbol==K.ch[i]) // 找到与K.ch[i]相符的结点
       { q=p; // q指向当前结点
         p=p->first; // p指向将与K.ch[i+1]比较的结点(孩子结点)
         ++i; // 关键字向后移一位
       }
       else // 未找到与K.ch[i]相符的结点，插入关键字
       { ap=(DLTree)malloc(sizeof(DLTNode)); // 动态生成结点
         if(q->first==p)
           q->first=ap; // 在长子的位置插入
         else // q->next==p
           q->next=ap; // 在右兄弟的位置插入
         ap->next=p; // 右兄弟为p
         ap->symbol=K.ch[i]; // 关键字符为当前位关键字
         ap->kind=BRANCH; // 结点种类为分支
         p=ap; // p指向ap
         ap=(DLTree)malloc(sizeof(DLTNode)); // 动态生成结点
         i++; // 关键字向后移一位
         for(;i<K.num;i++) // 插入分支结点
         { p->first=ap; // 在长子的位置插入
           ap->next=NULL; // 右兄弟为空
           ap->symbol=K.ch[i]; // 关键字符为当前位关键字
           ap->kind=BRANCH; // 结点种类为分支
           p=ap; // p指向ap
           ap=(DLTree)malloc(sizeof(DLTNode)); // 动态生成孩子结点
         }
         p->first=ap; // 插入叶子结点
         ap->next=NULL; // 叶子结点的右兄弟为空
         ap->symbol=Nil; // 叶子结点的关键字符为空
         ap->kind=LEAF; // 结点种类为叶子
         ap->infoptr=r; // 记录指针指向关键字串所在记录
       }
     }
   }
 }

 struct SElemType // 定义栈元素类型
 { char ch;
   DLTree p;
 };
 #include"c3-1.h" // 顺序栈
 #include"bo3-1.cpp" // 顺序栈的基本操作
 void TraverseDSTable(DLTree DT,void(*Visit)(Record*))
 { // 初始条件：双链键树DT存在，Visit是对记录操作的应用函数
   // 操作结果：按关键字的顺序输出关键字及其对应的记录
   SqStack s;
   SElemType e;
   DLTree p;
   int i=0,n=9; // 输出n个元素后换行
   if(DT) // 树非空
   { InitStack(s); // 初始化栈
     e.p=DT; // 将根结点的信息赋给e
     e.ch=DT->symbol;
     Push(s,e); // 将e入栈
     p=DT->first; // p指向根结点的长子
     while(p->kind==BRANCH) // p是分支结点
     { e.p=p; // 将结点p的信息赋给e
       e.ch=p->symbol;
       Push(s,e); // 将e入栈
       p=p->first; // p指向p的长子
     }
     e.p=p; // 将结点p的信息赋给e
     e.ch=p->symbol;
     Push(s,e); // 将e入栈
     Visit(p->infoptr); // 访问叶子结点的记录
     i++; // 访问数+1
     while(!StackEmpty(s)) // 栈不空
     { Pop(s,e); // 弹出栈顶元素
       p=e.p; // 栈元素指针赋p
       if(p->next) // p有右兄弟结点
       { p=p->next; // p指向p的右兄弟
         while(p->kind==BRANCH) // p是分支结点
         { e.p=p; // 将结点p的信息赋给e
           e.ch=p->symbol;
           Push(s,e); // 将e入栈
           p=p->first; // p指向p的长子
         }
         e.p=p; // 将结点p的信息赋给e
         e.ch=p->symbol;
         Push(s,e); // 将e入栈
         Visit(p->infoptr); // 访问叶子结点的记录
         i++; // 访问数+1
         if(i%n==0)
           printf("\n"); // 输出n个元素后换行
       }
     }
   }
 }
