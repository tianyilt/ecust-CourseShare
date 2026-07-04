#include <stdio.h>
#include <stdlib.h>

#define Stack_Size 100
typedef char StackElementType;

typedef struct
{
    StackElementType elem[Stack_Size];
    int top;
} SeqStack;

void InitStack(SeqStack *S)
{
    S->top = -1;
}

int Push(SeqStack *S, StackElementType x)
{
    if (S->top == Stack_Size - 1)
        return 0;
    S->top++;
    S->elem[S->top] = x;
    return 1;
}

int Pop(SeqStack *S, StackElementType *x)
{
    if (S->top == -1)
        return 0;
    *x = S->elem[S->top];
    S->top--;
    return 1;
}

int GetTop(SeqStack *S, StackElementType *x)
{
    if (S->top == -1)
        return 0;
    *x = S->elem[S->top];
    return 1;
}

int main()
{
    // ”√À≥–Ú’ª µœ÷¿®∫≈∆•≈‰
    SeqStack S;
    InitStack(&S);
    char str[Stack_Size];
    printf("Input a string with brackets: ");
    scanf("%s", str);
    int p = 0;
    char c = str[p++];
    while (c != '\0')
    {
        if (c == '(' || c == '[' || c == '{')
            Push(&S, c);
        else if (c == ')')
        {
            char x;
            GetTop(&S, &x);
            if (x == '(')
                Pop(&S, &x);
            else
            {
                printf("Not matched!\n");
                return 0;
            }
        }
        else if (c == ']')
        {
            char x;
            GetTop(&S, &x);
            if (x == '[')
                Pop(&S, &x);
            else
            {
                printf("Not matched!\n");
                return 0;
            }
        }
        else if (c == '}')
        {
            char x;
            GetTop(&S, &x);
            if (x == '{')
                Pop(&S, &x);
            else
            {
                printf("Not matched!\n");
                return 0;
            }
        }
        c = str[p++];
    }
    if (S.top == -1)
        printf("Matched!\n");
    else
        printf("Not matched!\n");
}
