#include <bits/stdc++.h>
using namespace std;

typedef struct link
{
    int val;
    int exp;
    struct link *next;
} Node, *linklist;

linklist createList(int len, vector<vector<int>> &n)
{
    linklist L;
    Node *r, *s;
    L = (Node *)malloc(sizeof(Node));
    L->next = NULL;
    r = L;
    for (int i = 0; i < len; i++)
    {
        s = (Node *)malloc(sizeof(Node));
        s->exp = n[i][0];
        s->val = n[i][1];
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
        printf("%c%2dx^%d ", (p->val > 0 ? '+' : '-'), abs(p->val), p->exp);
        p = p->next;
    }
    printf("\n");
}

linklist addList(linklist *L1, linklist *L2)
{
    linklist l1, l2, l3;
    Node *temp, *p;
    l1 = (*L1)->next;
    l2 = (*L2)->next;
    l3 = (linklist)malloc(sizeof(Node));
    p = l3;
    while (l1 != NULL && l2 != NULL)
    {
        if (l1->exp == l2->exp)
        {
            if (l1->val + l2->val == 0)
            {
                l1 = l1->next;
                l2 = l2->next;
                continue;
            }
            else
            {
                temp = (linklist)malloc(sizeof(Node));
                temp->exp = l1->exp;
                temp->val = l1->val + l2->val;
                temp->next = NULL;
                l1 = l1->next;
                l2 = l2->next;
            }
        }
        else if (l1->exp > l2->exp)
        {
            temp = (linklist)malloc(sizeof(Node));
            temp->exp = l1->exp;
            temp->val = l1->val;
            temp->next = NULL;
            l1 = l1->next;
        }
        else
        {
            temp = (linklist)malloc(sizeof(Node));
            temp->exp = l2->exp;
            temp->val = l2->val;
            temp->next = NULL;
            l2 = l2->next;
        }
        p->next = temp;
        p = temp;
    }
    while (l1 != NULL)
    {
        temp = (linklist)malloc(sizeof(Node));
        temp->exp = l1->exp;
        temp->val = l1->val;
        temp->next = NULL;
        l1 = l1->next;
        p->next = temp;
        p = temp;
    }
    while (l2 != NULL)
    {
        temp = (linklist)malloc(sizeof(Node));
        temp->exp = l2->exp;
        temp->val = l2->val;
        temp->next = NULL;
        l2 = l2->next;
        p->next = temp;
        p = temp;
    }
    return l3;
}

int main()
{
    // 规定一元多项式表示方法:
    // 从首元结点向后, 每个节点的exp表示指数, val表示系数, 指数降序排列
    vector<vector<int>> n1 = {{4, 2}, {3, 4}, {2, 3}, {1, 2}, {0, 1}}; // 2x^4 + 3x^3 + 2x^2 + 1
    vector<vector<int>> n2 = {{5, 1}, {4, -2}, {3, 2}, {1, -4}};       // x^5 - 2x^4 + 2x^3 - 4x

    printf("================\n");
    linklist L1 = createList(n1.size(), n1);
    linklist L2 = createList(n2.size(), n2);
    printf("n1:      ");
    printlist(L1);
    printf("n2:      ");
    printlist(L2);

    linklist L3 = addList(&L1, &L2);
    printf("n1 + n2: ");
    printlist(L3);
    printf("================\n");
}