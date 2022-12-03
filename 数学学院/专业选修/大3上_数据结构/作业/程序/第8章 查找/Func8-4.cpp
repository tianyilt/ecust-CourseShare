 // func8-4.cpp 包括算法9.5(a)和bo6-2.cpp，algo8-4.cpp和algo8-5.cpp调用
 #include"bo6-2.cpp" // 包括InitBiTree()，DestroyBiTree()和InOrderTraverse()函数
 #define InitDSTable InitBiTree // 构造二叉排序树和平衡二叉树与初始化二叉树的操作同
 #define DestroyDSTable DestroyBiTree // 销毁二叉排序树和平衡二叉树与销毁二叉树的操作同
 #define TraverseDSTable InOrderTraverse
 // 按关键字顺序遍历二叉排序树和平衡二叉树与中序遍历二叉树的操作同

 BiTree SearchBST(BiTree T,KeyType key)
 { // 在根指针T所指二叉排序树或平衡二叉树中递归地查找某关键字等于key的数据元素，
   // 若查找成功，则返回指向该数据元素结点的指针，否则返回空指针。算法9.5(a)
   if(!T||EQ(key,T->data.key)) // 树T空或待查找的关键字等于T所指结点的关键字
     return T; // 查找结束，返回指针T
   else if LT(key,T->data.key) // 待查找的关键字小于T所指结点的关键字
     return SearchBST(T->lchild,key); // 在左子树中继续递归查找
   else // 待查找的关键字大于T所指结点的关键字
     return SearchBST(T->rchild,key); // 在右子树中继续递归查找
 }
