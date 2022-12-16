 // bo8-2.cpp 二叉排序树的基本操作(4个)，包括算法9.5(b)、算法9.6～9.8
 Status SearchBST(BiTree &T,KeyType key,BiTree f,BiTree &p) // 算法9.5(b)
 { // 在根指针T所指二叉排序树中递归地查找其关键字等于key的数据元素，若查找成功，
   // 则指针p指向该数据元素结点，并返回TRUE，否则指针p指向查找路径上访问的最后一个结点
   // 并返回FALSE，指针f指向T的双亲，其初始调用值为NULL
   if(!T) // 查找不成功
   { p=f; // p指向查找路径上访问的最后一个结点
     return FALSE;
   }
   else if EQ(key,T->data.key) // 查找成功
   { p=T; // p指向该数据元素结点
     return TRUE;
   }
   else if LT(key,T->data.key) // key小于T所指结点的关键字
     return SearchBST(T->lchild,key,T,p); // 在左子树中继续递归查找
   else // key大于T所指结点的关键字
     return SearchBST(T->rchild,key,T,p); // 在右子树中继续递归查找
 }

 Status InsertBST(BiTree &T,ElemType e)
 { // 若二叉排序树T中没有关键字等于e.key的元素，插入e并返回TRUE；否则返回FALSE。算法9.6
   BiTree p,s;
   if(!SearchBST(T,e.key,NULL,p)) // 查找不成功，p指向查找路径上访问的最后一个叶子结点
   { s=(BiTree)malloc(sizeof(BiTNode)); // 生成新结点
     s->data=e; // 给新结点的数据域赋值
     s->lchild=s->rchild=NULL; // 给新结点的左右孩子域赋初值空
     if(!p) // 树T空
       T=s; // 待插结点*s为新的根结点
     else if LT(e.key,p->data.key) // 树T不空，*s的关键字小于*p的关键字
       p->lchild=s; // 待插结点*s为p所指结点的左孩子
     else // 树T不空，*s的关键字大于*p的关键字
       p->rchild=s; // 待插结点*s为p所指结点右孩子
     return TRUE;
   }
   else
     return FALSE; // 树中已有关键字相同的结点，不再插入
 }

 void Delete(BiTree &p)
 { // 从二叉排序树中删除p所指结点，并重接它的左或右子树。算法9.8
   BiTree s,q=p; // q指向待删除结点(提到if语句之外)
   if(!p->rchild) // p的右子树空则只须重接它的左子树(待删结点是叶子也走此分支)
   { p=p->lchild; // p指向待删除结点的左孩子
     free(q); // 释放待删除结点
   }
   else if(!p->lchild) // p的左子树空，只须重接它的右子树
   { p=p->rchild; // p指向待删除结点的右孩子
     free(q); // 释放待删除结点
   }
   else // p的左右子树均不空
   { s=p->lchild; // s指向待删除结点的左孩子(s由p转左)
     while(s->rchild) // s有右孩子
     { q=s; // q指向s
       s=s->rchild; // s指向s的右孩子
     } // s向右到尽头(s指向待删结点的前驱结点，q指向s的双亲结点)
     p->data=s->data; // 将待删结点前驱的值取代待删结点的值
     if(q!=p) // 情况①，待删结点的左孩子有右子树
       q->rchild=s->lchild; // 重接*q的右子树
     else // 情况②，待删结点的左孩子没有右子树
       q->lchild=s->lchild; // 重接*q的左子树
     free(s); // 释放s所指结点
   }
 }

 Status DeleteBST(BiTree &T,KeyType key)
 { // 若二叉排序树T中存在关键字等于key的数据元素时，则删除
   // 该数据元素结点，并返回TRUE；否则返回FALSE。算法9.7
   if(!T) // 树T空
     return FALSE;
   else // 树T不空
   { if EQ(key,T->data.key) // 关键字等于树T根结点的关键字
       Delete(T); // 删除该结点
     else if LT(key,T->data.key) // 关键字小于T所指结点的关键字
       DeleteBST(T->lchild,key); // 在T的左孩子中递归查找
     else // 关键字大于T所指结点的关键字
       DeleteBST(T->rchild,key); // 在T的右孩子中递归查找
     return TRUE;
   }
 }
