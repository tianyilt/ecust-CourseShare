// 【问题描述】
// 商品货架可以看成一个栈，栈顶商品的生产日期最早，栈底商品的生产日期
// 最近。上货时，需要倒货架，以保证生产日期较近的商品在较下的位置。
// 【基本要求】
// 针对一种特定商品，实现上述管理过程。
// 【实现提示】
// 用栈模拟货架和周转空间。
#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;
typedef struct Node
{
    ElemType data;
    struct Node *next;
} Node;

typedef struct
{
    Node *top;
    int size;
} *LinkStack;

void InitStack(LinkStack S) // 初始化
{
    S->top = NULL;
    S->size = 0;
}

void Push(LinkStack S, ElemType x) // 进栈
{
    Node *temp = (Node *)malloc(sizeof(Node));
    temp->data = x;
    temp->next = S->top;
    S->top = temp;
}

ElemType GetTop(LinkStack S) // 取栈顶
{
    if (S->top)
        return S->top->data;
    else
        return -1;
}

void Pop(LinkStack S) // 出栈
{
    if (S->top)
    {
        Node *temp = S->top;
        S->top = S->top->next;
        free(temp);
    }
}

bool IsEmpty(LinkStack S) // 判空
{
    if (S->top)
        return false;
    else
        return true;
}

void PrintStack(LinkStack S)
{
    Node *temp;
    temp = S->top;
    printf("货架从顶至底的商品生产日期依次为: ");
    while (temp)
    {
        printf("% 3d|", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main()
{
    LinkStack S = (LinkStack)malloc(sizeof(LinkStack));
    InitStack(S);
    // Node->data 表示日期
    int initial[] = {4, 3, 3, 3, 2, 2, 1, 1, 1, 1};
    int len = sizeof(initial) / sizeof(initial[0]);
    for (int i = 0; i < len; i++)
    {
        Push(S, initial[i]);
    }
    PrintStack(S);
    LinkStack temp = (LinkStack)malloc(sizeof(LinkStack)); // 周转货架
    InitStack(temp);
    printf("请输入新货物的生产日期以及商品个数: ");
    int x, y;
    scanf("%d %d", &x, &y);
    // 先把货架上的商品取下来放到周转货架上
    while (!IsEmpty(S))
    {
        Push(temp, GetTop(S));
        Pop(S);
    }
    // 将新货物放到货架上
    for (int i = 0; i < y; i++)
    {
        Push(S, x);
    }
    // 再把周转货架上的商品放回货架上
    while (!IsEmpty(temp))
    {
        Push(S, GetTop(temp));
        Pop(temp);
    }
    PrintStack(S);
}