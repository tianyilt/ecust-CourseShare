#include <bits/stdc++.h>
using namespace std;

#define N 50
#define M 2 * N - 1

typedef struct
{
    int weight;
    int parent;
    int LChild;
    int RChild;
} HTNode, HuffmanTree[M + 1];

void Select(HuffmanTree ht, int n, int *s1, int *s2)
{
    // 在1~n中选择出两个还没指定parent的最小权值结点, 并返回他们在 ht 中的序号
    int min = 0x7fffffff;
    for (int i = 1; i <= n; i++)
    {
        if (ht[i].parent == 0 && ht[i].weight < min)
        {
            min = ht[i].weight;
            *s1 = i;
        }
    }
    min = 0x7fffffff;
    for (int i = 1; i <= n; i++)
    {
        if (ht[i].parent == 0 && ht[i].weight < min && i != *s1)
        {
            min = ht[i].weight;
            *s2 = i;
        }
    }
}

void CreateHuffmanTree(HuffmanTree ht, int w[], int n)
{
    // 1~n 号单元用于存放 叶子结点
    for (int i = 1; i <= n; i++)
    {
        ht[i].weight = w[i];
        ht[i].parent = ht[i].LChild = ht[i].RChild = 0;
    }

    // n+1~2n-1 号单元用于存放 非叶子结点
    int m = 2 * n - 1;
    for (int i = n + 1; i <= m; i++)
    {
        ht[i].weight = ht[i].parent = ht[i].LChild = ht[i].RChild = 0;
    }

    // 构造哈夫曼树, 创建 n-1 个非叶子结点
    for (int i = n + 1; i <= m; i++)
    {
        int s1, s2;
        Select(ht, i - 1, &s1, &s2); // 在1~i-1中选择出两个还没指定parent的最小权值结点, 并返回他们在 ht 中的序号
        ht[i].weight = ht[s1].weight + ht[s2].weight;
        ht[s1].parent = ht[s2].parent = i;
        ht[i].LChild = s1;
        ht[i].RChild = s2;
    }
}

void PrintHuffmanTree(HuffmanTree ht, int n)
{
    printf("Index\tWeight\tParent\tLChild\tRChild\n");
    for (int i = 1; i <= 2 * n - 1; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\n", i, ht[i].weight, ht[i].parent, ht[i].LChild, ht[i].RChild);
    }
}

int main()
{
    int n;
    printf("Input the number of leaf nodes: ");
    scanf("%d", &n);
    int w[n + 1];
    printf("Input the weight of each node: \n");
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &w[i]);
    }
    HuffmanTree ht;
    CreateHuffmanTree(ht, w, n);
    for (int i = 1; i <= 20; i++)
        printf("=");
    printf("Huffman Tree has been created!\n");
    PrintHuffmanTree(ht, n);
    cout << endl;
}

