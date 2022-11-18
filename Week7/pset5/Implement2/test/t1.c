#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

#define HASH_SIZE 2000;
int main(void)
{
int sum = 0;
printf("Word to hash= \n");
char * str;
str=malloc(sizeof(char)*40);
scanf("%s",str);
for (int i =0;str[i] != '\0';i++)
	{
	sum=sum+str[i];
	}
int index= sum % HASH_SIZE;
printf("%d \n",index);	

return 0;
}
