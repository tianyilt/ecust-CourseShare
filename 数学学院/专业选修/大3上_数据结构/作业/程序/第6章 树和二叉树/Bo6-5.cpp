 // bo6-5.cpp 树的二叉链表(孩子-兄弟)存储(存储结构由c6-4.h定义)的基本操作(16个)
 #define ClearTree DestroyTree // 二者操作相同
 void InitTree(CSTree &T)
 { // 操作结果：构造空树T
   T=NULL;
 }

 void DestroyTree(CSTree &T)
 { // 初始条件：树T存在。操作结果：销毁树T
   if(T) // 非空树
   { DestroyTree(T->firstchild); // 递归销毁T的长子为根结点的子树
     DestroyTree(T->nextsibling); // 递归销毁T的下一个兄弟为根结点的子树
     free(T); // 释放根结点
     T=NULL; // 空指针赋0
   }
 }

 typedef CSTree QElemType; // 定义队列元素类型为孩子-兄弟二叉链表的指针类型
 #include"c3-2.h" // 定义LinkQueue类型(链队列)
 #include"bo3-2.cpp" // LinkQueue类型的基本操作
 void CreateTree(CSTree &T)
 { // 构造树T
   char c[20]; // 临时存放孩子结点(设不超过20个)的值
   CSTree p,p1;
   LinkQueue q;
   int i,m;
   InitQueue(q); // 初始化队列q
   printf("请输入根结点(字符型，空格为空)：");
   scanf("%c%*c",&c[0]); // 输入根结点的值
   if(c[0]!=Nil) // 非空树
   { T=(CSTree)malloc(sizeof(CSNode)); // 建立根结点
     T->data=c[0]; // 给根结点赋值
     T->nextsibling=NULL; // 根结点没有下一个兄弟
     EnQueue(q,T); // 入队根结点的指针
     while(!QueueEmpty(q)) // 队不空
     { DeQueue(q,p); // 出队一个结点的指针
       printf("请按长幼顺序输入结点%c的所有孩子：",p->data);
       gets(c); // 将结点的所有孩子作为字符串输入
       m=strlen(c);
       if(m>0) // 有孩子
       { p1=p->firstchild=(CSTree)malloc(sizeof(CSNode)); // 建立长子结点
         p1->data=c[0]; // 给长子结点赋值
         EnQueue(q,p1); // 入队p1结点的指针
         for(i=1;i<m;i++) // 对于除长子之外的其他孩子
         { p1->nextsibling=(CSTree)malloc(sizeof(CSNode)); // 建立下一个兄弟结点
           p1=p1->nextsibling; // p1指向下一个兄弟结点
           p1->data=c[i]; // 给p1所指结点赋值
           EnQueue(q,p1); // 入队p1结点的指针
         }
         p1->nextsibling=NULL; // 最后一个结点没有下一个兄弟
       }
       else // 无孩子
         p->firstchild=NULL; // 长子指针为空
     }
   }
   else
     T=NULL; // 空树
 }

 Status TreeEmpty(CSTree T)
 { // 初始条件：树T存在。操作结果：若T为空树，则返回TURE；否则返回FALSE
   if(T) // T不空
     return FALSE;
   else
     return TRUE;
 }

 int TreeDepth(CSTree T)
 { // 初始条件：树T存在。操作结果：返回T的深度
   CSTree p;
   int depth,max=0;
   if(!T) // 树空
     return 0;
   for(p=T->firstchild;p;p=p->nextsibling) // 对于树T根结点的所有孩子结点(由p指向)
   { // 求子树深度的最大值
     depth=TreeDepth(p); // 递归求孩子结点的深度depth
     if(depth>max) // 最大孩子结点的深度存max
       max=depth;
   }
   return max+1; // 树的深度=子树深度最大值+1
 }

 TElemType Value(CSTree p)
 { // 返回p所指结点的值
   return p->data;
 }

 TElemType Root(CSTree T)
 { // 初始条件：树T存在。操作结果：返回T的根
   if(T)
     return Value(T);
   else
     return Nil;
 }

 CSTree Point(CSTree T,TElemType s)
 { // 返回二叉链表(孩子-兄弟)树T中指向元素值为s的结点的指针。新增
   LinkQueue q;
   QElemType a;
   if(T) // 非空树
   { InitQueue(q); // 初始化队列
     EnQueue(q,T); // 根结点入队
     while(!QueueEmpty(q)) // 队不空
     { DeQueue(q,a); // 出队，队列元素赋给a
       if(a->data==s) // 找到元素值为s的结点
         return a; // 返回指向其的指针
       if(a->firstchild) // 有长子
         EnQueue(q,a->firstchild); // 入队长子
       if(a->nextsibling) // 有下一个兄弟
         EnQueue(q,a->nextsibling); // 入队下一个兄弟
     }
   }
   return NULL;
 }

 Status Assign(CSTree &T,TElemType cur_e,TElemType value)
 { // 初始条件：树T存在，cur_e是树T中结点的值。操作结果：改cur_e为value
   CSTree p;
   if(T) // 非空树
   { p=Point(T,cur_e); // p为cur_e的指针
     if(p) // 找到cur_e
     { p->data=value; // 赋新值
       return OK;
     }
   }
   return ERROR; // 树空或未找到
 }

 TElemType Parent(CSTree T,TElemType cur_e)
 { // 初始条件：树T存在，cur_e是T中某个结点
   // 操作结果：若cur_e是T的非根结点，则返回它的双亲；否则函数值为“空”
   CSTree p,t;
   LinkQueue q;
   InitQueue(q); // 初始化队列q
   if(T) // 树非空
   { if(Value(T)==cur_e) // 根结点值为cur_e
       return Nil;
     EnQueue(q,T); // 根结点入队
     while(!QueueEmpty(q)) // 队列不空
     { DeQueue(q,p); // 出队元素(指针)赋给p
       if(p->firstchild) // p有长子
       { if(p->firstchild->data==cur_e) // 长子为cur_e
           return Value(p); // 返回双亲的值
         t=p; // 双亲指针赋给t
         p=p->firstchild; // p指向长子
         EnQueue(q,p); // 入队长子
         while(p->nextsibling) // 有下一个兄弟
         { p=p->nextsibling; // p指向下一个兄弟
           if(Value(p)==cur_e) // 下一个兄弟为cur_e
             return Value(t); // 返回双亲的值
           EnQueue(q,p); // 入队下一个兄弟
         }
       }
     }
   }
   return Nil; // 树空或未找到cur_e
 }

 TElemType LeftChild(CSTree T,TElemType cur_e)
 { // 初始条件：树T存在，cur_e是T中某个结点
   // 操作结果：若cur_e是T的非叶子结点，则返回它的最左孩子；否则返回“空”
   CSTree f;
   f=Point(T,cur_e); // f指向结点cur_e
   if(f&&f->firstchild) // 找到结点cur_e且结点cur_e有长子
     return f->firstchild->data; // 返回结点cur_e的长子的值
   else
     return Nil; // 返回空
 }

 TElemType RightSibling(CSTree T,TElemType cur_e)
 { // 初始条件：树T存在，cur_e是T中某个结点
   // 操作结果：若cur_e有右兄弟，则返回它的右兄弟；否则返回“空”
   CSTree f;
   f=Point(T,cur_e); // f指向结点cur_e
   if(f&&f->nextsibling) // 找到结点cur_e且结点cur_e有右兄弟
     return f->nextsibling->data; // 返回结点cur_e的右兄弟的值
   else
     return Nil; // 返回空
 }

 Status InsertChild(CSTree &T,CSTree p,int i,CSTree c)
 { // 初始条件：树T存在，p指向T中某个结点，1≤i≤p所指结点的度+1，非空树c与T不相交
   // 操作结果：插入c为T中p结点的第i棵子树。因为p所指结点的地址不会改变，
   //           故p不需要是引用类型
   int j;
   CSTree q;
   if(T) // T不空
   { if(i==1) // 插入c为p的长子
     { c->nextsibling=p->firstchild; // p的原长子现是c的下一个兄弟(c本无兄弟)
       p->firstchild=c; // p的长子指针指向c(c成为p的长子)
     }
     else // c不是p的长子
     { q=p->firstchild; // q指向p的长子结点
       j=2;
       while(q&&j<i) // 找c的插入点，并由q指向
       { q=q->nextsibling; // q指向下一个兄弟结点
         j++; // 计数+1
       }
       if(j==i) // 找到插入位置
       { c->nextsibling=q->nextsibling; // c的下一个兄弟指向p的原第i个孩子
         q->nextsibling=c; // 在p中插入c作为p的第i个孩子
       }
       else // p原有孩子数小于i-1
         return ERROR;
     }
     return OK;
   }
   else // T空
     return ERROR;
 }

 Status DeleteChild(CSTree &T,CSTree p,int i)
 { // 初始条件：树T存在，p指向T中某个结点，1≤i≤p所指结点的度
   // 操作结果：删除T中p所指结点的第i棵子树。
   //           因为p所指结点的地址不会改变，故p不需要是引用类型
   CSTree b,q;
   int j;
   if(T) // T不空
   { if(i==1) // 删除长子
     { // 把长子结点子树从p中分离出来
       b=p->firstchild; // b指向p的长子结点
       p->firstchild=b->nextsibling; // p的原次子现是长子
       b->nextsibling=NULL; // p的长子结点成为待删除子树的根结点，其下一个兄弟指针为空
       DestroyTree(b); // 销毁由b指向的p的长子结点子树
     }
     else // 删除非长子
     { q=p->firstchild; // q指向p的长子结点
       j=2;
       while(q&&j<i) // 找第i棵子树
       { q=q->nextsibling; // q指向下一个兄弟结点
         j++; // 计数+1
       }
       if(j==i) // 找到第i棵子树
       { b=q->nextsibling; // b指向待删除子树
         q->nextsibling=b->nextsibling; // 从树p中删除这棵子树
         b->nextsibling=NULL; // 待删除子树的根结点的下一个兄弟指针为空
         DestroyTree(b); // 销毁由b指向的p的长子结点子树
       }
       else // p原有孩子数小于i
         return ERROR;
     }
     return OK;
   }
   else
     return ERROR;
 }

 void PostOrderTraverse(CSTree T,void(*Visit)(TElemType))
 { // 后根遍历孩子-兄弟二叉链表结构的树T
   CSTree p;
   if(T)
   { if(T->firstchild) // 有长子
     { PostOrderTraverse(T->firstchild,Visit); // 后根遍历长子子树
       p=T->firstchild->nextsibling; // p指向长子的下一个兄弟
       while(p) // 还有下一个兄弟
       { PostOrderTraverse(p,Visit); // 后根遍历下一个兄弟子树
         p=p->nextsibling; // p指向再下一个兄弟
       }
     }
     Visit(Value(T)); // 最后访问根结点
   }
 }

 void LevelOrderTraverse(CSTree T,void(*Visit)(TElemType))
 { // 层序遍历孩子-兄弟二叉链表结构的树T
   CSTree p;
   LinkQueue q;
   InitQueue(q); // 初始化队列q
   if(T) // 树非空
   { Visit(Value(T)); // 先访问根结点
     EnQueue(q,T); // 入队根结点的指针
     while(!QueueEmpty(q)) // 队不空
     { DeQueue(q,p); // 出队一个结点的指针
       if(p->firstchild) // 有长子
       { p=p->firstchild; // p指向长子结点
         Visit(Value(p)); // 访问长子结点
         EnQueue(q,p); // 入队长子结点的指针
         while(p->nextsibling) // 有下一个兄弟
         { p=p->nextsibling; // p指向下一个兄弟结点
           Visit(Value(p)); // 访问下一个兄弟
           EnQueue(q,p); // 入队兄弟结点的指针
         }
       }
     }
   }
   printf("\n");
 }
