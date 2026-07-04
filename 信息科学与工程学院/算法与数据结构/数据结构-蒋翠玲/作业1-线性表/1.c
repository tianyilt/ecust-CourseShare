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

linklist ascendMerge(linklist L1, linklist L2)
{
    Node *p1 = L1->next, *p2 = L2->next;
    linklist L = (Node *)malloc(sizeof(Node));
    Node *r = L;
    while (p1 != NULL && p2 != NULL)
    {
        if (p1->val < p2->val)
        {
            Node *temp = (Node *)malloc(sizeof(Node));
            temp->val = p1->val;
            r->next = temp;
            p1 = p1->next;
        }
        else
        {
            Node *temp = (Node *)malloc(sizeof(Node));
            temp->val = p2->val;
            r->next = temp;
            p2 = p2->next;
        }
        r = r->next;
    }
    r->next = p1 ? p1 : p2;
    return L;
}

linklist descendMerge(linklist L1, linklist L2)
{
    Node *p1 = L1->next, *p2 = L2->next;
    linklist L = (Node *)malloc(sizeof(Node));
    L->next = NULL;
    while (p1 != NULL && p2 != NULL)
    {
        if (p1->val < p2->val)
        {
            Node *temp = (Node *)malloc(sizeof(Node));
            temp->val = p1->val;
            temp->next = L->next;
            L->next = temp;
            p1 = p1->next;
        }
        else
        {
            Node *temp = (Node *)malloc(sizeof(Node));
            temp->val = p2->val;
            temp->next = L->next;
            L->next = temp;
            p2 = p2->next;
        }
    }
    while (p1 != NULL)
    {
        Node *temp = (Node *)malloc(sizeof(Node));
        temp->val = p1->val;
        temp->next = L->next;
        L->next = temp;
        p1 = p1->next;
    }
    while (p2 != NULL)
    {
        Node *temp = (Node *)malloc(sizeof(Node));
        temp->val = p2->val;
        temp->next = L->next;
        L->next = temp;
        p2 = p2->next;
    }
    return L;
}

int main()
{
    int a[] = {1, 2, 4, 8, 9};
    int b[] = {3, 5, 6, 7, 10};
    linklist L1 = createList(sizeof(a) / sizeof(a[0]), a);
    linklist L2 = createList(sizeof(b) / sizeof(b[0]), b);
    
    printf("===================================\n");
    printf("The two lists are:\n");
    printlist(L1);
    printlist(L2);

    printf("\n");

    linklist ascendList = ascendMerge(L1, L2);
    printf("The merged list in ascending order is:\n");
    printlist(ascendList);

    linklist descendList = descendMerge(L1, L2);
    printf("The merged list in descending order is:\n");
    printlist(descendList);
    printf("===================================\n");
}