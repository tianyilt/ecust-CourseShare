#include <stdio.h>
#include <stdlib.h>
#define MaxSize 30

typedef struct TreeNode
{ // 树的结点
    int data;
    struct TreeNode *lchild; // 指向左孩子节点
    struct TreeNode *rchild; // 指向右孩子节点
} BiNode, *BiTree;

// 队列结构体
typedef struct queue
{
    struct TreeNode *numQueue[MaxSize];
    int front;
    int rear;
} Queue;
Queue queue; // 声明全局变量
// 初始化队列
void initQueue()
{
    queue.front = 0;
    queue.rear = 0;
}
// 入队
void Push(BiTree root)
{
    queue.numQueue[++queue.rear] = root;
}
// 出队
BiTree Pop()
{
    return queue.numQueue[++queue.front];
}
// 判断队列是否为空
int empty()
{
    return queue.rear == queue.front;
}

// 先序建立二叉树
BiTree CreateTree()
{
    int data;
    scanf("%d", &data); // 根节点数据
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

// 层次遍历:非递归实现
void LevelOrderTraverseNonRec(BiTree root)
{
    BiTree p;
    Push(root);
    while (!empty())
    {                           // empty()判断队列是否为空
        p = Pop();              // 出队
        printf("%d ", p->data); // 输出队首结点
        if (p->lchild)
        { // 把Pop掉的结点的左子结点加入队列
            Push(p->lchild);
        }
        if (p->rchild)
        { // 把Pop掉的结点的右子结点加入队列
            Push(p->rchild);
        }
    }
}
// 二叉树的最大深度
int maxDepth(BiTree root)
{
    if (root)
    {
        int maxLeft = maxDepth(root->lchild);
        int maxRight = maxDepth(root->rchild);
        if (maxLeft > maxRight)
        {
            return maxLeft + 1;
        }
        else
        {
            return maxRight + 1;
        }
    }
    return 0;
}
// 二叉树高度
int BiTreeHeight(BiTree root)
{
    if (root)
    {
        int leftHeight = BiTreeHeight(root->lchild);
        int rightHeight = BiTreeHeight(root->rchild);
        return (leftHeight > rightHeight) ? (leftHeight + 1) : (rightHeight + 1);
    }
    return 0;
}
// 叶子节点
int LeafNodeNum(BiTree root)
{
    if (root == NULL)
    {
        return 0;
    }
    if (root->lchild == NULL && root->rchild == NULL)
    {
        return 1;
    }
    else
    {
        return LeafNodeNum(root->lchild) + LeafNodeNum(root->rchild);
    }
}
// 求第k层节点个数
int LevelNodeNum(BiTree root, int k)
{
    if (root == NULL || k < 1)
    {
        return 0;
    }
    if (k == 1)
    {
        return 1;
    }
    return LevelNodeNum(root->lchild, k - 1) + LevelNodeNum(root->rchild, k - 1);
}
// 求二叉树总节点个数
int CountNode(BiTree root)
{
    if (root)
    {
        if ((root->lchild == NULL) && (root->rchild == NULL))
        {
            return 1;
        }
        else
        {
            return CountNode(root->lchild) + CountNode(root->rchild) + 1;
        }
    }
    return 0;
}
// 查找元素为 x 的节点
BiTree SearchNode(BiTree root, int x)
{
    if (root)
    {
        if (root->data == x)
        {
            return root;
        }
        else
        {
            BiTree p;
            p = SearchNode(root->lchild, x);
            if (!p)
            {
                p = SearchNode(root->rchild, x);
            }
            return p;
        }
    }
    return NULL;
}
// 测试
int main()
{
    // 测试数据：5 3 2 0 0 0 8 6 0 0 9 0 0
    // BiTree root;
    // CreateTree(&root);
    BiTree root = NULL;
    root = CreateTree(); // 创建树
    printf("先序非递归遍历：");
    PreOrderTraverse(root);
    printf("\n中序非递归遍历：");
    InOrderTraverse(root);
    printf("\n后序非递归遍历：");
    PostOrderTraverse(root);
    printf("\n先序递归遍历：");
    PreOrderTraverse(root); // 先序遍历输出
    printf("\n中序递归遍历：");
    InOrderTraverse(root); // 中序遍历输出
    printf("\n后序递归遍历：");
    PostOrderTraverse(root); // 中序遍历输出
    printf("\n层次非递归遍历：");
    LevelOrderTraverseNonRec(root); // 层次遍历输出
    printf("\n二叉树的深度为：%d", maxDepth(root));
    printf("\n二叉树的高度为：%d", BiTreeHeight(root));
    printf("\n叶子节点为：%d", LeafNodeNum(root));
    printf("\n总节点为：%d", CountNode(root));
    printf("\n第3层节点个数为：%d", LevelNodeNum(root, 3));
    BiTree q;
    q = SearchNode(root, 9);
    if (q)
    {
        printf("\n查找到了 ：%d", q->data);
    }
    else
    {
        printf("\n没有查找到 9 ");
    }

    return 0;
}