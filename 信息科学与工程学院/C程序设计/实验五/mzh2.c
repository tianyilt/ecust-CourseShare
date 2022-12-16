#include<stdio.h>
#define N 5
int main()
{
	void Input();
	void Output();
	int n
	struct info
	{
		char name[20];
		char author[20];
		char pub[20];
		int year;
		float prize;
		char ISBN[20];
	}a[M];
	n=N;
	printf("请输入%d本图书信息：书名，作者，出版社，出版年，单价，ISBN编号：\n",n);
	Input();
	printf("\n");
	printf("图书检索的结果是:\n");
	printf("   书名             作者              出版社          出版年      单价          ISBN\n");
	Output();
	system("pause");
	return 0;
}

void Input()
{
	int i;
	for(i=0;i<M;i++)
		scanf("%s%s%s%d%f%s",a[i].name,a[i].author,a[i].pub,&a[i].year,&a[i].prize,a[i].ISBN);
}

void Output()
{
	