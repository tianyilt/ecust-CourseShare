#include <stdio.h>
#include <stdlib.h>
typedef struct link
{
    int val;
    struct link *next;
} Node, *linklist;

linklist createList(int len, int n[])
{
    linklist L;
    Node *r, *s;
    L = (Node *)malloc(sizeof(Node));
    L->next = NULL;
    r = L;
    for (int i = 0; i < len; i++)
    {
        s = (Node *)malloc(sizeof(Node));
        s->val = n[i];
        r->next = s;
        r = s;
    }
    r->next = NULL;
    return L;
}

void printlist(linklist L)
{
    Node *p;
    p = L->next;
    while (p != NULL)
    {
        printf("%-4d", p->val);
        p = p->next;
    }
    printf("\n");
}

void ReverseList(linklist L)
{
    Node *f, *l; // 创建两个工作指针
    f = L->next;
    L->next = NULL;
    while (f != NULL)
    {
        l = f->next;
        f->next = L->next;
        L->next = f;
        f = l;
    }
}

int main()
{
    int a[] = {1, 4, 2, 8, 5, 7};
    linklist L1 = createList(sizeof(a) / sizeof(a[0]), a);

    printf("===================================\n");
    printf("L1: ");
    printlist(L1);

    ReverseList(L1);

    printf("After reverse: ");
    printlist(L1);
    printf("===================================\n");
}