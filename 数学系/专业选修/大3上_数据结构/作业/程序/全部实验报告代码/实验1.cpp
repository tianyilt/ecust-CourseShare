#include "stdio.h"

#define MAXSIZE 10
void Mult_matrix(int c[MAXSIZE][MAXSIZE],
	int a[MAXSIZE][MAXSIZE],
	int b[MAXSIZE][MAXSIZE], int n)
{
	int i, j, k;
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++) {
			c[i][j] = 0;
			for (k = 0; k < n; k++)
				c[i][j] += a[i][k] * b[k][j];
		};
}/*Mult_matrix*/

int main(void)
{
	int n, i, j;
	int a[MAXSIZE][MAXSIZE], b[MAXSIZE][MAXSIZE], c[MAXSIZE][MAXSIZE];
	printf("\n\n");
	printf("input the dimension of matrix:");
	scanf("%d", &n);
	printf("\n\n");
	printf("input data by row for matrix a\n");
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
		{
			printf("input a[%d][%d]:\n", i, j);
			scanf("%d",&a[i][j]);
		}
	printf("\n\n");
	printf("input data by row for matrix b\n");
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
		{
			printf("input b[%d][%d]:", i, j);
			scanf("%d",&b[i][j] );
		}
	Mult_matrix(c, a, b, n);
	printf("output matrix c\n");
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
			printf("%10d",c[i][j] );
		printf("\n");
	}
}

