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

void DealList(linklist L, int mink, int maxk)
{
    Node *p = L->next, *q = L;
    while (p != NULL && p->val <= mink)
    {
        q = p;
        p = p->next;
    }
    while (p != NULL && p->val < maxk)
    {
        Node *temp = p;
        p = p->next;
        free(temp);
    }
    q->next = p;
}

int main()
{
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    linklist L1 = createList(sizeof(a) / sizeof(a[0]), a);

    printf("===================================\n");
    printf("L1: ");
    printlist(L1);

    printf("Input mink & maxk: ");
    int mink, maxk;
    scanf("%d%d", &mink, &maxk);

    DealList(L1, mink, maxk);

    printf("After delet: ");
    printlist(L1);
    printf("===================================\n");
}