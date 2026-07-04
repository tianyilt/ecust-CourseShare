#include<stdio.h>
#include<stdlib.h>

typedef struct Node
{
    char data;
    struct Node *next;
}Node;

typedef struct LinkStack
{
    Node *top;
    int size;
}*LinkStack;

void InitStack(LinkStack S)//³õÊ¼»¯
{
    S->top=NULL;
    S->size=0;
}

void Push(LinkStack S,char x)
{
    Node *temp=(Node*)malloc(sizeof(Node));
    temp->data=x;
    temp->next=S->top;
    S->top=temp;
}

void PrintStack(LinkStack S)
{
    Node *temp;
    temp=S->top;
    printf("Stack elements:");
    while(temp)
    {
        printf("%c",temp->data);
        temp=temp->next;
    }
    printf("\n");
}

int main()
{
    LinkStack S;
    InitStack(S);
    Push(S,'c');
    printf("top=%c",S->top->data);
    return 0;
}