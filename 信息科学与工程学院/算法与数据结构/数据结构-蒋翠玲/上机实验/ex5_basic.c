#include <stdio.h>
#include <stdlib.h>

#define N 20
#define M 2 * N - 1
typedef struct
{
    int weight;
    int parent;
    int LChild;
    int RChild;
} HTNode, HuffmanTree[M + 1];

void CrtHuffmanTree(HuffmanTree ht, int w[], int n)
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
    for(int i = n + 1; i <= m; i++)
    {
        int s1, s2;
        Select(ht, i - 1, &s1, &s2);
        ht[i].weight = ht[s1].weight + ht[s2].weight;
        ht[s1].parent = ht[s2].parent = i;
        ht[i].LChild = s1; ht[i].RChild = s2;
    }
}
