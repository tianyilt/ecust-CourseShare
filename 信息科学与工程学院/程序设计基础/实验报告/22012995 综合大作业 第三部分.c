#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
int MAP[12][12];
int SCORE = 0;
double SCORES[202];
int GENERATION = 0;
int MAX_GENERATION = 1000;
/* the position of TinyYellow */
int TY_X = 1;
int TY_Y = 1;
int t1, t2, t3, t4, t5; // 5 tiles (include TY) around TY
int STRATEGY[243];      // The number based on 1
int BEST_STRATEGY[243];
double BEST_SCORE = 0;
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
        printf("\t");
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
    printf("Here\'s the Final Project\n");
    printf("------------------------------------------------------------\n");
    printf("The program will produce a total random strategy table as txt.\n");
    printf("Each generation has 100 TinyYellows.\n");
    printf("Each of them will act on 100 random maps for 200 steps.\n");
    printf("An average score of each generation will be shown.\n");
    printf("All TinyYellows will be ranked according to their scores.\n");
    printf("The new generation comes from the top 10, and 45 pairs of offsprings.\n");
    printf("There will be 1000 generation in all to show the process of evolution.\n");
    printf("It takes some time, be patient.\n");
    printf("------------------------------------------------------------\n");
    printf("\n");
    printf("Press any key to observe the whole process.");
    system("pause");
}
/* DIY time out function */
void delay()
{
    int i, j;
    for (i = 0; i < 20000; i++)
    {
        for (j = 0; j < 10000; j++)
            ;
    };
}
/* 100maps for one TY */
double TY_act(int number, int times, int total_steps)
{
    int input;
    char info[30] = "Initial state";
    int count = 0; // count the movement
    int case_id;   // a number representing current 5 tiles
    int k2 = 0, k3 = 0;
    *(SCORES + number) = 0.0;
    for (k2 = 0; k2 < times; k2++)
    {
        // printf("//======================================//\n");
        CreateMap(MAP);
        input = 0;
        count = 0; // count the movement
        SCORE = 0;
        /* core */
        while (count++ < total_steps)
        {
            // delay();
            // system("cls");
            // printf("% 4d moves left\n", total_steps + 1 - count);
            // PrintMap(MAP);
            // printf("\n");
            // PrintInfo(info, SCORE);
            /* analyze the 5 tiles */
            /* here we convert jar into 2 */
            t1 = MAP[TY_X][TY_Y - 1] >= 3 ? 2 : (MAP[TY_X][TY_Y - 1] <= 0 ? 0 : 1);
            t2 = MAP[TY_X - 1][TY_Y] >= 3 ? 2 : (MAP[TY_X - 1][TY_Y] <= 0 ? 0 : 1);
            t3 = MAP[TY_X][TY_Y] <= 2 ? 0 : 2;
            t4 = MAP[TY_X + 1][TY_Y] >= 3 ? 2 : (MAP[TY_X + 1][TY_Y] <= 0 ? 0 : 1);
            t5 = MAP[TY_X][TY_Y + 1] >= 3 ? 2 : (MAP[TY_X][TY_Y + 1] <= 0 ? 0 : 1);
            case_id = t1 * 3 * 3 * 3 * 3 + t2 * 3 * 3 * 3 + t3 * 3 * 3 + t4 * 3 + t5;
            input = *(STRATEGIES[number] + case_id);
            /* deal input */
            if (input <= 1)
            {
                input = (rand() % 6 + 2);
            }
            switch (input)
            {
            case 2:
                // strcpy(info, "Move up");
                Move('2');
                break;
            case 3:
                // strcpy(info, "Move down");
                Move('3');
                break;
            case 4:
                // strcpy(info, "Move left");
                Move('4');
                break;
            case 5:
                // strcpy(info, "Move right");
                Move('5');
                break;
            case 6:
                // strcpy(info, "Stand still");
                break;
            case 7:
                // strcpy(info, "Pick up");
                PickUp();
                break;
            case 'p':
                count = 32;
                return 0.0;
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
                return 0.0;
                break;
            } // switch end
        }     // core
        *(SCORES + number) += SCORE * 1.0;
        TY_X = 1;
        TY_Y = 1;
        // delay();
    } // each TY's map of 100
    *(SCORES + number) /= 100.0;
    // printf("The average score of Tiny Yellow No.% 3d\'s 100 tries is: %.4lf\n", number, *(SCORES + number));
    return *(SCORES + number);
}
/* print score board */
void PrintScoreBoard()
{
    printf("\n----------------------------\n");
    printf("The following is the Rank Table of this turn: \n");
    printf("Rank\tID\tScore\n");
    for (int z = 0; z < 200; z++)
    {
        printf("%-3d\t% 3d\t%lf\n", z, *(RANK + z), *(SCORES + *(RANK + z)));
    }
    printf("\n----------------------------\n");
}
/* core play */
void CorePlay()
{
    double currentScore;
    for (int i = 0; i < 200; i++)
    {
        currentScore = TY_act(i, 100, 200);
        if (i == 0)
        {
            for (int ii = 1; ii < 201; ii++)
            {
                *(RANK + ii) = -1;
            }
            *(RANK) = 0;
            continue;
        }
        // insert current TY's id number into the RANK board, with their SCORES in descending order
        int j;
        for (j = 0; j < 200; j++)
        {
            if (*(RANK + j) == -1 || *(SCORES + *(RANK + j)) - currentScore < 0.0001)
            {
                break;
            }
        }
        for (int k = 199; k >= j; k--)
        {
            *(RANK + k + 1) = *(RANK + k);
        }
        *(RANK + j) = i;
    }
}
/* load the strategy table of the first generation */
void CreateStrategies(int number)
{
    FILE *f;
    f = fopen("strategy_table_G0.txt", "w");
    for (int i = 0; i < number; i++)
    {
        fprintf(f, "#");
        for (int j = 0; j < 243; j++)
        {
            fprintf(f, "%d", rand() % 7 + 1);
        }
        fprintf(f, "\n");
    }
    fclose(f);
}
/* load the strategy table of the first generation */
void LoadStrategyTable()
{
    FILE *f;
    f = fopen("strategy_table_G0.txt", "r");
    int c;
    int number = 0;
    while ((c = fgetc(f)) != EOF)
    {
        if (c == '#') /* start one TY */
        {
            for (int i = 0; i < 243; i++)
            {
                *(STRATEGY + i) = fgetc(f) - '0';
                *(*(STRATEGIES + number) + i) = *(STRATEGY + i);
                // printf("%d", *(STRATEGY + i));
            }
            number++;
        }
    }
    fclose(f);
}
int main()
{
    PrintExplanation();
    printf("Give a MU: ");
    scanf("%d", &MU);
    printf("To which generation: ");
    scanf("%d", &MAX_GENERATION);
    /* initialize the random seed */
    time_t t;
    srand((unsigned)time(&t));
    /* create and load 200 TYs' strategies */
    CreateStrategies(200);
    LoadStrategyTable();
    FILE *scoreFILE;
    scoreFILE = fopen("scores.txt", "w");
    while (GENERATION < MAX_GENERATION)
    {
        CorePlay();
        double average = 0.0;
        for (int j = 0; j < 200; j++)
        {
            average += *(SCORES + j);
        }
        average /= 200.0;
        // PrintScoreBoard();
        printf("200 G%03d_TinyYellows get an average score of %-03.4lf\n", GENERATION, average);
        fprintf(scoreFILE, "%.4lf\n", average);
        // system("pause");
        // system("cls");
        // printf("TinyYellows are reproducing offsprings...\n");
        // creat a RANKS table, in which, the Rank 0 TY gets 200 chances, while the Rank 199 TY gets 1 chances
        int RANKS[20102], n = 0;
        for (int k = 0; k < 200; k++)
        {
            for (int m = 0; m < 200 - k; m++)
            {
                RANKS[n++] = *(RANK + k);
            }
        }
        if (*(SCORES + RANK[0]) > BEST_SCORE)
        {
            BEST_SCORE = *(SCORES + RANK[0]);
            for (int i = 0; i < 243; i++)
            {
                BEST_STRATEGY[i] = *(*(STRATEGIES + RANK[0]) + i);
            }
        }
        // A temporary offspring table to hold the new generation
        int temp_STRATEGIES[200][243];
        // 2 parents reproduce 2 offsprings, 95 pairs in all
        for (int o = 0; o < 95; o++)
        {
            int parent1, parent2;
            int child1[243], child2[243];
            parent1 = rand() % 20100;
            parent2 = rand() % 20100;
            for (int p = 0; p < 4; p++)
            {
                for (int q = p * 60; q < 243; q++)
                {
                    if (p % 2 == 0)
                    {
                        child1[q] = (rand() % MU != 0) ? *(*(STRATEGIES + RANKS[parent1]) + q) : (rand() % 7) + 1;
                        child2[q] = (rand() % MU != 0) ? *(*(STRATEGIES + RANKS[parent2]) + q) : (rand() % 7) + 1;
                    }
                    else
                    {
                        child1[q] = (rand() % MU != 0) ? *(*(STRATEGIES + RANKS[parent2]) + q) : (rand() % 7) + 1;
                        child2[q] = (rand() % MU != 0) ? *(*(STRATEGIES + RANKS[parent1]) + q) : (rand() % 7) + 1;
                    }
                }
            }
            for (int r = 0; r < 243; r++)
            {
                *(*(temp_STRATEGIES + 2 * o) + r) = child1[r];
                *(*(temp_STRATEGIES + 2 * o + 1) + r) = child2[r];
            }
        }
        // The top 10 TYs will be added into the next generation directly
        for (int s = 0; s < 10; s++)
        {
            for (int t = 0; t < 243; t++)
            {
                *(*(temp_STRATEGIES + s + 190) + t) = *(*(STRATEGIES + RANK[s]) + t);
            }
        }
        // Now replace the STRATEGIES table with a new generation
        for (int u = 0; u < 200; u++)
        {
            for (int v = 0; v < 243; v++)
            {
                *(*(STRATEGIES + u) + v) = *(*(temp_STRATEGIES + u) + v);
            }
        }
        GENERATION++;
        // printf("[Done] Current generation is: %d\n", GENERATION);
    }
    fclose(scoreFILE);
    FILE *f;
    f = fopen("strategy.txt", "w");
    for (int i = 0; i < 243; i++)
    {
        fprintf(f, "%d", BEST_STRATEGY[i]);
    }
    fclose(f);
    printf("The strategy table of the highest score has been out put to txt.\n");
end:
    system("pause");
    return 0;
}