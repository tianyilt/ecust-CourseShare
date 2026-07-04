#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VERTEX_NUM 20
#define STRING_LENGTH 20
#define INFINITY 99999

const int _VexNum = 8;
const int _ArcNum = 10;

const char locations[MAX_VERTEX_NUM][STRING_LENGTH] = {"教学楼", "学生宿舍", "图书馆", "活动中心", "操场", "一食堂", "信息楼", "校医院"};
const char arc1[MAX_VERTEX_NUM][STRING_LENGTH] = {"教学楼", "学生宿舍", "教学楼", "一食堂", "一食堂", "一食堂", "学生宿舍", "信息楼", "活动中心", "校医院"};
const char arc2[MAX_VERTEX_NUM][STRING_LENGTH] = {"学生宿舍", "一食堂", "图书馆", "图书馆", "活动中心", "信息楼", "校医院", "校医院", "校医院", "操场"};
const int arcWeight[MAX_VERTEX_NUM] = {10, 8, 5, 2, 3, 2, 6, 9, 7, 4};

typedef enum
{
    DG,
    DN,
    UDG,
    UDN
} GraphKind;

typedef struct ArcNode
{
    int adj; // 两顶点之间的路径长度
} ArcNode;

typedef struct
{
    // 节点数组
    char vertex[MAX_VERTEX_NUM][STRING_LENGTH];
    // i和j节点间的路径长度
    ArcNode arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
    // 节点数量
    int vexnum;
    // 边数量
    int arcnum;
    // 图的种类
    GraphKind kind;
} AdjMatrix;

int LocateVertex(AdjMatrix *G, char v[]) // 确定某个顶点在图内vertex的下标
{
    int j = -1, k;
    for (k = 0; k < G->vexnum; k++)
    {
        if (strcmp(G->vertex[k], v) == 0)
        {
            j = k;
            break;
        }
    }
    return j;
}

int Create(AdjMatrix *G) // 创建一个带权有向图
{
    int i = 0, j, k, weight;
    char v1[STRING_LENGTH], v2[STRING_LENGTH];
    printf("请输入图的顶点和边的个数: ");
    scanf("%d %d", &G->vexnum, &G->arcnum); // 输入图的顶点和个数
    fflush(stdin);
    for (i = 0; i < G->vexnum; i++)
    {
        for (j = 0; j < G->vexnum; j++)
        {
            G->arcs[i][j].adj = INFINITY; // 初始化邻接矩阵
        }
    }
    printf("逐行输入节点的名称:\n");
    for (i = 0; i < G->vexnum; i++)
    {
        scanf("%s", G->vertex[i]);
        fflush(stdin);
        // 输入图的顶点，按顺序确定顶点在图中的位置（就是这一步i=0的时候给我存进vertex[1]里面去了）
    }
    printf("请输入两个节点名和对应的权值:\n");
    for (k = 0; k < G->arcnum; k++)
    {
        scanf("%s", v1);
        scanf("%s", v2);
        scanf("%d", &weight);
        // 输入一条弧的两个顶点及权值
        i = LocateVertex(G, v1);
        j = LocateVertex(G, v2);
        G->arcs[i][j].adj = weight;
        G->arcs[j][i].adj = weight; // 建立弧
        fflush(stdin);
    }
    G->kind = DN;
    return 1;
}

int CreateFromData(AdjMatrix *G) // 创建一个带权有向图
{
    int i = 0, j, k, weight;
    char v1[STRING_LENGTH], v2[STRING_LENGTH];
    G->vexnum = _VexNum;
    G->arcnum = _ArcNum;
    for (i = 0; i < G->vexnum; i++)
    {
        for (j = 0; j < G->vexnum; j++)
        {
            G->arcs[i][j].adj = INFINITY; // 初始化邻接矩阵
        }
    }
    for (i = 0; i < G->vexnum; i++)
    {
        strcpy(G->vertex[i], locations[i]);
    }
    for (k = 0; k < G->arcnum; k++)
    {
        strcpy(v1, arc1[k]);
        strcpy(v2, arc2[k]);
        weight = arcWeight[k];
        // 输入一条弧的两个顶点及权值
        i = LocateVertex(G, v1);
        j = LocateVertex(G, v2);
        // 无向图, 两个方向权重相同
        G->arcs[i][j].adj = weight;
        G->arcs[j][i].adj = weight;
    }
    G->kind = UDG;
    return 1;
}

