#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
int main (void)
{
char * s1="nuts";
char s2[10]="nuts";

int n =strcmp(s1,s2);
printf("%d \n",n);



return 0;
}
