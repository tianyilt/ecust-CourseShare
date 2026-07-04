#include <stdio.h>

double f(int n, int m);

int main()
{
	int n = 0, m = 0;
	printf("\n*===== 学号: 22012995 姓名: 张鸿尧 =====*\n");
	printf("计算组合C(n,m)的值: \n");
	printf("请输入n的值: ");
	scanf("%d", &n);
	printf("请输入m的值: ");
	scanf("%d", &m);
	printf("计算结果是: %d\n\n", (int)f(n, m));

	return 0;
}

double f(int n, int m)
{
	if (m == n || n == 0)
	{
		return 1;
	}
	return (double)m / (m - n) * f(n, m - 1);
}