void Print(AdjMatrix *G)
{
    int i, j;
    printf("          ");
    for (i = 0; i < G->vexnum; i++)
    {
        printf("%-10s", G->vertex[i]);
    }
    printf("\n");
    for (i = 0; i < G->vexnum; i++)
    {
        printf("%-10s", G->vertex[i]);
        for (j = 0; j < G->vexnum; j++)
        {
            if (G->arcs[i][j].adj != INFINITY)
                printf("%-10d", G->arcs[i][j].adj);
            else
                printf("∞         ");
        }
        printf("\n");
    }
}

void process1(AdjMatrix *G, int visited[], int v)
{
    int w;
    for (w = 0; w < G->vexnum; w++)
    {
        if (G->arcs[v][w].adj > 0 && G->arcs[v][w].adj != INFINITY && visited[w] == 0)
        {
            printf("->%s", G->vertex[w]);
            visited[w] = 1;
            process1(G, visited, w);
        }
    }
}

void DFS1(AdjMatrix *G, char startVex[])
{
    int v = LocateVertex(G, startVex);
    static int visited[MAX_VERTEX_NUM];
    memset(visited, 0, sizeof(visited));
    visited[v] = 1;
    printf("%s", startVex);
    process1(G, visited, v);
}

void process2(AdjMatrix *G, int visited[], int v, int record[], int count)
{
    int w;
    int flag = 1;
    for (w = 0; w < G->vexnum; w++)
    {
        if (G->arcs[v][w].adj > 0 && G->arcs[v][w].adj != INFINITY && visited[w] == 0)
        {
            flag = 0;
            record[count] = w;
            visited[w] = 1;
            process2(G, visited, w, record, count + 1);
            visited[w] = 0;
        }
    }
    // flag = 1 说明没有任何一条边可以走了, 输出record
    if (flag)
    {
        for (int i = 0; i < count - 1; i++)
        {
            printf("%s->", G->vertex[record[i]]);
        }
        printf("%s\n", G->vertex[v]);
    }
}

void DFS2(AdjMatrix *G, char startVex[])
{
    int v = LocateVertex(G, startVex);
    static int visited[MAX_VERTEX_NUM];
    memset(visited, 0, sizeof(visited));
    int record[MAX_VERTEX_NUM];
    visited[v] = 1;
    record[0] = v;
    process2(G, visited, v, record, 1);
}

void process3(AdjMatrix *G, int visited[], int v, int record[], int count, int required)
{
    int w;
    int flag = 1;
    for (w = 0; w < G->vexnum; w++)
    {
        if (G->arcs[v][w].adj > 0 && G->arcs[v][w].adj != INFINITY && visited[w] == 0)
        {
            flag = 0;
            record[count] = w;
            visited[w] = 1;
            process3(G, visited, w, record, count + 1, required);
            visited[w] = 0;
        }
    }
    // flag = 1 说明没有任何一条边可以走了, 输出record
    if (flag)
    {
        // 检查该路径中是否包含了指定节点
        int flag2 = 0;
        for (int i = 0; i < count; i++)
        {
            if (record[i] == required)
            {
                flag2 = 1;
                break;
            }
        }
        if (flag2 || v == required)
        {
            for (int i = 0; i < count - 1; i++)
            {
                printf("%s->", G->vertex[record[i]]);
            }
            printf("%s\n", G->vertex[v]);
        }
    }
}

