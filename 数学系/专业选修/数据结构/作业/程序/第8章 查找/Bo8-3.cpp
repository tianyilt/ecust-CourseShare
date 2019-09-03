 // bo8-3.cpp 平衡二叉树的基本操作，包括算法9.9～9.12
 void R_Rotate(BSTree &p)
 { // 对以*p为根的二叉排序树作右旋处理，使二叉排序树的重心右移，但不修改平衡因子。
   // 处理之后p指向新的树根结点，即旋转处理之前的左子树的根结点。算法9.9
   BSTree lc;
   lc=p->lchild; // lc指向p的左孩子结点，lc的左子树不变
   p->lchild=lc->rchild; // lc的右子树挂接为p的左子树
   lc->rchild=p; // 原根结点成为lc的右孩子
   p=lc; // p指向原左孩子结点(新的根结点)
 }

 void L_Rotate(BSTree &p)
 { // 对以*p为根的二叉排序树作左旋处理，使二叉排序树的重心左移，但不修改平衡因子。
   // 处理之后p指向新的树根结点，即旋转处理之前的右子树的根结点。算法9.10
   BSTree rc;
   rc=p->rchild; // rc指向p的右孩子结点，rc的右子树不变
   p->rchild=rc->lchild; // rc的左子树挂接为p的右子树
   rc->lchild=p; // 原根结点成为rc的左孩子
   p=rc; // p指向原右孩子结点(新的根结点)
 }

 void LR_Rotate(BSTree &p)
 { // 对以*p为根的平衡二叉树的LR型失衡，直接进行平衡旋转处理，不修改平衡因子
   BSTree lc=p->lchild; // lc指向小值结点
   p->lchild=lc->rchild->rchild; // 中值结点的右子树成为大值结点的左子树
   lc->rchild->rchild=p; // 大值结点成为中值结点的右子树
   p=lc->rchild; // 根指针指向中值结点
   lc->rchild=p->lchild; // 中值结点的左子树成为小值结点的右子树
   p->lchild=lc; // 小值结点成为中值结点的左子树
 }

 void RL_Rotate(BSTree &p)
 { // 对以*p为根的平衡二叉树的RL型失衡，直接进行平衡旋转处理，不修改平衡因子
   BSTree rc=p->rchild; // rc指向大值结点
   p->rchild=rc->lchild->lchild; // 中值结点的左子树成为小值结点的右子树
   rc->lchild->lchild=p; // 小值结点成为中值结点的左子树
   p=rc->lchild; // 根指针指向中值结点
   rc->lchild=p->rchild; // 中值结点的右子树成为大值结点的左子树
   p->rchild=rc; // 大值结点成为中值结点的右子树
 }

 #define LH +1 // 左高。在教科书第236页
 #define EH  0 // 等高
 #define RH -1 // 右高

 void LeftBalance(BSTree &T) // 算法9.12
 { // 初始条件：原本平衡二叉排序树T的左子树比右子树高(T->bf=1)，
   //           又在左子树中插入了结点，并导致左子树更高，破坏了树T的平衡性
   // 操作结果：对不平衡的树T作左平衡旋转处理，使树T的重心右移，
   //           实现新的平衡。本算法结束时，T指向新的平衡二叉树根结点
   BSTree lc,rd;
   lc=T->lchild; // lc指向*T的左孩子结点
   switch(lc->bf) // 检查*T的左子树的平衡度，并作相应平衡处理
   { case LH: // 新结点插入在*T的左孩子的左子树上，导致左子树的平衡因子为左高，
             // 形成LL(╱)型不平衡，要作单右旋处理
             T->bf=lc->bf=EH; // 旋转后，原根结点和左孩子结点(新根结点)的平衡因子都为0
             R_Rotate(T); // 对树T作右旋处理，使树T的重心右移
             break;
     case RH: // 新结点插入在*T的左孩子的右子树上，导致左子树的平衡因子为右高，
             // 形成LR(＜)型不平衡，要作双旋处理
             rd=lc->rchild; // rd指向*T的左孩子的右子树根结点
             switch(rd->bf) // 检查*T的左孩子的右子树的平衡度，修改*T及其左孩子的平衡因子
             { case LH: // 新结点插入在*T的左孩子的右子树的左子树上
                       T->bf=RH; // 旋转后，原根结点的平衡因子为右高
                       lc->bf=EH; // 旋转后，原根结点的左孩子结点平衡因子为等高
                       break;
               case EH: // 新结点插入为*T的左孩子的右孩子(叶子)
                       T->bf=lc->bf=EH; // 旋转后，原根和左孩子结点的平衡因子都为等高
                       break;
               case RH: // 新结点插入在*T的左孩子的右子树的右子树上
                       T->bf=EH; // 旋转后，原根结点的平衡因子为等高
                       lc->bf=LH; // 旋转后，原根结点的左孩子结点平衡因子为左高
             }
             rd->bf=EH; // 旋转后的新根结点(*T的左孩子的右孩子结点)的平衡因子为等高
 #ifndef FLAG // 没定义FLAG，使用2个函数实现双旋处理，同教科书
             L_Rotate(T->lchild);
             // 对*T的左子树作左旋处理，使*T成为LL(╱)型不平衡
             R_Rotate(T); // 对*T作右旋处理
 #else // 定义了FLAG，直接处理LR型不平衡
             LR_Rotate(T); // 对*T直接进行平衡旋转处理
 #endif
   }
 }

 void RightBalance(BSTree &T)
 { // 初始条件：原本平衡二叉排序树T的右子树比左子树高(T->bf=-1)，又在右子树中插入了结点，
   //           并导致右子树更高，破坏了树T的平衡性
   // 操作结果：对不平衡的树T作右平衡旋转处理，使树T的重心左移，实现新的平衡。
   //           本算法结束时，T指向新的平衡二叉树根结点
   BSTree rc,ld;
   rc=T->rchild; // rc指向*T的右孩子结点
   switch(rc->bf) // 检查*T的右子树的平衡度，并作相应平衡处理
   { case RH: // 新结点插入在*T的右孩子的右子树上，导致右子树的平衡因子为右高，
             // 形成RR(╲)型不平衡，要作单左旋处理
             T->bf=rc->bf=EH; // 旋转后，原根结点和右孩子结点(新根结点)的平衡因子都为0
             L_Rotate(T); // 对树T作左旋处理，使树T的重心左移
             break;
     case LH: // 新结点插入在*T的右孩子的左子树上，导致右子树的平衡因子为左高，
             // 形成RL(＞)型不平衡，要作双旋处理
             ld=rc->lchild; // ld指向*T的右孩子的左子树根结点
             switch(ld->bf) // 检查*T的右孩子的左子树的平衡度，修改*T及其右孩子的平衡因子
             { case RH: // 新结点插入在*T的右孩子的左子树的右子树上
                       T->bf=LH; // 旋转后，原根结点的平衡因子为左高
                       rc->bf=EH; // 旋转后，原根结点的右孩子结点平衡因子为等高
                       break;
               case EH: // 新结点插入为*T的右孩子的左孩子(叶子)
                       T->bf=rc->bf=EH; // 旋转后，原根和右孩子结点的平衡因子都为等高
                       break;
               case LH: // 新结点插入在*T的右孩子的左子树的左子树上
                       T->bf=EH; // 旋转后，原根结点的平衡因子为等高
                       rc->bf=RH; // 旋转后，原根结点的右孩子结点的平衡因子为右高
             }
             ld->bf=EH; // 旋转后的新根结点(*T的右孩子的左孩子结点)的平衡因子为等高
 #ifndef FLAG // 没定义FLAG，使用2个函数实现双旋处理
             R_Rotate(T->rchild);
             // 对*T的右子树作右旋处理，使*T成为RR(╲)型不平衡
             L_Rotate(T); // 对*T作左旋处理
 #else // 定义了FLAG，直接处理RL型不平衡
             RL_Rotate(T); // 对*T直接进行平衡旋转处理
 #endif
   }
 }

 Status InsertAVL(BSTree &T,ElemType e,Boolean &taller)
 { // 若在平衡的二叉排序树T中不存在和e有相同关键字的结点，则插入一个数据元素为e的新结点，
   // 并返回TRUE；否则返回FALSE。若因插入而使二叉排序树T失去平衡，则作平衡旋转处理，
   // 布尔变量taller反映在调用InsertAVL()前后，T是否长高。算法9.11
   if(!T) // 树或子树T空
   { // 插入新结点，树“长高”，置taller为TRUE
     T=(BSTree)malloc(sizeof(BSTNode)); // 生成新结点，且T指向其
     T->data=e; // 给新结点赋值
     T->lchild=T->rchild=NULL; // 新结点是叶子结点
     T->bf=EH; // 叶子结点的平衡因子为等高
     taller=TRUE; // 以T为根结点的树长高了(深度由0变为1)，此信息返回给T的双亲结点
   }
   else // 树或子树T不空
   { if EQ(e.key,T->data.key) // T所指结点的关键字和e相同，不再插入
     { // taller=FALSE; // 树T保持原来的形态，没有长高(此句可省)
       return FALSE; // 没有在树T中插入结点的标志
     }
     if LT(e.key,T->data.key) // e的关键字小于*T的关键字
     { if(!InsertAVL(T->lchild,e,taller)) // 继续在*T的左子树中递归调用InsertAVL()
         return FALSE; // 如未插入e，返回没有在树T中插入结点的标志
       if(taller) // 如已将e插入到*T的左子树中且左子树“长高”
         switch(T->bf) // 检查*T的平衡度，并作适当处理
         { case LH: // 原本树T的左子树比右子树高，现在T的左子树又“长高”了
                   LeftBalance(T); // 对树T作左平衡处理，使树T的重心右移
                   taller=FALSE; // 对T作左平衡处理后，树T的深度同插入结点e前，未长高
                   break;
           case EH: // 原本树T的左、右子树等高，现在T的左子树又“长高”了
                   T->bf=LH; // T的平衡因子由0变为1(左高)
                   taller=TRUE; // 树T比插入结点e前“长高”了，此信息返回给T的双亲结点
                   break;
           case RH:T->bf=EH; // 原本树T的右子树比左子树高，现在T的左、右子树等高
                   taller=FALSE; // 树T没有长高，此信息返回给T的双亲结点
         }
     }
     else // e的关键字大于*T的关键字
     { if(!InsertAVL(T->rchild,e,taller)) // 继续在*T的右子树中进行搜索，如未插入
         return FALSE; // 没有在树T中插入结点的标志
       if(taller) // 已插入到T的右子树且右子树“长高”
         switch(T->bf) // 检查T的平衡度
         { case LH:T->bf=EH; // 原本树T的左子树比右子树高，现在T的左、右子树等高
                   taller=FALSE; // 树T没有长高，此信息返回给T的双亲结点
                   break;
           case EH: // 原本树T的左、右子树等高，现在T的右子树又“长高”了
                   T->bf=RH; // T的平衡因子由0变为-1(右高)
                   taller=TRUE; // 树T比插入结点e前“长高”了，此信息返回给T的双亲结点
                   break;
           case RH: // 原本右子树比左子树高，现在T的右子树又“长高”了
                   RightBalance(T); // 对树T作右平衡处理，使树T的重心左移
                   taller=FALSE; // 对T作右平衡处理后，树T的深度同插入结点e前，未长高
         }
     }
   }
   return TRUE;
 }
