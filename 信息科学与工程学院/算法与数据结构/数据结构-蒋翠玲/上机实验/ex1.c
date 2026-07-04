#include <stdio.h>
#include <stdlib.h>

typedef int ELemType;

// 创建一个单链表
typedef struct Node
{
    ELemType data;
    struct Node *next;
} Node, *LinkList;

// 初始化单链表
void InitList(LinkList *L)
{
    *L = (LinkList)malloc(sizeof(Node));
    (*L)->next = NULL;
}

// 头插法创建单链表
void CreateFromHead(LinkList *L, int n[], int len)
{
    Node *s;
    while (--len >= 0)
    {
        s = (LinkList)malloc(sizeof(Node));
        s->data = n[len];
        s->next = (*L)->next;
        (*L)->next = s;
    }
}

// 尾插法创建单链表
void CreateFromTail(LinkList *L, int n[], int len)
{
    Node *s, *r;
    r = (Node *)L;
    for (int i = 0; i < len; i++)
    {
        s = (LinkList)malloc(sizeof(Node));
        s->data = n[len];
        r->next = s;
        r = s;
    }
    r->next = NULL;
}

// 打印单链表
void PrintList(LinkList L)
{
    Node *p = L->next;
    while (p)
    {
        printf("%d -> ", p->data);
        p = p->next;
    }
    printf("NULL\n");
}

int main()
{
    LinkList L;
    InitList(&L);
    int n[] = {1, 4, 2, 8, 5, 7};
    printf("CreateFromHead: \n");
    CreateFromHead(&L, n, sizeof(n) / sizeof(n[0]));
    PrintList(L);
    printf("CreateFromTail: \n");
    CreateFromTail(&L, n, sizeof(n) / sizeof(n[0]));
    PrintList(L);
    return 0;
}