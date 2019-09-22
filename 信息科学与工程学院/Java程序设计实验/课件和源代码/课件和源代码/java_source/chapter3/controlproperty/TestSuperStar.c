#include <stdio.h>
#include "SuperStar.h"
#include "malloc.h"
int main(int argc, char *argv[])
{
	 struct SuperStar *star=NULL;
	 star=(struct SuperStar *)malloc(sizeof(struct SuperStar ));
	 setAge(star,60);
	 setName(star,"成龙");
	 printf("%s  %d岁\n", getName(star), getAge(star));
	 printf("%s  %d岁\n",star->name,star->age);//可通过struct的field获得真实的值
	 
	 free(star);
	return 0;
}
