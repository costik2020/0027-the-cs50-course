#define _XOPEN_SOURCE

#include<unistd.h>
#include<crypt.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

typedef char* string;




char* GetString(void)
	{
	char line[256];

   char * arg1=malloc(sizeof(char)*200);
   int isint;

   while (1) 
       {
		
		fgets(line, sizeof (line), stdin);
		isint = sscanf(line, "%[^\n]s",arg1);
		if (isint) break;

		printf("Retry: \n");
	  }
	
	return arg1;
	}
	







