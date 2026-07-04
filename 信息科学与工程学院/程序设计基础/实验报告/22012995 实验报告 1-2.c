#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int answer1;
float answer2;
int Add(int a, int b)
{
	return a + b;
}

int Sub(int a, int b)
{
	return a - b;
}

int Mul(int a, int b)
{
	return a * b;
}

float Div(int a, int b)
{
	float k;
	int m;
	k = (float)a / b;
	m = (int)(k * 100 + 0.5);
	k = (float)m / 100;
	return k;
}

int main()
{

	int a, b, n, i, score = 0;
	char FLAG = 'Y';
	FILE *fp;
	srand((unsigned)time(NULL));
	fp = fopen("result.txt", "w");
	if (fp == NULL)
	{
		printf("未找到文件\n");
	}
	printf("\n*===== 学号: 22012995 姓名: 张鸿尧 =====*\n");
	printf("二十以内的加、减、乘、除（四舍五入保留两位小数），请答题：\n");
	while (FLAG == 'Y' || FLAG == 'y')
	{

		for (i = 1; i <= 5; i++)
		{
			n = rand() % 4 + 1;
			a = rand() % 21;
			b = rand() % 21;
			if (n == 1)
			{
				printf("%d+%d=", a, b);
				scanf("%d", &answer1);
				fprintf(fp, "%d+%d=%d\n", a, b, answer1);
				if (answer1 == Add(a, b))
				{
					score += 20;
				}
			}
			else if (n == 2)
			{
				printf("%d-%d=", a, b);
				scanf("%d", &answer1);
				fprintf(fp, "%d-%d=%d\n", a, b, answer1);
				if (answer1 == Sub(a, b))
				{
					score += 20;
				}
			}
			else if (n == 3)
			{
				printf("%d*%d=", a, b);
				scanf("%d", &answer1);
				fprintf(fp, "%d*%d=%d\n", a, b, answer1);
				if (answer1 == Mul(a, b))
				{
					score += 20;
				}
			}
			else if (n == 4)
			{
				printf("%d/%d=", a, b);
				scanf("%lf", &answer2);
				fprintf(fp, "%d/%d=%lf\n", a, b, answer2);
				if (answer2 - Div(a, b) <= 0.01)
				{
					score += 20;
				}
			}
		}
		printf("正确率为：%d%%\n", score);
		fprintf(fp, "正确率为：%d%%\n", score);
		score = 0;
		printf("是否继续，如果“是”，则输入Y（y）；如果“否”，则输入N（n)\n");
		fflush(stdin);
		FLAG = getchar();
	}
	fclose(fp);
	return 0;
}