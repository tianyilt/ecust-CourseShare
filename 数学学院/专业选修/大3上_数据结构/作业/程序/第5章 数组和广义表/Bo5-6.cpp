 // bo5-6.cpp 广义表的扩展线性链表存储(存储结构由c5-5.h定义)的基本操作(12个)
 #include"func5-3.cpp" // 算法5.8

 void InitGList(GList1 &L)
 { // 创建空的广义表L
   L=(GList1)malloc(sizeof(GLNode1)); // 建表头结点
   L->tag=LIST; // 给表头结点的标志域赋值
   L->hp=L->tp=NULL; // 给表头结点的指针域赋值
 }

 void Create(GList1 &L,SString S)
 { // 由广义表的书写形式串S创建子表L，CreateGList()调用
   SString emp,sub,hsub;
   GList1 p;
   StrAssign(emp,"()"); // 设emp="()"
   if(!(L=(GList1)malloc(sizeof(GLNode1)))) // 建表结点不成功
     exit(OVERFLOW);
   if(!StrCompare(S,emp)) // 创建空表
   { L->tag=LIST; // 依然是表
     L->hp=NULL; // 是空表
   }
   else if(StrLength(S)==1) // 创建单原子广义表
   { L->tag=ATOM; // 给结点的标志域赋值
     L->atom=S[1]; // 给结点的值域赋值
   }
   else // 递归创建子表
   { L->tag=LIST; // 是表
     SubString(sub,S,2,StrLength(S)-2);
     // 脱外层括号(去掉第1个字符(左括号)和最后1个字符(右括号))给串sub
     sever(sub,hsub); // 从sub中分离出表头串hsub(外层逗号之前的)，表尾串赋给sub
     Create(L->hp,hsub); // 创建子表的表头元素
     p=L->hp; // p指向子表的表头元素
     while(!StrEmpty(sub)) // 表尾不空，则重复建n个子表
     { sever(sub,hsub); // 从sub中分离出表头串hsub
       Create(p->tp,hsub); // 依次创建子表
       p=p->tp; // p向后移
     }
   }
   L->tp=NULL; // 尾指针为空
 }

 void CreateGList(GList1 &L,SString S) // 修改算法5.7
 { // 采用扩展线性链表存储结构，由广义表的书写形式串S创建广义表L。L最初为空的广义表
   SString emp,sub,hsub;
   GList1 p;
   StrAssign(emp,"()"); // 设emp="()"
   if(!StrCompare(S,emp)) // S="()"
     InitGList(L); // 创建空表
   else // S不是空串
   { SubString(sub,S,2,StrLength(S)-2);
     // 脱外层括号(去掉第1个字符(左括号)和最后一个字符(右括号))给串sub
     sever(sub,hsub); // 从sub中分离出表头串hsub(外层逗号之前的)，表尾串赋给sub
     Create(L->hp,hsub); // 创建表头元素
     p=L->hp; // p指向第1个元素
     while(!StrEmpty(sub)) // 表尾不空，则继续创建子表
     { sever(sub,hsub); // 从sub中分离出最前面的串给hsub，其余部分赋给sub
       Create(p->tp,hsub); // 依次创建子表
       p=p->tp; // p向后移
     }
     p->tp=NULL; // 最后一个元素的尾指针为空
   }
 }

 void DestroyGList(GList1 &L)
 { // 初始条件：广义表L存在。操作结果：销毁广义表L
   GList1 ph,pt;
   if(L) // L存在
   { // 由ph和pt接替L的两个指针
     if(L->tag) // 是子表
       ph=L->hp;
     else // 是原子
       ph=NULL;
     pt=L->tp;
     DestroyGList(ph); // 递归销毁表ph
     DestroyGList(pt); // 递归销毁表pt
     free(L); // 释放L所指结点
     L=NULL; // 令L为空
   }
 }

 void CopyGList(GList1 &T,GList1 L)
 { // 初始条件：广义表L存在。操作结果：由广义表L复制得到广义表T
   T=NULL;
   if(L) // L存在
   { T=(GList1)malloc(sizeof(GLNode1));
     if(!T)
       exit(OVERFLOW);
     T->tag=L->tag; // 复制枚举变量
     if(L->tag==ATOM) // 复制共用体部分
       T->atom=L->atom; // 复制单原子
     else
       CopyGList(T->hp,L->hp); // 复制子表
     if(L->tp==NULL) // 到表尾
       T->tp=L->tp;
     else
       CopyGList(T->tp,L->tp); // 复制子表
   }
 }

 int GListLength(GList1 L)
 { // 初始条件：广义表L存在。操作结果：求广义表L的长度，即元素个数
   int len=0;
   GList1 p=L->hp; // p指向第1个元素
   while(p)
   { len++;
     p=p->tp;
   };
   return len;
 }

 int GListDepth(GList1 L)
 { // 初始条件：广义表L存在。操作结果：求广义表L的深度
   int max=0,dep;
   GList1 p;
   if(L->tag==LIST&&!L->hp)
     return 1; // 空表深度为1
   else if(L->tag==ATOM)
     return 0; // 单原子表深度为0，只会出现在递归调用中
   else // 求一般表的深度
     for(p=L->hp;p;p=p->tp)
     { dep=GListDepth(p); // 求以p为头指针的子表深度
       if(dep>max)
         max=dep;
     }
   return max+1; // 非空表的深度是各元素的深度的最大值加1
 }

 Status GListEmpty(GList1 L)
 { // 初始条件：广义表L存在。操作结果：判定广义表L是否为空
   if(!L->hp)
     return OK;
   else
     return ERROR;
 }

 GList1 GetHead(GList1 L)
 { // 初始条件：广义表L存在。操作结果：生成广义表L的表头元素，返回指向这个元素的指针
   GList1 h,p;
   if(!L->hp) // 空表无表头
     return NULL;
   p=L->hp->tp; // p指向L的表尾
   L->hp->tp=NULL; // 截去L的表尾部分
   CopyGList(h,L->hp); // 将表头元素复制给h
   L->hp->tp=p; // 恢复L的表尾(保持原L不变)
   return h;
 }

 GList1 GetTail(GList1 L)
 { // 初始条件：广义表L存在。操作结果：将L的表尾生成为广义表，返回指向这个新广义表的指针
   GList1 t;
   InitGList(t); // 创建空的广义表t
   if(L->hp) // L非空
     CopyGList(t->hp,L->hp->tp); // 将L的表尾复制给t的表头
   return t;
 }

 void InsertFirst_GL(GList1 &L,GList1 e)
 { // 初始条件：广义表L存在。操作结果：插入元素e(也可能是子表)作为L的第1个元素(表头)
   GList1 p=L->hp; // p指向广义表L的第1个元素
   L->hp=e; // 广义表L的头指针指向e
   e->tp=p; // e(只是1个元素，其尾指针必为NULL)的尾指针指向L原来的第1个元素
 }

 void DeleteFirst_GL(GList1 &L,GList1 &e)
 { // 初始条件：广义表L存在。操作结果：删除广义表L的第1个元素，并用e返回其指针
   e=L->hp; // e指向L的第1个元素
   if(L->hp) // L非空
   { L->hp=e->tp; // L的头指针指向原第2个元素
     e->tp=NULL; // e的尾指针设为空
   }
 }

 void Traverse_GL(GList1 L,void(*visit)(AtomType))
 { // 利用递归算法遍历广义表L
   if(L) // L存在
   { if(L->tag==ATOM) // L为单原子
       visit(L->atom); // 访问单原子
     else // L为子表
       Traverse_GL(L->hp,visit); // 遍历L->hp子表
     Traverse_GL(L->tp,visit); // 遍历L->tp子表
   }
 }
