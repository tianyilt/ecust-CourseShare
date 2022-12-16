#ifndef SUPERSTAR_H
#define SUPERSTAR_H

struct SuperStar
{
        char *name;
        int age; 
} ;
char* getName(struct SuperStar *star) ;
void setName(struct SuperStar *star,char *name) ;

int getAge(struct SuperStar *star); 
void setAge(struct SuperStar *star,int age); 

int makeUp(int age);
#endif

