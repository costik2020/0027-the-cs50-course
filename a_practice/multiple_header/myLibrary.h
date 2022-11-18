#define _XOPEN_SOURCE

#include<unistd.h>
#include<crypt.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<time.h>
#include<stdbool.h>

typedef char* string;
const int INT_MAX=2147483647;

//////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


// Implementation of CS50 GetString ... not acutal function but close to..
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


// GetInt function
int GetInt(void)
	{
	char line[40];

   int arg1=0;
   int isint;

   while (1) 
       {
		
		fgets(line, sizeof (line), stdin);
		isint = sscanf(line, "%d",&arg1);
		// If there is no input just Enter
		if (isint == -1)
			{
			return INT_MAX;
			break;
			}
		if (isint==1)
			{
			break;
			}
			
			

		printf("Retry: \n");
	  }
	
	return arg1;
	}	







