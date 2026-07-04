#include <stdio.h>

int flag(char ch[]);

int main()
{
	char a[18], FLAG = 'y';
	printf("\n*===== 学号: 22012995 姓名: 张鸿尧 =====*\n");
	while (FLAG == 'Y' || FLAG == 'y')
	{
		printf("请输入身份证号：\n");
		gets(a);
		if (flag(a) == 1)
			printf("correct,出生年月为%c%c%c%c年%c%c月%c%c日\n", a[6], a[7], a[8], a[9], a[10], a[11], a[12], a[13]);
		else
			printf("wrong\n");
		printf("是否继续，如果“是”，则输入Y（y）；如果“否”，则输入N（n): ");
		FLAG = getchar();
		fflush(stdin);
	}
	return 0;
}

int flag(char ch[])
{
	int m, n, a[18];
	for (n = 0; n < 18; n++)
	{
		if (ch[n] == 'x' || ch[n] == 'X')
		{
			a[n] = 10;
		}
		else if (ch[n] - '0' >= 0 && ch[n] - '0' <= 9)
		{
			a[n] = ch[n] - '0';
		}
		else
		{
			return 0;
		}
	}
	m = a[0] * 7 + a[1] * 9 + a[2] * 10 + a[3] * 5 + a[4] * 8 + a[5] * 4 + a[6] * 2 + a[7] * 1 + a[8] * 6 + a[9] * 3 + a[10] * 7 + a[11] * 9 + a[12] * 10 + a[13] * 5 + a[14] * 8 + a[15] * 4 + a[16] * 2;
	if (m % 11 >= 2 && m % 11 == 12 - a[17])
		return 1;
	else if (m % 11 <= 1 && m % 11 == 1 - a[17])
		return 1;
	else
		return 0;
}