#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void sorted(char a[][15], int length);

int main()
{
	printf("\n*===== 学号: 22012995 姓名: 张鸿尧 =====*\n");
	int i, n = 0, j, flag = 0, m = 0;
	char cities[15][15], b[15], temp[15];
	FILE *fp;
	fp = fopen("city.txt", "r");
	if (fp == NULL)
	{
		printf("未找到该文件\n");
	}
	while (fgets(cities[n], 15, fp) != NULL)
	{
		for (int i = 0; i < 15; i++)
		{
			if (cities[n][i] == '\n')
			{
				cities[n][i] = '\0';
			}
		}
		n++;
	}
	fclose(fp);
	sorted(cities, n);
	i = 0;
	while (i < n)
	{
		puts(cities[i++]);
	}
	printf("请输入你想查找的城市（英文，如Beijing,Chengdu）：");
	gets(b);
	for (j = 0; j < n; j++)
	{
		if (strcmp(b, cities[j]) == 0)
		{
			flag = 1;
			break;
		}
	}
	if (flag)
	{
		printf("查到这个城市！\n");
	}
	else
	{
		printf("没有找到这个城市！\n");
	}
	return 0;
}

void sorted(char a[][15], int length)
{
	char temp[15];
	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < length - i - 1; j++)
		{
			if (strcmp(a[j], a[j + 1]) > 0)
			{
				strcpy(temp, a[j]);
				strcpy(a[j], a[j + 1]);
				strcpy(a[j + 1], temp);
			}
		}
	}
}