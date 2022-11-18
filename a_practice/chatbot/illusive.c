#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main(void)
{


printf("\n");
char *message;
message=malloc(sizeof(char)*200);
printf("Me:");
scanf("%s",message);

printf("\n");
printf("Illusive :");
if (!strcmp(message,"hy"))
	{
	printf("hy you too sir \n");
	}
if (!strcmp(message,"quit"))
	{
	printf("bye\n");
	
	}
if (!strcmp(message,"whatispi"))
	{
	printf("pi is 3.1415\n");
	
	}			
		
	
if (!strcmp(message,"good"))
	{
	printf("good indeed sir\n");
	
	}	
if (!strcmp(message,"php"))
	{
	printf("php it is a server side programming language\n");
	
	}			
	
if (!strcmp(message,"limit"))
	{
	printf("Sky is the limit , there is no such thing as limit my Master\n");
	
	}	

return 0;
}
