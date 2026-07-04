#include <stdio.h>
#include <stdlib.h>

#define Stack_Size 50
typedef int StackElementType;

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
    SeqStack S;
    InitStack(&S);
    printf("Check if a number is a palindrome, input the number: ");
    int x;
    scanf("%d", &x);
    // 用栈逆序存储数字
    int temp = x;
    while (temp > 0)
    {
        Push(&S, temp % 10);
        temp /= 10;
    }
    // 逐个弹出栈顶元素与原数比较
    int flag = 1;
    while (S.top != -1)
    {
        Pop(&S, &temp);
        if (temp != x % 10)
        {
            flag = 0;
            break;
        }
        x /= 10;
    }
    if (flag)
        printf("Is a palindrome number\n");
    else
        printf("Is not a palindrome number\n");
    return 0;
    // 时间复杂度分析:
    //      用栈逆序存储数字: O(n)
    //      逐个弹出栈顶元素与原数比较: O(n)
    //      故总时间复杂度为O(2n)
    //
    // 空间复杂度分析:
    //      用栈逆序存储数字: O(n)
}
