# include <stdio.h>

void average(int score[][4])
{
	int i,num,sum=0;
	printf("Please enter the class num: ");
	scanf("%d",&num);
	for (i=0;i<5;i++) sum += *(*(score+i)+num-1);
	printf("The average score of class %d is: %.2f\n",num,sum/5.0);
}

void fail(int score[][4])
{
	int i,j,sum,num;
	printf("Students failed:\n");
	for (i=0;i<5;i++)
	{
		num = 0;
		sum = 0;
		for (j=0;j<4;j++)
		{
			sum += *(*(score+i)+j);
			if (*(*(score+i)+j)<60) num+=1;
		}
		if (num > 1) printf("Num.%d score:%d %d %d %d average:%.2f\n",i+1,*(*(score+i)+0),*(*(score+i)+1),*(*(score+i)+2),*(*(score+i)+3),sum/4.0);
	}
}

void passed(int score[][4])
{
	int i,j,sum,num;
	printf("Students passed:\n");
	for (i=0;i<5;i++)
	{
		sum = 0;
		num = 4;
		for (j=0;j<4;j++)
		{
			sum += *(*(score+i)+j);
			if (*(*(score+i)+j)>85) num -= 1;
		}
		if (num==0||sum/4.0>90) printf("Num.%d score:%d %d %d %d average:%.2f\n",i+1,*(*(score+i)+0),*(*(score+i)+1),*(*(score+i)+2),*(*(score+i)+3),sum/4.0);
	}
}

int main()
{
	int i, score[5][4];
	printf("Please input the score.Each student in one line:\n");
	for (i=0;i<5;i++) scanf("%d%d%d%d",&score[i][0],&score[i][1],&score[i][2],&score[i][3]);
	average(score);
	fail(score);
	passed(score);
	system("pause");
	return 0;
}