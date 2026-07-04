#include <stdio.h>
#include <stdlib.h>
#define MaxSize 100 // 非零元素的个数最多100
typedef int ElemType;

typedef struct
{
    int row, col;
    ElemType e;
} Triple;
typedef struct
{
    Triple data[MaxSize + 1];
    int m, n, len;
} TSMatrix;

void initiateTSMatrix(TSMatrix *M, int M0[4][4])
{
    int i, j, k = 1;
    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
            if (M0[i][j] != 0)
            {
                M->data[k].e = M0[i][j];
                M->data[k].row = i;
                M->data[k++].col = j;
            }
    M->m = 4;
    M->n = 4;
    M->len = k - 1;
}

void OutMatrix(TSMatrix *M) // 输出稀疏矩阵
{
    int i;
    for (i = 1; i <= M->len; i++)
    {
        printf("%d %d %d\n", M->data[i].row, M->data[i].col, M->data[i].e);
    }
    printf("\n");
}

void AddMatrix(TSMatrix *A, TSMatrix *B, TSMatrix *C)
{
    int pA, pB, pC;
    pA = pB = pC = 1;
    while (pA <= A->len && pB <= B->len)
    {
        // A的行列字典序小于B
        if ((A->data[pA].row < B->data[pB].row) || ((A->data[pA].row == B->data[pB].row) && (A->data[pA].col < B->data[pB].col)))
        {
            C->data[pC].row = A->data[pA].row;
            C->data[pC].col = A->data[pA].col;
            C->data[pC++].e = A->data[pA++].e;
        }
        // A的行列字典序大于B
        else if ((A->data[pA].row > B->data[pB].row) || ((A->data[pA].row == B->data[pB].row) && (A->data[pA].col > B->data[pB].col)))
        {
            C->data[pC].row = B->data[pB].row;
            C->data[pC].col = B->data[pB].col;
            C->data[pC++].e = B->data[pB++].e;
        }
        // A的行列字典序等于B
        else
        {
            C->data[pC].row = A->data[pA].row;
            C->data[pC].col = A->data[pA].col;
            C->data[pC++].e = A->data[pA++].e + B->data[pB++].e;
        }
    }
    while (pA <= A->len)
    {
        C->data[pC].row = A->data[pA].row;
        C->data[pC].col = A->data[pA].col;
        C->data[pC++].e = A->data[pA++].e;
    }
    while (pB <= B->len)
    {
        C->data[pC].row = B->data[pB].row;
        C->data[pC].col = B->data[pB].col;
        C->data[pC++].e = B->data[pB++].e;
    }
    C->m = A->m;
    C->n = A->n;
    C->len = pC - 1;
}

int main()
{
    // 定义两个稀疏数组A,B 求他们的和C
    TSMatrix A, B, C;
    int A0[4][4] = {
        {0, 0, 3, 0},
        {0, 0, 5, 7},
        {0, 0, 0, 0},
        {0, 2, 6, 0}};
    int B0[4][4] = {
        {1, 0, 3, 0},
        {0, 0, 2, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 4}};
    initiateTSMatrix(&A, A0);
    initiateTSMatrix(&B, B0);
    printf("A:\n");
    OutMatrix(&A);
    printf("B:\n");
    OutMatrix(&B);
    AddMatrix(&A, &B, &C);
    printf("C:\n");
    OutMatrix(&C);
    return 0;
    // 时间复杂度分析:
    //     两个数组的非零元素个数分别为k1,k2
    //     所以C的非零元素个数为k1+k2
    //     所以求C的时间复杂度为O(k1+k2)
    // 空间复杂度分析:
    //     由于采用顺序存储,所以空间复杂度为O(1)
}