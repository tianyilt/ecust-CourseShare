#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int MAP[12][12];
int SCORE = 0;
/* the position of TinyYellow */
int TY_X = 1;
int TY_Y = 1;

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

/**
 *  id  meaning     sign
 *  0   vacancy
 *  1   wall          #
 *  2   tiny yellow   !
 *  3   jar           @
 *  4   yellow&jar    !@
 *
 */

/* print the map  */
void PrintMap(int map[12][12])
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
        printf("\n");
    } // each lane
}

/* print info and score */
void PrintInfo(char info[], int score)
{
    printf("%-30s ", info);
    printf("score: %d\n\n", score);
}

/* print explanation */
void PrintExplanation()
{
    printf("Here\'s the rules\n");
    printf("------------------------------------------------------------\n");
    printf("What\'s the legend?\n");
    printf("Wall\t\t#\n");
    printf("TinyYellow\t!\n");
    printf("Jar\t\t@\n");
    printf("\n");
    printf("How to move?\n");
    printf("Input the corresponding number to control the TinyYellow\n");
    printf("1 or q\tRandom movement\n");
    printf("2 or w\tMove up\n");
    printf("3 or s\tMove down\n");
    printf("4 or a\tMove left\n");
    printf("5 or d\tMove right\n");
    printf("6 or x\tStand still\n");
    printf("7 or e\tPick up the jar\n");
    printf("\n");
    printf("How to score?\n");
    printf("*Hit the wall\t\t-5\'\n");
    printf("*Pick up a jar\t\t+10\'\n");
    printf("*Pick up nothing\t-2\'\n");
    printf("------------------------------------------------------------\n");
    printf("\n");
    printf("Once you understand the rules, press any key to start the game.");
    system("pause");
}

/* move TinyYellow */
void Move(int direction)
{
    int *p;
    p = &MAP[TY_X][TY_Y];

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

int main()
{
    PrintExplanation();

    /* initialize the random seed */
    time_t t;
    srand((unsigned)time(&t));
    CreateMap(MAP);

    char input;
    char info[30] = "Initial state";
    int count = 0; // count the movement

    /* core */
    while (count++ < 32)
    {
        system("cls");
        printf("% 4d moves left\n", 33 - count);
        PrintMap(MAP);
        PrintInfo(info, SCORE);
        printf("Input the command(if you forget the rules, input \'?\'; input \'p\' to quit)\n");
        input = getchar();
        while (getchar() != '\n')
        {
        }
        /* deal input */
        if (input == '1' || input == 'q')
        {
            input = (rand() % 6 + 2) + '0';
        }
        switch (input)
        {

        case '2':
        case 'w':
            strcpy(info, "Move up");
            Move('2');
            break;
        case '3':
        case 's':
            strcpy(info, "Move down");
            Move('3');
            break;
        case '4':
        case 'a':
            strcpy(info, "Move left");
            Move('4');
            break;
        case '5':
        case 'd':
            strcpy(info, "Move right");
            Move('5');
            break;
        case '6':
        case 'x':
            strcpy(info, "Stand still");
            break;
        case '7':
        case 'e':
            strcpy(info, "Pick up");
            PickUp();
            break;
        case 'p':
            count = 32;
            return 0;
        case '?':
            system("cls");
            PrintExplanation();
            break;
        default:
            strcpy(info, "Invalid command");
            printf("\nThe command is invalid!\nInput again!\n");
            count--;
            system("pause");
            break;
        } // switch end
    }

    printf("\nGame end!\n");
    printf("TinyYellow get the score of %d under your guidiance.", SCORE);
    system("pause");
    return 0;
}
