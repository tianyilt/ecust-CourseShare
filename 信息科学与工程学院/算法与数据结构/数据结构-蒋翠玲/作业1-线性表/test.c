#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;
typedef struct Node
{
    ElemType data;
    struct Node *next;
} Node;

typedef struct LinkStack
{
    Node *top;
    int size;
} *LinkStack;

void InitStack(LinkStack S)
{
    S->top = NULL;
    S->size = 0;
}

void Push(LinkStack S, ElemType x)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = x;
    newNode->next = S->top;
    S->top = newNode;
    S->size++;
}

int main()
{
    LinkStack S;
    InitStack(S);
    Push(S, 1);
    printf("size=%d , top=%d\n", S->size, S->top->data);
}