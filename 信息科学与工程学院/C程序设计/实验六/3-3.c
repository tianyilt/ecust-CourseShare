# include <stdio.h>
# include <string.h>

int Duplicate(char str[],char dest[],int n)
{
	char *p=str+n-1,*q=dest;
	if (n>strlen(str)) return -1;
	for (;*p!='\0';p++,q++) *q=*p;
	return strlen(dest);
}

int main()
{
	char str[100],dest[100]={'\0'};
	int n,num;
	printf("Input a string: ");
	scanf("%[^\n]",str);
	printf("Input a integer: ");
	scanf("%d",&n);
	num = Duplicate(str,dest,n);
	printf("Output is: %s, %d characters.\n",dest,num);
	system("pause");
	return 0;
}