#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode
{ // 树的结点
    int data;
    struct TreeNode *lchild; // 指向左孩子节点
    struct TreeNode *rchild; // 指向右孩子节点
} BiNode, *BiTree;

// 先序建立二叉树
BiTree CreateTree()
{
    int data;
    scanf("%d", &data);
    BiTree root;

    if (data <= 0)
    {
        return NULL;
    }
    else
    {
        root = (BiTree)malloc(sizeof(BiNode));
        root->data = data;
        root->lchild = CreateTree();
        root->rchild = CreateTree();
    }
    return root;
}

// 先序遍历
void PreOrderTraverse(BiTree root)
{
    if (root)
    {
        printf("%d ", root->data);
        PreOrderTraverse(root->lchild);
        PreOrderTraverse(root->rchild);
    }
}
// 中序遍历
void InOrderTraverse(BiTree root)
{
    if (root)
    {
        InOrderTraverse(root->lchild);
        printf("%d ", root->data);
        InOrderTraverse(root->rchild);
    }
}
// 后序遍历
void PostOrderTraverse(BiTree root)
{
    if (root)
    {
        PostOrderTraverse(root->lchild);
        PostOrderTraverse(root->rchild);
        printf("%d ", root->data);
    }
}

int main()
{
    // 测试数据：1 2 4 0 0 0 3 5 0 0 6 0 0
    BiTree root = NULL;
    root = CreateTree(); // 创建树
    printf("\n先序递归遍历：");
    PreOrderTraverse(root);
    printf("\n中序递归遍历：");
    InOrderTraverse(root);
    printf("\n后序递归遍历：");
    PostOrderTraverse(root);
    return 0;
}