void DFS3(AdjMatrix *G, char startVex[], char requiredVex[])
{
    int v = LocateVertex(G, startVex);
    static int visited[MAX_VERTEX_NUM];
    memset(visited, 0, sizeof(visited));
    int record[MAX_VERTEX_NUM];
    visited[v] = 1;
    record[0] = v;
    process3(G, visited, v, record, 1, LocateVertex(G, requiredVex));
}

void process4(AdjMatrix *G, int visited[], int v, int record[], int count, int target, int bestRecord[], int *bestCount, int *minLen)
{
    int w;
    if (v == target)
    {
        // 计算路径长度
        int sum = 0;
        for (int i = 0; i < count - 1; i++)
        {
            sum += G->arcs[record[i]][record[i + 1]].adj;
        }
        sum += G->arcs[record[count - 2]][v].adj;
        // 如果找到了更短的路径, 更新最短路径
        if (sum < *minLen)
        {
            *minLen = sum;
            *bestCount = count;
            for (int i = 0; i < count - 1; i++)
            {
                bestRecord[i] = record[i];
            }
            bestRecord[count - 1] = v;
        }
        return;
    }
    for (w = 0; w < G->vexnum; w++)
    {
        if (G->arcs[v][w].adj > 0 && G->arcs[v][w].adj != INFINITY && visited[w] == 0)
        {
            record[count] = w;
            visited[w] = 1;
            process4(G, visited, w, record, count + 1, target, bestRecord, bestCount, minLen);
            visited[w] = 0;
        }
    }
}

void DFS4(AdjMatrix *G, char startVex[], char targetVex[], int bestRecord[], int *bestCount, int *minLen)
{
    int v = LocateVertex(G, startVex);
    static int visited[MAX_VERTEX_NUM];
    memset(visited, 0, sizeof(visited));
    int record[MAX_VERTEX_NUM];
    visited[v] = 1;
    record[0] = v;
    process4(G, visited, v, record, 1, LocateVertex(G, targetVex), bestRecord, bestCount, minLen);
}

int main()
{
    AdjMatrix G;
    // Create(&G);
    CreateFromData(&G);
    Print(&G);
    printf("================================================\n");

    printf("请输入深度优先遍历的起始节点名: ");
    char startVex[STRING_LENGTH];
    scanf("%s", startVex);
    fflush(stdin);
    while (LocateVertex(&G, startVex) == -1)
    {
        printf("不存在该节点, 请重新输入: ");
        scanf("%s", startVex);
        fflush(stdin);
    }

    // printf("所有符合要求的深度优先遍历结果: \n");
    // DFS2(&G, startVex);
    // putchar('\n');

    // printf("请输入必须途径的节点名: ");
    // char requiredVex[STRING_LENGTH];
    // scanf("%s", requiredVex);
    // fflush(stdin);
    // while (LocateVertex(&G, requiredVex) == -1)
    // {
    //     printf("不存在该节点, 请重新输入: ");
    //     scanf("%s", requiredVex);
    //     fflush(stdin);
    // }

    // printf("所有符合要求的深度优先遍历结果: \n");
    // DFS3(&G, startVex, requiredVex);
    // putchar('\n');

    printf("请输入目的地的节点名: ");
    char targetVex[STRING_LENGTH];
    scanf("%s", targetVex);
    fflush(stdin);
    while (LocateVertex(&G, targetVex) == -1)
    {
        printf("不存在该节点, 请重新输入: ");
        scanf("%s", targetVex);
        fflush(stdin);
    }

    int bestRecord[MAX_VERTEX_NUM];
    int bestCount = 0;
    int minLen = INFINITY;

    DFS4(&G, startVex, targetVex, bestRecord, &bestCount, &minLen);
    printf("出发地和目的地之间最短距离为: %d\n", minLen);
    printf("最短路径为: \n");
    for (int i = 0; i < bestCount - 1; i++)
    {
        printf("%s->", G.vertex[bestRecord[i]]);
    }
    printf("%s\n", G.vertex[bestRecord[bestCount - 1]]);

    return 0;
}