#include <stdio.h>
#include <stdlib.h>

#define ELEMENT_TYPE int

// 二叉树的定义如下(二叉链表)：
typedef struct
{
    int data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

// 先序创建二叉树
void CreateBiTree(BiTree *T)
{
    int x;
    scanf("%d", &x);
    if (x == -1)
        *T = NULL;
    else
    {
        *T = (BiTree)malloc(sizeof(BiTNode));
        (*T)->data = x;
        CreateBiTree(&(*T)->lchild);
        CreateBiTree(&(*T)->rchild);
    }
}

// 二叉树的前序遍历
void PreOrderTraverse(BiTree T)
{
    if (T != NULL)
    {
        printf("%d ", T->data);
        PreOrderTraverse(T->lchild);
        PreOrderTraverse(T->rchild);
    }
}

// 判断二叉树是否为正则二叉树
int isRegular(BiTree T)
{
    if (T == NULL)
        return 1;
    if (T->lchild == NULL && T->rchild == NULL)
        return 1;
    if (T->lchild != NULL && T->rchild != NULL)
        return isRegular(T->lchild) && isRegular(T->rchild);
    return 0;
}

int main()
{
    BiTree T;
    printf("Create BiTree: (end with -1)\n");
    CreateBiTree(&T);
    printf("PreOrderTraverse: ");
    PreOrderTraverse(T);
    printf("\n");
    printf("isRegular: %d\n", isRegular(T));
}