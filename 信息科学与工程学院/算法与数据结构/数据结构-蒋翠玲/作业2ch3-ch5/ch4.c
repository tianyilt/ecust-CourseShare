#include <stdio.h>
#include <stdlib.h>

#define Stack_Size 50
#define StackElementType int
#define MAXSIZE 50
#define QueueElementType int

typedef struct
{
    StackElementType elem[Stack_Size];
    int top;
} SeqStack;

void InitStack(SeqStack *S)
{
    S->top = -1;
}

int Push(SeqStack *S, StackElementType x)
{
    if (S->top == Stack_Size - 1)
        return 0;
    S->top++;
    S->elem[S->top] = x;
    return 1;
}

int Pop(SeqStack *S, StackElementType *x)
{
    if (S->top == -1)
        return 0;
    *x = S->elem[S->top];
    S->top--;
    return 1;
}

int GetTop(SeqStack *S, StackElementType *x)
{
    if (S->top == -1)
        return 0;
    *x = S->elem[S->top];
    return 1;
}

typedef struct
{
    QueueElementType elem[MAXSIZE];
    int front, rear;
} SeqQueue;

void InitQueue(SeqQueue *Q)
{
    Q->front = Q->rear = 0;
}

int EnterQueue(SeqQueue *Q, QueueElementType x)
{
    if ((Q->rear + 1) % MAXSIZE == Q->front)
        return 0;
    Q->elem[Q->rear] = x;
    Q->rear = (Q->rear + 1) % MAXSIZE;
    return 1;
}

int DeleteQueue(SeqQueue *Q, QueueElementType *x)
{
    if (Q->front == Q->rear)
        return 0;
    *x = Q->elem[Q->front];
    Q->front = (Q->front + 1) % MAXSIZE;
    return 1;
}

int main()
{
    SeqQueue Q;
    InitQueue(&Q);
    // 读入队列元素
    printf("Enter the queue size: ");
    int n;
    scanf("%d", &n);
    printf("Enter the queue: ");
    for (int i = 0; i < n; i++)
    {
        int temp;
        scanf("%d", &temp);
        EnterQueue(&Q, temp);
    }
    // 打印队列元素
    printf("Before reverse, the queue is: ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", Q.elem[(Q.front + i) % MAXSIZE]);
    }
    printf("\n");
    // 创建一个栈，用于逆序存储队列元素
    SeqStack S;
    InitStack(&S);
    for (int i = 0; i < n; i++)
    {
        int temp;
        DeleteQueue(&Q, &temp);
        Push(&S, temp);
    }
    // 放回队列
    for (int i = 0; i < n; i++)
    {
        int temp;
        Pop(&S, &temp);
        EnterQueue(&Q, temp);
    }
    // 打印逆序后的队列元素
    printf("After reverse, the queue is: ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", Q.elem[(Q.front + i) % MAXSIZE]);
    }
    printf("\n");
    return 0;
    // 时间复杂度分析:
    //      1. 读入n个元素，进入队列，时间复杂度为O(n)
    //      2. 读出n个元素，进入栈，时间复杂度为O(n)
    //      3. 读出n个元素，进入队列，时间复杂度为O(n)
    //      故总时间复杂度为O(3n)
    // 空间复杂度分析:
    //      借用了一个栈，空间复杂度为O(n)
}
