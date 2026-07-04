#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTEX_NUM 10 /*最多顶点个数*/
#define INFINITY 9999     /*最多顶点个数*/

typedef enum
{
    DG,
    DN,
    UDG,
    UDN
} GraphKind; /*图的种类DN有向图，DN有向网，UDG无向图，UDN无向网*/
typedef char VertexData;

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
    return (j);
}

int CreatDN(AdjMatrix *G)
{
    int i, j, k, weight;
    VertexData v1, v2;
    printf("请输入图的顶点数和弧数: ");
    scanf("%d,%d", &G->arcnum, &G->vexnum); /*输入图的顶点数和弧数*/
    fflush(stdin);
    for (i = 0; i < G->vexnum; i++)
        for (int j = 0; j < G->vexnum; j++)
            G->arcs[i][j].weight = INFINITY;
    for (i = 0; i < G->vexnum; i++)
    {
        printf("请输入第%d个顶点对应的字母: ", i + 1);
        scanf("%c", &G->vexs[i]); /*输入图的顶点*/
        fflush(stdin);
    }
    for (k = 0; k < G->arcnum; k++)
    {
        printf("请输入第%d个弧对应的两个顶点和权值: ", k + 1);
        scanf("%c,%c,%d", &v1, &v2, &weight);
        fflush(stdin);
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
        printf("%c    ", G->vexs[i]);
    }
    printf("\n");
    for (int i = 0; i < G->vexnum; i++)
    {
        printf("%c   ", G->vexs[i]);
        for (int j = 0; j < G->vexnum; j++)
        {
            if (G->arcs[i][j].weight != INFINITY)
                printf("%4d ", G->arcs[i][j].weight);
            else
                printf("   ∞ ");
        }
        printf("\n");
    }
}

int main()
{
    AdjMatrix G;
    CreatDN(&G);
    PrintAdjMatrix(&G);
}