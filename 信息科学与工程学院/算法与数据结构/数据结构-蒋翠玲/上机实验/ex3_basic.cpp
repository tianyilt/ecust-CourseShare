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
    printf("Stack elements:");
    while (temp)
    {
        printf("%d", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main()
{
    // 运用链式栈实现十进制转二进制
    LinkStack S;
    InitStack(S);
    int n;
    printf("The decimal number is: ");
    scanf("%d", &n);
    while (n)
    {
        Push(S, n % 2);
        n /= 2;
    }
    printf("The binary number is: ");
    while (!IsEmpty(S))
    {
        printf("%d", GetTop(S));
        Pop(S);
    }
    printf("\n");
    return 0;
}