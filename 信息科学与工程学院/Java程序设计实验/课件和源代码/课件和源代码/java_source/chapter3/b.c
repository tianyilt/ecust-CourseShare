#include <stdio.h>
void prn(int i){
	i++;
}
void prn2(int *i){
	(*i)++;
} 
int main(int argc, char *argv[])
{  int j=0;
   prn(j); 
   printf(" %d\n",j);
   prn2(&j); 
   printf(" %d\n",j); 
   return 0;
}
