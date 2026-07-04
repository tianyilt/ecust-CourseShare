#include <bits/stdc++.h>
using namespace std;

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

void printList(linklist L)
{
    Node *p;
    p = L->next;
    while (p != NULL)
    {
        printf("%2d -> ", p->val);
        p = p->next;
    }
    printf("NULL\n");
}

int searchNodeInList(linklist L, int x)
{
    Node *p;
    int pos = 0;
    p = L->next;
    while (p != NULL)
    {
        if (p->val == x)
        {
            return pos;
        }
        pos++;
        p = p->next;
    }
    return -1;
}

void addNodeToList(linklist L, int pos, int x)
{
    Node *p, *s;
    p = L;
    for (int i = 0; i < pos; i++)
    {
        p = p->next;
    }
    s = (Node *)malloc(sizeof(Node));
    s->val = x;
    s->next = p->next;
    p->next = s;
}

void deleteNodeFromList(linklist L, int pos)
{
    Node *p, *s;
    p = L;
    for (int i = 0; i < pos; i++)
    {
        p = p->next;
    }
    s = p->next;
    p->next = s->next;
    free(s);
}

int main()
{
    int len;
    int n[50];
    printf("Please input the list length: ");
    scanf("%d", &len);
    printf("Please input the list: ");
    for (int i = 0; i < len; i++)
    {
        scanf("%d", &n[i]);
    }
    linklist L = createList(len, n);
    printf("The original list is: ");
    printList(L);
    printf("\n");
    printf("Please input the number to search: ");
    int x;
    scanf("%d", &x);
    int pos = searchNodeInList(L, x);
    if (pos == -1)
    {
        printf("The number %d is not in the list.\n", x);
    }
    else
    {
        printf("The number %d is in the list, the position is %d.\n", x, pos);
    }
    printf("\n");
    printf("Please input the position and value to add a number: ");
    int addPos, addNum;
    scanf("%d%d", &addPos, &addNum);
    addNodeToList(L, addPos, addNum);
    printf("The new list is: ");
    printList(L);
    printf("\n");
    printf("Please input the position to delete a number: ");
    int delPos;
    scanf("%d", &delPos);
    deleteNodeFromList(L, delPos);
    printf("The new list is: ");
    printList(L);
    printf("\n");
    return 0;
}