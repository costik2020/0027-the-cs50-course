#include "myLibrary.h"

int main (int argc,char* argv[])
{
// User input
char * key=malloc(sizeof(char)*50);
char * salt=malloc(sizeof(char)*3 );
// char * correctHash="50Bpa7n/23iug" ;
char * correctHash=malloc(sizeof(char)*20);
if (argc != 2)
	{
	printf("There is something wrrong with the argunets conunt \n");
	return 1;
	}
strcpy(correctHash,argv[1]);
if (strlen(correctHash) != 13)
	{
	printf("The hash lenght seems to be wrrong ! \n");
	return 1;
	}



//Take salt from correctHash
salt[0]=correctHash[0];
salt[1]=correctHash[1];
salt[2]='\0';

// Run through the dictionary

FILE * di=fopen("words","r");
char * str=malloc(sizeof(char)*50);
while(1)
	{
	int isEnd=fscanf(di,"%s",str);
	if (isEnd==EOF)
		break;
	strcpy(key,str);
	char * hash=malloc(sizeof(char)*20);
	hash=crypt(key,salt);
	if ( !(strcmp(hash,correctHash)) )
		{
		printf("Password found !!! \n");
		printf("Password is : %s \n",key);
	
		}	
	
	}





printf("...end...\n");
return 0;
}
