#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROW 10                                            // 游戏区行数
#define COL 10                                            // 游戏区列数
#define complex_level 85                                  // 复杂度(0~100), 100最简单, 越低越难, 建议大于70
int DIRECTION[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // 4个方向

struct MyNode
{ // 存储节点坐标的结构体
    int x;
    int y;
    int from; // 来自起点或者终点, 0代表起点, 2代表终点
};
typedef struct MyNode MyNode;

struct MyQueue
{ // 用于存储节点的队列
    MyNode *data[ROW * COL];
    int front;
    int rear;
};
typedef struct MyQueue MyQueue;

void QPush(MyQueue *Q, int x, int y, int from)
{

    MyNode *node = (MyNode *)malloc(sizeof(MyNode));
    node->x = x;
    node->y = y;
    node->from = from;
    Q->data[++Q->rear] = node;
}

int QEmpty(MyQueue *Q)
{
    if (Q->front == Q->rear)
    {
        return 1;
    }
    return 0;
}

MyNode *QPop(MyQueue *Q)
{
    return Q->data[++Q->front];
}

void init(int map[ROW][COL], int check[ROW][COL], int start[2], int end[2])
{
    // 初始化地图，全部置为墙壁
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            map[i][j] = 1;
        }
    }
    // 设置起点和终点, 起点为[[1,ROW/2],[1,COL/2]]中随机取数，终点在[ROW/2, ROW-2]和[COL/2, COL-2]中随机取数
    srand((unsigned)time(NULL));
    int x = rand() % (ROW / 2 - 1) + 1;
    int y = rand() % (COL / 2 - 1) + 1;
    start[0] = x;
    start[1] = y;
    x = rand() % (ROW / 2 - 1) + ROW / 2;
    y = rand() % (COL / 2 - 1) + COL / 2;
    end[0] = x;
    end[1] = y;
    map[x][y] = 2;

    // 初始化check表，全部置为0
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            check[i][j] = 0;
        }
    }

    // 围墙设为已确认
    for (int i = 0; i < ROW; i++)
    {
        check[i][0] = 1;
        check[i][COL + 1] = 1;
    }
    for (int i = 0; i < COL; i++)
    {
        check[0][i] = 1;
        check[ROW + 1][i] = 1;
    }
}

int CanPass(int map[ROW][COL], int check[ROW][COL], MyNode *node)
{
    // 检查当前节点能否变成通道
    int cnt = 0;
    for (int i = 0; i < 4; i++)
    {
        int x = node->x + DIRECTION[i][0];
        int y = node->y + DIRECTION[i][1];
        if (map[x][y] == 1)
        {
            cnt++;
        }
    }
    if (cnt >= 3)
    {
        return 1;
    }
    return 0;
}

void bfs(int map[ROW][COL], int check[ROW][COL], int start[2], int end[2])
{
    // 用队列保存待检查的节点
    MyQueue *Q = (MyQueue *)malloc(sizeof(MyQueue)); // 队列用于维护所有待检查的节点
    Q->front = -1;                                   // 初始化队列
    Q->rear = -1;

    QPush(Q, start[0], start[1], 0);
    // 随机加入end周围4格中任意一个
    int temp = rand() % 4;
    QPush(Q, end[0] + DIRECTION[temp][0], end[1] + DIRECTION[temp][1], 2);
    // 其余3个格子设置为已确认
    for (int i = 0; i < 4; i++)
    {
        if (i != temp)
        {
            check[end[0] + DIRECTION[i][0]][end[1] + DIRECTION[i][1]] = 1;
        }
    }
    check[end[0]][end[1]] = 1;

    while (!QEmpty(Q))
    {
        MyNode *cur = QPop(Q);
        // 检查当前节点能否变成通道
        if (CanPass(map, check, cur))
        {
            map[cur->x][cur->y] = cur->from; // 变成通道
            check[cur->x][cur->y] = 1;       // 确认当前节点
            // 判断当前节点的上下左右4个节点, 若未确认则加入队列
            for (int i = 0; i < 4; i++)
            {
                int nextX = cur->x + DIRECTION[i][0];
                int nextY = cur->y + DIRECTION[i][1];
                // 有概率将未确认的节点加入队列
                if (check[nextX][nextY] == 0 && rand() % 100 < complex_level)
                {
                    check[nextX][nextY] = 2; // 将要确认
                    QPush(Q, nextX, nextY, cur->from);
                }
            }
        }
        else
        {
            check[cur->x][cur->y] = 1; // 确认当前节点
        }
    }
}

int linkStartAndEnd(int map[ROW][COL])
{
    // 寻找一个1, 其周围4格中刚好有一个0和一个2, 将这个1变为0, 找到返回1, 没找到返回0
    for (int i = 1; i < ROW + 1; i++)
    {
        for (int j = 1; j < COL + 1; j++)
        {
            if (map[i][j] == 1)
            {
                int cnt0 = 0; // 0的个数
                int cnt2 = 0; // 2的个数
                int cnt1 = 0; // 1的个数
                for (int k = 0; k < 4; k++)
                {
                    int x = i + DIRECTION[k][0];
                    int y = j + DIRECTION[k][1];
                    if (map[x][y] == 0)
                    {
                        cnt0++;
                    }
                    else if (map[x][y] == 2)
                    {
                        cnt2++;
                    }
                    else if (map[x][y] == 1)
                    {
                        cnt1++;
                    }
                }
                if (cnt0 == 1 && cnt2 == 1 && cnt1 == 2)
                {
                    map[i][j] = 0;
                    return 1;
                }
            }
        }
    }
    return 0;
}

void standarizeMap(int map[ROW][COL], int end[2])
{
    // 将所有的2改为0
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            if (map[i][j] == 2)
            {
                map[i][j] = 0;
            }
        }
    }
    // 将终点改为2
    map[end[0]][end[1]] = 2;
}

int main()
{
    int start[2], end[2]; // 起点和终点的坐标
    int map[ROW][COL];    // 增加一圈围墙, 0代表通道, 1代表墙, 2代表终点
    int check[ROW][COL];  // 0代表尚未确认，1代表已经确认, 2代表将要确认
    do
    {
        init(map, check, start, end); // 初始化
        bfs(map, check, start, end);  // bfs搜索
    } while (!linkStartAndEnd(map));  // 连接起点和终点成功
    standarizeMap(map, end);          // 将所有的2改为0, 将终点改为2
    map[start[0]][start[1]] = 9;      // 起点改为0
    // 打印地图
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            printf("%d ", map[i][j]);
        }
        printf("\n");
    }
    return 0;
}