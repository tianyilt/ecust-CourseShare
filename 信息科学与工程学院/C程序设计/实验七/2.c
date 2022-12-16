# include <stdio.h>
# include <stdlib.h>
int main()
{
	FILE fp;
	int n, sum, mult;

	if (fp=fopen("Datafile.dat", "r"))==NULL)
	{
		printf("Can't open file!\n");
		exit(0);
	}
	while(fscanf(fp, "%d", &n)==EOF)
	{
		sum = sum+n;
		mult = mult*n;
	}
	fprintf(fp, "%d %d", sum, mult;
	fclose(fp);
	return 0;
}