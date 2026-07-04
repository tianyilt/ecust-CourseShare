#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 30

typedef struct TreeNode
{ // 树的结点
    int data;
    struct TreeNode *lchild; // 指向左孩子节点
    struct TreeNode *rchild; // 指向右孩子节点
} BiNode, *BiTree;

// 创建二叉搜索树
BiTree CreateBST(int data[], int len)
{
    BiTree root = NULL;
    int i;
    for (i = 0; i < len; i++)
    {
        // 二叉搜索树的插入操作
        BiNode *s = (BiNode *)malloc(sizeof(BiNode));
        s->data = data[i];
        s->lchild = NULL;
        s->rchild = NULL;
        if (!root)
            root = s;
        else
        {
            BiTree p = root;
            while (p)
            {
                if (s->data < p->data)
                {
                    if (!p->lchild)
                    {
                        p->lchild = s;
                        break;
                    }
                    else
                        p = p->lchild;
                }
                else
                {
                    if (!p->rchild)
                    {
                        p->rchild = s;
                        break;
                    }
                    else
                        p = p->rchild;
                }
            }
        }
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
    // 测试数据： 5 4 2 8 7 1 6 9 3 -1
    // 读入无序的序列
    int data[MAXSIZE];
    printf("请输入无序序列(-1收尾)：");
    int i = 0;
    do
        scanf("%d", &data[i]);
    while (data[i++] != -1);

    // 创建二叉排序树
    BiTree root = NULL;
    root = CreateBST(data, --i); // 创建为二叉排序树

    // 打印遍历结果
    printf("\n先序递归遍历：");
    PreOrderTraverse(root);
    printf("\n中序递归遍历：");
    InOrderTraverse(root);
    printf("\n后序递归遍历：");
    PostOrderTraverse(root);
    return 0;
}