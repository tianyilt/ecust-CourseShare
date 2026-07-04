#include<bits/stdc++.h>
using namespace std;
#define MAX_VERTEX_NUM 10 /*最多顶点个数*/
#define _INFINITY 9999     /*最多顶点个数*/

typedef enum
{
    DG,
    DN,
    UDG,
    UDN
} GraphKind; /*图的种类DN有向图，DN有向网，UDG无向图，UDN无向网*/
typedef string VertexData;

typedef struct ArcNode
{
    int weight;
} ArcNode;

typedef struct
{
    VertexData vexs[MAX_VERTEX_NUM];              /*顶点向量，一维数组*/
    ArcNode arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; /*邻接矩阵*/
    int vexnum, arcnum;                           /*图的顶点数和弧数*/
    GraphKind kind;
} AdjMatrix;

int LocateVertex(AdjMatrix *G, VertexData v)
{
    int j = 0, k;
    for (k = 0; k < G->vexnum; k++)
        if (G->vexs[k] == v)
        {
            j = k;
            break;
        }
    return j;
}

int CreatDN(AdjMatrix *G)
{
    int i, j, k, weight;
    VertexData v1, v2;
    printf("请输入图的顶点数和弧数: ");
    cin >> G->vexnum >> G->arcnum;
    cin.ignore();
    for (i = 0; i < G->vexnum; i++)
        for (int j = 0; j < G->vexnum; j++)
            G->arcs[i][j].weight = _INFINITY;
    printf("顶点初始化完毕\n");
    for (i = 0; i < G->vexnum; i++)
    {
        printf("请输入第%d个顶点对应的名称: ", i + 1);
        cin >> G->vexs[i];
        cin.ignore();
    }
    for (k = 0; k < G->arcnum; k++)
    {
        printf("请输入第%d个弧对应的两个顶点和权值: ", k + 1);
        cin >> v1 >> v2 >> weight;
        cin.ignore();
        i = LocateVertex(G, v1);
        j = LocateVertex(G, v2);
        G->arcs[i][j].weight = weight; /*建立弧*/
        G->arcs[j][i].weight = weight;
    }
    return 1;
}

void PrintAdjMatrix(AdjMatrix *G)
{
    printf("       ");
    for (int i = 0; i < G->vexnum; i++)
    {
        cout << setw(8) << G->vexs[i];
    }
    printf("\n");
    for (int i = 0; i < G->vexnum; i++)
    {
        cout << setw(8) << G->vexs[i];
        for (int j = 0; j < G->vexnum; j++)
        {
            if (G->arcs[i][j].weight != _INFINITY)
                printf("%7d ", G->arcs[i][j].weight);
            else
                printf("      ∞ ");
        }
        printf("\n");
    }
}

int main()
{
    // {"教学楼", "学生宿舍", "图书馆", "活动中心", "操场", "一食堂", "信息楼"};
    /* 
        教学楼 学生宿舍 10
        学生宿舍 图书馆 8
        教学楼 一食堂 5
        一食堂 活动中心 2
        一食堂 操场 3
        学生宿舍 信息楼 2
        信息楼 图书馆 2
     */
    AdjMatrix G;
    CreatDN(&G);
    PrintAdjMatrix(&G);
}