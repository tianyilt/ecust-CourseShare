# include <stdio.h>
# define N 2

struct Student
{
	char num[10];
	char name[10];
	char phone[20];
	char addr[50];
}students[N];

void save()
{
	FILE *fp;
	int i;
	if ((fp=fopen("student.txt","w"))==NULL)
	{
		printf("Cannot open file\n");
		return;
	}
	for (i=0;i<N;i++)
	{
		fprintf(fp,"%-10s%-10s%-20d%-50s\n",students[i].num,students[i].name,students[i].phone,students[i].addr);
		printf("%-10s%-10s%-20d%-50s\n",students[i].num,students[i].name,students[i].phone,students[i].addr);
	}
	fclose(fp);
}

int main()
{
	int i;
	printf("Please enter data of %d students:\n",N);
	for (i=0;i<N;i++)
	{
		scanf("%s%s%s%s",students[i].num,students[i].name,students[i].phone,students[i].addr);
	}
	save();
	system("pause");
	return 0;
}