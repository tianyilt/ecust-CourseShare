#include<stdio.h>
#define N 10
int main()
{
	int i,j,m,n,sum;
	struct info
	{
		int num;
		char name[20];
		char nation[20];
		int score[7];
		float ave;
	};
	struct info a[N];
	printf("请输入选手信息：编号、姓名、国籍、7位评委的打分：\n");
	i=0;
	for(i;i<N;i++)
	{
		scanf("%d %s %s",&a[i].num,a[i].name,a[i].nation);
		j=0,m=0,n=0,sum=0;
		for(j;j<7;j++)
		{
			scanf("%d",&a[i].score[j]);
			if(a[i].score[j]>a[i].score[m])
				m=j;
			if(a[i].score[j]<a[i].score[n])
				n=j;
			sum+=a[i].score[j];
		}
		sum=sum-a[i].score[m]-a[i].score[n];
		a[i].ave=sum*1.0/5;
	}
	printf("选手最终成绩：\n");
	printf("No.   Name    Nationality  Total_Score\n");
	for(i=0;i<N;i++)
		printf("%-6d%-8s  %-11s  %-.2f\n",a[i].num,a[i].name,a[i].nation,a[i].ave);
	system("pause");
	return 0;
}
