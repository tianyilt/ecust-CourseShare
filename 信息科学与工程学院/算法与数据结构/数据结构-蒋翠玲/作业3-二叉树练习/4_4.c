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

// 交换二叉树的左右子树
void swap(BiTree T)
{
    if (T != NULL)
    {
        BiTNode *tmp = T->lchild;
        T->lchild = T->rchild;
        T->rchild = tmp;
        swap(T->lchild);
        swap(T->rchild);
    }
}

int main()
{
    BiTree T;
    printf("Create BiTree: (end with -1)\n");
    CreateBiTree(&T);
    printf("PreOrderTraverse before swap: ");
    PreOrderTraverse(T);
    printf("\n");
    swap(T);
    printf("PreOrderTraverse after swap: ");
    PreOrderTraverse(T);
}