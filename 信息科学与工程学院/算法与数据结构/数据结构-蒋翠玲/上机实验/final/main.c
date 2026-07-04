#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define ROW 20                                            // 游戏区行数
#define COL 40                                            // 游戏区列数
int DIRECTION[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // 4个方向

#define UP 72    // 方向键：上
#define DOWN 80  // 方向键：下
#define LEFT 75  // 方向键：左
#define RIGHT 77 // 方向键：右

/*声明游戏角色的结构体*/
struct Man
{
    int x; // 角色横坐标
    int y; // 角色纵坐标
    int v; // 角色移动速度
};

/*隐藏光标*/
void HideCursor()
{
    CONSOLE_CURSOR_INFO curInfo; // 定义光标信息的结构体变量
    curInfo.dwSize = 1;          // 光标尺寸,如果没赋值的话,隐藏光标无效
    curInfo.bVisible = FALSE;    // 将光标设置为不可见

    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE); // 获取控制台标准输出设备的句柄

    SetConsoleCursorInfo(handle, &curInfo); // 设置控制台光标信息
}

/*光标移动*/
void CursorJump(int x, int y)
{
    COORD pos; // 定义光标位置的结构体变量
    pos.X = x; // 横坐标设置
    pos.Y = y; // 纵坐标设置

    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE); // 获取控制台标准输出设备的句柄

    SetConsoleCursorPosition(handle, pos); // 设置控制台光标位置
}

/* 创建随机地图 */
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
    // 设置起点和终点, 起点为[[1,ROW/2],[1,COL/2]]中随机取数，终点同理在右下方
    srand((unsigned)time(NULL));
    int x = rand() % (ROW / 5) + 1;
    int y = rand() % (COL / 5) + 1;
    start[0] = x;
    start[1] = y;
    x = -rand() % (5) + ROW - 2;
    y = -rand() % (5) + COL - 2;
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
        check[i][COL - 1] = 1;
    }
    for (int i = 0; i < COL; i++)
    {
        check[0][i] = 1;
        check[ROW - 1][i] = 1;
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
                // 80%的概率将未确认的节点加入队列
                if (check[nextX][nextY] == 0 && rand() % 100 < 72)
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
    for (int i = 1; i < ROW - 1; i++)
    {
        for (int j = 1; j < COL - 1; j++)
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
    for (int i = 0; i < ROW + 2; i++)
    {
        for (int j = 0; j < COL + 2; j++)
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

void CreatRandomMap(int map[ROW][COL], int start[2], int end[2])
{
    int check[ROW][COL]; // 0代表尚未确认，1代表已经确认, 2代表将要确认
    do
    {
        init(map, check, start, end); // 初始化
        bfs(map, check, start, end);  // bfs搜索
    } while (!linkStartAndEnd(map));  // 连接起点和终点成功
    standarizeMap(map, end);          // 将所有的2改为0, 将终点改为2
}

/*初始化游戏角色*/
struct Man man = {1, 1, 1};

int main()
{
    /*初始化控制台窗口*/
    system("chcp65001"); // 设置编码格式为UTF-8
    system("cls");       // cmd窗口清屏
    HideCursor();        // 隐藏光标

    /*初始化地图*/
    int map[ROW][COL];
    int start[2], end[2];
    CreatRandomMap(map, start, end);
    man.x = start[0];
    man.y = start[1];

    /*打印地图*/
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            CursorJump(2 * j, i);
            switch (map[i][j])
            {
            case 0: // 打印通道
                printf(" ");
                break;
            case 1: // 打印墙壁
                printf("■");
                break;
            case 2: // 打印目的地
                printf("#'");
                break;
            default:
                break;
            }
        }
    }

    /*打印游戏角色'@'*/
    CursorJump(2 * man.x, man.y);
    printf("@");

    /*游戏逻辑主体*/
    while (1)
    {
        /*获取角色控制指令*/
        int willx = 0;      // 暂存角色移动后的横坐标
        int willy = 0;      // 暂存角色移动后的纵坐标
        char key = getch(); // 读取keycode
        switch (key)
        {
        case UP: // 获取角色上移后的坐标
            willx = man.x;
            willy = man.y - man.v;
            break;
        case DOWN: // 获取角色下移后的坐标
            willx = man.x;
            willy = man.y + man.v;
            break;
        case LEFT: // 获取角色左移后的坐标
            willx = man.x - man.v;
            willy = man.y;
            break;
        case RIGHT: // 获取角色右移后的坐标
            willx = man.x + man.v;
            willy = man.y;
            break;
        default:
            break; // 其他按键则忽略处理
        }

        /*判断交互条件*/
        switch (map[willy][willx])
        {
        case 0:            // 在通道中移动
            man.x = willx; // 传递移动后的横坐标
            man.y = willy; // 传递移动后的纵坐标

            printf("\b ");                // 删除角色原来的痕迹
            CursorJump(2 * man.x, man.y); // 把光标移动到角色的目标坐标
            printf("@");                  // 打印角色符号
            break;
        case 1: // 撞墙
            break;
        case 2: // 到达目的地
            CursorJump(2 * COL + 2, 0);
            printf("You win!\n"); // 游戏胜利
            getch();              // 暂停等待，按任意键结束
            return 0;
            break;
        default:
            break;
        }
    }
}