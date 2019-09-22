# include <stdio.h>

int tran(int year, int *month, int *day)
{
	int cases=0;
	if ((year%4==0 && year%100!=0)||(year%400==0))
	{
		if (*day>0&&*day<=31) cases=12;
		else if (*day>31&&*day<=60) cases=11;
		else if (*day>60&&*day<=91) cases=10;
		else if (*day>91&&*day<=121) cases=9;
		else if (*day>121&&*day<=152) cases=8;
		else if (*day>152&&*day<=182) cases=7;
		else if (*day>182&&*day<=213) cases=6;
		else if (*day>213&&*day<=244) cases=5;
		else if (*day>244&&*day<=274) cases=4;
		else if (*day>274&&*day<=305) cases=3;
		else if (*day>305&&*day<=335) cases=2;
		else if (*day>335&&*day<=366) cases=1;
		else cases=-1;
		switch(cases)
		{
			case 1: *month+=1;*day-=30;
			case 2: *month+=1;*day-=31;
			case 3: *month+=1;*day-=30;
			case 4: *month+=1;*day-=31;
			case 5: *month+=1;*day-=31;
			case 6: *month+=1;*day-=30;
			case 7: *month+=1;*day-=31;
			case 8: *month+=1;*day-=30;
			case 9: *month+=1;*day-=31;
			case 10: *month+=1;*day-=29;
			case 11: *month+=1;*day-=31;
			case 12: *month+=1;break;
			default: return -1;
		}
	}
	else
	{
		if (*day>0&&*day<=31) cases=12;
		else if (*day>31&&*day<=59) cases=11;
		else if (*day>59&&*day<=90) cases=10;
		else if (*day>90&&*day<=120) cases=9;
		else if (*day>120&&*day<=151) cases=8;
		else if (*day>151&&*day<=181) cases=7;
		else if (*day>181&&*day<=212) cases=6;
		else if (*day>212&&*day<=243) cases=5;
		else if (*day>243&&*day<=273) cases=4;
		else if (*day>273&&*day<=304) cases=3;
		else if (*day>304&&*day<=334) cases=2;
		else if (*day>334&&*day<=365) cases=1;
		else cases=-1;
		switch(cases)
		{
			case 1: *month+=1;*day-=30;
			case 2: *month+=1;*day-=31;
			case 3: *month+=1;*day-=30;
			case 4: *month+=1;*day-=31;
			case 5: *month+=1;*day-=31;
			case 6: *month+=1;*day-=30;
			case 7: *month+=1;*day-=31;
			case 8: *month+=1;*day-=30;
			case 9: *month+=1;*day-=31;
			case 10: *month+=1;*day-=28;
			case 11: *month+=1;*day-=31;
			case 12: *month+=1;break;
			default: return -1;
		}
	}
	return 1;
}

int main()
{
	int year, day, month=0, *m=&month, *d=&day, isTrue=0;
	printf("请输入Julian历法的日期(年，第几天): ");
	scanf("%d,%d",&year,&day);
	isTrue = tran(year,m,d);
	if (isTrue==1) printf("现代历法的日期是:%d年%d月%d日\n",year,month,day);
	else printf("您输入的Julian日期有误!\n");
	system("pause");
	return 0;
}
