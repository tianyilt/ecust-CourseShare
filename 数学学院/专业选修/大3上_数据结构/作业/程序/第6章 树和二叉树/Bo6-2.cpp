 // bo6-2.cpp 二叉链表的4个基本操作，包括算法6.1，func8-4.cpp等调用
 #define ClearBiTree DestroyBiTree // 清空二叉树和销毁二叉树的操作一样
 void InitBiTree(BiTree &T)
 { // 操作结果：构造空二叉树T
   T=NULL;
 }

 void DestroyBiTree(BiTree &T)
 { // 初始条件：二叉树T存在。操作结果：销毁二叉树T
   if(T) // 非空树
   { DestroyBiTree(T->lchild); // 递归销毁左子树，如无左子树，则不执行任何操作
     DestroyBiTree(T->rchild); // 递归销毁右子树，如无右子树，则不执行任何操作
     free(T); // 释放根结点
     T=NULL; // 空指针赋0
   }
 }

 void PreOrderTraverse(BiTree T,void(*Visit)(TElemType))
 { // 初始条件：二叉树T存在，Visit是对结点操作的应用函数。修改算法6.1
   // 操作结果：先序递归遍历T，对每个结点调用函数Visit一次且仅一次
   if(T) // T不空
   { Visit(T->data); // 先访问根结点
     PreOrderTraverse(T->lchild,Visit); // 再先序遍历左子树
     PreOrderTraverse(T->rchild,Visit); // 最后先序遍历右子树
   }
 }

 void InOrderTraverse(BiTree T,void(*Visit)(TElemType))
 { // 初始条件：二叉树T存在，Visit是对结点操作的应用函数
   // 操作结果：中序递归遍历T，对每个结点调用函数Visit一次且仅一次
   if(T)
   { InOrderTraverse(T->lchild,Visit); // 先中序遍历左子树
     Visit(T->data); // 再访问根结点
     InOrderTraverse(T->rchild,Visit); // 最后中序遍历右子树
   }
 }
