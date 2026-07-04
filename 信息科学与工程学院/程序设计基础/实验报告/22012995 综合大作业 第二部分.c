#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
int MAP[12][12];
int SCORE = 0;
double SCORES[202];
int GENERATION = 0;
/* the position of TinyYellow */
int TY_X = 1;
int TY_Y = 1;
int t1, t2, t3, t4, t5; // 5 tiles (include TY) around TY
int STRATEGY[243];      // The number based on 1
int BEST_STRATEGY[243];
int STRATEGIES[200][243];
int RANK[202];
int MU = 200; // The smaller the Gene Mutation Index is, the more likely the gene mutation will happen
/**
 *  id  meaning     sign
 *  0   vacancy
 *  1   wall          #
 *  2   tiny yellow   !
 *  3   jar           @
 *  4   yellow&jar    !@
 *
 */
#pragma region "Here is basic function in Project_1"
/* creat a random map */
void CreateMap(int map[12][12])
{
    int i, j;
    for (j = 0; j < 12; j++)
    {
        map[0][j] = map[11][j] = 1;
        map[j][0] = map[j][11] = 1;
    }
    for (i = 1; i < 11; i++)
    {
        for (j = 1; j < 11; j++)
        {
            map[i][j] = (rand() % 2) == 0 ? 0 : 3;
        }
    }
    map[1][1] = 2;
}
/* print the map  */
void PrintMap(const int map[12][12])
{
    for (int i = 0; i < 12; i++)
    {
        for (int j = 0; j < 12; j++)
        {
            switch (map[j][i])
            {
            case 0:
                printf("   ");
                break;
            case 1:
                printf("  #");
                break;
            case 2:
                printf(" ! ");
                break;
            case 3:
                printf("  @");
                break;
            case 4:
                printf(" !@");
                break;
            default:
                printf("???");
            }
        } // each num in one lane
        printf("    ");
        for (int j = 0; j < 12; j++)
        {
            printf("%3d", map[j][i]);
        }
        printf("\n");
    } // each lane
}
/* print info and score */
void PrintInfo(char info[], int score)
{
    printf("%-30s ", info);
    printf("score: %d\n\n", score);
}
/* move TinyYellow */
void Move(char direction)
{
    int *p = &MAP[TY_X][TY_Y];
    switch (direction)
    {
    case '2': // up
        if (TY_Y == 1)
        {
            SCORE -= 5;
            return;
        }
        TY_Y--;
        break;
    case '3': // down
        if (TY_Y == 10)
        {
            SCORE -= 5;
            return;
        }
        TY_Y++;
        break;
    case '4': // left
        if (TY_X == 1)
        {
            SCORE -= 5;
            return;
        }
        TY_X--;
        break;
    case '5': // right
        if (TY_X == 10)
        {
            SCORE -= 5;
            return;
        }
        TY_X++;
        break;
    default:
        break;
    }
    if (*p == 2)
    {
        *p = 0;
    }
    else if (*p == 4)
    {
        *p = 3;
    }
    else
    {
        printf("\nYou are a ghost?!\n");
    }
    if (MAP[TY_X][TY_Y] == 0)
    {
        MAP[TY_X][TY_Y] = 2;
    }
    else if (MAP[TY_X][TY_Y] == 3)
    {
        MAP[TY_X][TY_Y] = 4;
    }
    else
    {
        printf("\nYou met your clone?!\n");
    }
}
/* pick up a jar */
void PickUp()
{
    if (MAP[TY_X][TY_Y] == 4)
    {
        SCORE += 10;
        MAP[TY_X][TY_Y] = 2;
    }
    else
    {
        SCORE -= 2;
    }
}
#pragma endregion
/* print explanation */
void PrintExplanation()
{
    printf("Here\'s a display project.\n");
    printf("------------------------------------------------------------\n");
    printf("The program will read the \"strategy.txt\" in the same folder.\n");
    printf("Then show the whole process.\n");
    printf("------------------------------------------------------------\n");
    printf("\n");
    printf("Press any key to observe the whole process.");
    system("pause");
}
/* smooth output */
void gotoxy(int x, int y) // 光标移动到(x,y)位置，移动到（0,0）时用来清屏消除一闪一闪的
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE); // 在C语言中表示：从bai一个du特定的标
    COORD pos;                                       //  准zhi设备dao（标准输出）中取得一个句柄（用来标识不同设备的数值）。
    pos.X = x;
    pos.Y = y; // COORD pos = {x,y}; //定义COORD结构的实bai例pos，初始化参数用x和y，即dupos.x=x; pos.y=y;
    SetConsoleCursorPosition(handle, pos);
}
void hidden()
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    GetConsoleCursorInfo(hOut, &cci);
    cci.bVisible = FALSE;
    SetConsoleCursorInfo(hOut, &cci);
}
/* 100maps for one TY */
void TY_act(int total_steps)
{
    int input;
    int count = 0; // count the movement
    int case_id;   // a number representing current 5 tiles
    int k2 = 0, k3 = 0;
    // printf("//======================================//\n");
    CreateMap(MAP);
    input = 0;
    count = 0; // count the movement
    SCORE = 0;
    char info[30] = "Initial state";
    /* core */
    while (count++ < total_steps)
    {
        Sleep(180);
        gotoxy(0, 0);
        printf("% 4d moves left\n", total_steps + 1 - count);
        PrintMap(MAP);
        printf("\n");
        PrintInfo(info, SCORE);
        /* analyze the 5 tiles */
        /* here we convert jar into 2 */
        t1 = MAP[TY_X][TY_Y - 1] >= 3 ? 2 : (MAP[TY_X][TY_Y - 1] <= 0 ? 0 : 1);
        t2 = MAP[TY_X - 1][TY_Y] >= 3 ? 2 : (MAP[TY_X - 1][TY_Y] <= 0 ? 0 : 1);
        t3 = MAP[TY_X][TY_Y] <= 2 ? 0 : 2;
        t4 = MAP[TY_X + 1][TY_Y] >= 3 ? 2 : (MAP[TY_X + 1][TY_Y] <= 0 ? 0 : 1);
        t5 = MAP[TY_X][TY_Y + 1] >= 3 ? 2 : (MAP[TY_X][TY_Y + 1] <= 0 ? 0 : 1);
        case_id = t1 * 3 * 3 * 3 * 3 + t2 * 3 * 3 * 3 + t3 * 3 * 3 + t4 * 3 + t5;
        input = *(STRATEGY + case_id);
        /* deal input */
        if (input <= 1)
        {
            input = (rand() % 6 + 2);
        }
        switch (input)
        {
        case 2:
            strcpy(info, "Move up");
            Move('2');
            break;
        case 3:
            strcpy(info, "Move down");
            Move('3');
            break;
        case 4:
            strcpy(info, "Move left");
            Move('4');
            break;
        case 5:
            strcpy(info, "Move right");
            Move('5');
            break;
        case 6:
            strcpy(info, "Stand still");
            break;
        case 7:
            strcpy(info, "Pick up");
            PickUp();
            break;
        case 'p':
            count = 32;
            return;
        case '?':
            count--;
            system("cls");
            PrintExplanation();
            break;
        default:
            strcpy(info, "Invalid command");
            printf("\nThe command is invalid!\nInput again!\n");
            count--;
            printf("Your input is %d\n", input);
            printf("Current condition is %d\n", case_id);
            system("pause");
            return;
            break;
        } // switch end
    }     // core
}
/* load the strategy table of the first generation */
void LoadStrategyTable()
{
    FILE *f;
    f = fopen("strategy.txt", "r");
    char c, i = 0;
    while ((c = fgetc(f)) != EOF)
    {
        if (c < '0' || c > '9')
        {
            printf("The strategy.txt isn\'t formatted.\n");
            exit(0);
        }
        *(STRATEGY + i++) = (int)c - '0';
    }
    fclose(f);
}

int main()
{
    hidden();
    PrintExplanation();
    LoadStrategyTable();
    printf("Check the strategy: \n");
    for (int i = 0; i < 10; i++)
    {
        printf("%d", STRATEGY[i]);
    }
    printf("\n");
    system("pause");

    /* initialize the random seed */
    time_t t;
    srand((unsigned)time(&t));
    LoadStrategyTable();
    TY_act(200);
    printf("\nTY gets %ld.\n", SCORE);
end:
    system("pause");
    return 0;
}