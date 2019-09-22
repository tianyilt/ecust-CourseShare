# include <stdio.h>

int main()
{
	int n;
	char file[2][30], ch;
	FILE *fout, *fin;
	printf("输入明文文件名: ");
	scanf("%s",file[0]);
	printf("输入n的值: ");
	scanf("%d",&n);
	printf("输入密文文件名: ");
	scanf("%s",file[1]);
	if ((fin=fopen(file[0],"r"))==NULL||(fout=fopen(file[1],"w+"))==NULL)
	{
		printf("Cannot open file\n");
		exit(0);
	}
	while (~(ch=fgetc(fin))) fputc(ch+n,fout);
	rewind(fout);
	printf("加密成功后的密文为: ");
	while(~(ch=fgetc(fout))) putchar(ch);
	putchar(10);
	fclose(fin);
	fclose(fout);
	system("pause");
	return 0;
}