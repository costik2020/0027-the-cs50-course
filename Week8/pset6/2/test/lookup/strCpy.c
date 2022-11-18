#include<stdio.h>

int main (void)
{
char * path="WhoLikesCookies";
char ext[20];
ext[0]=path[0];
ext[1]=path[1];
ext[2]=path[2];
ext[3]='\0';

printf("%s \n",ext);



return 0;
}
