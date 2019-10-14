 // bo6-4.cpp 构造线索二叉树的11个基本操作，包括算法6.5～6.7
 void CreateBiThrTree(BiThrTree &T)
 { // 按先序输入线索二叉树中结点的值，构造线索二叉树T。0(整型)/空格(字符型)表示空结点
   TElemType ch;
   scanf(form,&ch); // 输入结点的值
   if(ch==Nil) // 结点的值为空
     T=NULL;
   else // 结点的值不为空
   { T=(BiThrTree)malloc(sizeof(BiThrNode)); // 生成根结点(先序)
     if(!T)
       exit(OVERFLOW);
     T->data=ch; // 将值赋给T所指结点
     CreateBiThrTree(T->lchild); // 递归构造左子树
     if(T->lchild) // 有左孩子
       T->LTag=Link; // 给左标志赋值(指针)
     CreateBiThrTree(T->rchild); // 递归构造右子树
     if(T->rchild) // 有右孩子
       T->RTag=Link; // 给右标志赋值(指针)
   }
 }

 BiThrTree pre; // 全局变量，始终指向刚刚访问过的结点
 void InThreading(BiThrTree p)
 { // 通过中序遍历进行中序线索化，线索化之后pre指向最后一个结点。算法6.7
   if(p) // 线索二叉树不空
   { InThreading(p->lchild); // 递归左子树线索化
     if(!p->lchild) // 没有左孩子
     { p->LTag=Thread; // 左标志为线索(前驱)
       p->lchild=pre; // 左孩子指针指向前驱
     }
     if(!pre->rchild) // 前驱没有右孩子
     { pre->RTag=Thread; // 前驱的右标志为线索(后继)
       pre->rchild=p; // 前驱右孩子指针指向其后继(当前结点p)
     }
     pre=p; // 保持pre指向p的前驱
     InThreading(p->rchild); // 递归右子树线索化
   }
 }

 void InOrderThreading(BiThrTree &Thrt,BiThrTree T)
 { // 中序遍历二叉树T，并将其中序线索化，Thrt指向头结点。算法6.6
   if(!(Thrt=(BiThrTree)malloc(sizeof(BiThrNode)))) // 生成头结点不成功
     exit(OVERFLOW);
   Thrt->LTag=Link; // 建头结点，左标志为指针
   Thrt->RTag=Thread; // 右标志为线索
   Thrt->rchild=Thrt; // 右孩子指针回指
   if(!T) // 若二叉树T空，则左孩子指针回指
     Thrt->lchild=Thrt;
   else // 二叉树T非空
   { Thrt->lchild=T; // 头结点的左孩子指针指向根结点
     pre=Thrt; // pre(前驱)的初值指向头结点
     InThreading(T); // 中序遍历进行中序线索化，pre指向中序遍历的最后一个结点
     pre->rchild=Thrt; // 最后一个结点的右孩子指针指向头结点
     pre->RTag=Thread; // 最后一个结点的右标志为线索
     Thrt->rchild=pre; // 头结点的右孩子指针指向中序遍历的最后一个结点
   }
 }

 void InOrderTraverse_Thr(BiThrTree T,void(*Visit)(TElemType))
 { // 中序遍历线索二叉树T(头结点)的非递归算法。算法6.5
   BiThrTree p;
   p=T->lchild; // p指向根结点
   while(p!=T)
   { // 空树或遍历结束时，p==T
     while(p->LTag==Link) // 由根结点一直找到二叉树的最左结点
       p=p->lchild; // p指向其左孩子
     Visit(p->data); // 访问此结点
     while(p->RTag==Thread&&p->rchild!=T)
     { // p->rchild是线索(后继)，且不是遍历的最后一个结点
       p=p->rchild; // p指向其后继
       Visit(p->data); // 访问后继结点
     }
     // 若p->rchild不是线索(是右孩子)，p指向右孩子，返回循环，找这棵子树中序遍历的第1个结点
     p=p->rchild;
   }
 }

 void PreThreading(BiThrTree p)
 { // PreOrderThreading()调用的递归函数
   if(!pre->rchild) // p的前驱没有右孩子
   { pre->RTag=Thread; // pre的右孩子指针为线索
     pre->rchild=p; // p前驱的后继指向p
   }
   if(!p->lchild) // p没有左孩子
   { p->LTag=Thread; // p的左孩子指针为线索
     p->lchild=pre; // p的左孩子指针指向前驱
   }
   pre=p; // 移动前驱
   if(p->LTag==Link) // p有左孩子
     PreThreading(p->lchild); // 对p的左孩子递归调用preThreading()
   if(p->RTag==Link) // p有右孩子
     PreThreading(p->rchild); // 对p的右孩子递归调用preThreading()
 }

 void PreOrderThreading(BiThrTree &Thrt,BiThrTree T)
 { // 先序线索化二叉树T，头结点的右孩子指针指向先序遍历的最后1个结点
   if(!(Thrt=(BiThrTree)malloc(sizeof(BiThrNode)))) // 生成头结点
     exit(OVERFLOW);
   Thrt->LTag=Link; // 头结点的左孩子指针为孩子
   Thrt->RTag=Thread; // 头结点的右孩子指针为线索
   Thrt->rchild=Thrt; // 头结点的右孩子指针指向自身
   if(!T) // 空树
     Thrt->lchild=Thrt; // 头结点的左孩子指针也指向自身
   else // 非空树
   { Thrt->lchild=T; // 头结点的左孩子指针指向根结点
     pre=Thrt; // 前驱为头结点
     PreThreading(T); // 从头结点开始先序递归线索化
     pre->RTag=Thread; // 最后一个结点的右孩子指针为线索
     pre->rchild=Thrt; // 最后一个结点的后继指向头结点
     Thrt->rchild=pre; // 头结点的后继指向最后一个结点
   }
 }

 void PreOrderTraverse_Thr(BiThrTree T,void(*Visit)(TElemType))
 { // 先序遍历线索二叉树T(头结点)的非递归算法
   BiThrTree p=T->lchild; // p指向根结点
   while(p!=T) // p未指向头结点(遍历的最后1个结点的后继指向头结点)
   { Visit(p->data); // 访问根结点
     if(p->LTag==Link) // p有左孩子
       p=p->lchild; // p指向左孩子(后继)
     else // p无左孩子
       p=p->rchild; // p指向右孩子或后继
   }
 }

 void PostThreading(BiThrTree p)
 { // PostOrderThreading()调用的递归函数
   if(p) // p不空
   { PostThreading(p->lchild); // 对p的左孩子递归调用PostThreading()
     PostThreading(p->rchild); // 对p的右孩子递归调用PostThreading()
     if(!p->lchild) // p没有左孩子
     { p->LTag=Thread; // p的左孩子指针为线索
       p->lchild=pre; // p的左孩子指针指向前驱
     }
     if(!pre->rchild) // p的前驱没有右孩子
     { pre->RTag=Thread; // p前驱的右孩子指针为线索
       pre->rchild=p; // p前驱的后继指向p
     }
     pre=p; // 移动前驱
   }
 }

 void PostOrderThreading(BiThrTree &Thrt,BiThrTree T)
 { // 后序递归线索化二叉树
   if(!(Thrt=(BiThrTree)malloc(sizeof(BiThrNode)))) // 生成头结点
     exit(OVERFLOW);
   Thrt->LTag=Link; // 头结点的左孩子指针为孩子
   Thrt->RTag=Thread; // 头结点的右孩子指针为线索
   if(!T) // 空树
     Thrt->lchild=Thrt->rchild=Thrt; // 头结点的左右孩子指针指向自身
   else // 非空树
   { Thrt->lchild=Thrt->rchild=T; // 头结点的左右孩子指针指向根结点(最后一个结点)
     pre=Thrt; // 前驱为头结点
     PostThreading(T); // 从头结点开始后序递归线索化
     if(pre->RTag!=Link) // 最后一个结点没有右孩子
     { pre->RTag=Thread; // 最后一个结点的右孩子指针为线索
       pre->rchild=Thrt; // 最后一个结点的后继指向头结点
     }
   }
 }

 void DestroyBiTree(BiThrTree &T)
 { // DestroyBiThrTree调用的递归函数，T指向根结点
   if(T) // 非空树
   { if(T->LTag==0) // 有左孩子
       DestroyBiTree(T->lchild); // 销毁左子树
     if(T->RTag==0) // 有右孩子
       DestroyBiTree(T->rchild); // 销毁右子树
     free(T); // 释放根结点
     T=NULL; // 空指针赋0
   }
 }

 void DestroyBiThrTree(BiThrTree &Thrt)
 { // 初始条件：线索二叉树Thrt存在。操作结果：销毁线索二叉树Thrt
   if(Thrt) // 头结点存在
   { if(Thrt->lchild) // 根结点存在
       DestroyBiTree(Thrt->lchild); // 递归销毁头结点lchild所指二叉树
     free(Thrt); // 释放头结点
     Thrt=NULL; // 线索二叉树Thrt指针赋0
   }
 }
