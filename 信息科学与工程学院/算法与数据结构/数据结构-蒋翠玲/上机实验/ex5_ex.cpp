#include <bits/stdc++.h>
using namespace std;

#define N 50
#define M 2 * N - 1
#define ElementType char
typedef struct
{
    ElementType data;
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

void CreateHuffmanTree(HuffmanTree ht, ElementType data[], int w[], int n)
{
    // 1~n 号单元用于存放 叶子结点
    for (int i = 1; i <= n; i++)
    {
        ht[i].data = data[i];
        ht[i].weight = w[i];
        ht[i].parent = ht[i].LChild = ht[i].RChild = 0;
    }

    // n+1~2n-1 号单元用于存放 非叶子结点
    int m = 2 * n - 1;
    for (int i = n + 1; i <= m; i++)
    {
        ht[i].data = '/';
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
    printf("Index\tdata\tWeight\tParent\tLChild\tRChild\n");
    for (int i = 1; i <= 2 * n - 1; i++)
    {
        printf("%d\t%c\t%d\t%d\t%d\t%d\n", i, ht[i].data, ht[i].weight, ht[i].parent, ht[i].LChild, ht[i].RChild);
    }
}

// 统计词频
void CountFrequency(string str, ElementType data[], int w[], int *n)
{
    map<ElementType, int> m;
    for (int i = 0; i < str.length(); i++)
    {
        m[str[i]]++;
    }
    int i = 0;
    for (auto p : m)
    {
        data[++i] = p.first;
        w[i] = p.second;
    }
    *n = i;
}

void process(HuffmanTree ht, string ans[], int i, string code)
{
    if (i == 0)
    {
        return;
    }
    if (ht[i].LChild == 0 && ht[i].RChild == 0)
    {
        // 到达叶子节点
        ans[i] = code;
        return;
    }
    process(ht, ans, ht[i].LChild, code + '0');
    process(ht, ans, ht[i].RChild, code + '1');
}

// 创建哈夫曼编码
void CreateHuffmanCode(HuffmanTree ht, string ans[], int n)
{
    int root = 2 * n - 1;
    // 迭代法遍历哈夫曼树, 获取每个叶子节点的哈夫曼编码
    process(ht, ans, root, "");
}

int main()
{
    printf("Input a string: ");
    string str;
    getline(cin, str);
    ElementType data[N + 1];
    int w[N + 1];
    int n;
    CountFrequency(str, data, w, &n);
    HuffmanTree ht;
    CreateHuffmanTree(ht, data, w, n);
    PrintHuffmanTree(ht, n);
    string code[N + 1];
    CreateHuffmanCode(ht, code, n);
    for (int i = 1; i <= n; i++)
    {
        printf("%c: %s\n", ht[i].data, code[i].c_str());
    }
    return 0;
}
