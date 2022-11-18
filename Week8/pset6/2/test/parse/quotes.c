#include<stdio.h>
#include<string.h>

int main(void)
{

int result= strcmp("\"","\"");
printf("result is %d \n",result);
printf("//////// \n");
printf("\"");
printf("//////// \n");
char* quote="ab\"c";

int i=0;
while (quote[i]!='\0')
	{
	printf("%c \n",quote[i]);
	if (quote[i]=='\"')
		{
		printf("True is a quote out there \n");		
		}
	i++;
	}

return 0;
}
