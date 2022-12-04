# include <stdio.h>

int search(int list[], int n, int x)
{
	int i;
	for (i=0;i<n;i++)
	{
		if (*(list+i)==x) return i;
	}
	return -1;
}

int main()
{
	int list[10],n,x,i,result;
	printf("Input n: ");
	scanf("%d",&n);
	printf("Input %d integers: ",n);
	for (i=0;i<n;i++) scanf("%d",list+i);
	printf("Input x: ");
	scanf("%d",&x);
	result = search(list,n,x);
	if (result==-1) printf("Not found\n");
	else printf("Index=%d\n",result);
	system("pause");
	return 0;
}