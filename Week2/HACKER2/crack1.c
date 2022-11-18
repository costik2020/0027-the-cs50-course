#include "myLibrary.h"

int check(char* s, char* correctHash, char* salt);
int dictionary(char* filename,char* correctHash,char* salt);

//Global variables

int main (int argc,char* argv[])
{
char * correctHash=malloc(sizeof(char)*20);
char * salt=malloc(sizeof(char)*3 );

// User input
//char * key=malloc(sizeof(char)*50);

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

// Run through the dictionary1
if(dictionary("words",correctHash,salt) == 1)
	return 1; 


// Trying 10 Million top common passwords list
if(dictionary("10MillPass.txt",correctHash,salt) == 1)
	return 1; 



//1000 Most common Passworrds
if(dictionary("1000MostCommon.txt",correctHash,salt) == 1)
	return 1;




printf("...Trying some numbers... \n");	
// Try some numbers only
for (long i=0;i<1000000000;i++)
	{
	char * kNr=malloc(sizeof(char)*12);
	sprintf(kNr,"%ld",i);
	int re= check(kNr,correctHash,salt);
	if (re==0)
		{
		return 1;
		}
	
	}
	





printf("...end...\n");
return 0;
}


// My check function that uses crypt()
int check(char* s, char* correctHash, char* salt)
	{
	printf("Trying ... %s \n",s);
	char * hash=malloc(sizeof(char)*20);
	hash=crypt(s,salt);
	if ( !(strcmp(hash,correctHash)) )
		{
		printf("Password found !!! \n");
		printf("Password is : %s \n",s);
		return 0;
		}
	
	
	return 1;
	}
	
// This function checks the dictionaries that i pass	
int dictionary(char* filename,char* correctHash,char* salt)
	{
	FILE * di=fopen(filename,"r"); 
	char * str=malloc(sizeof(char)*50);
	char * key=malloc(sizeof(char)*50);
	printf("...Trying dictionary... \n");
	while(1)
		{
		int isEnd=fscanf(di,"%s",str);
		if (isEnd==EOF)
			break;
		strcpy(key,str);
		int re=check(key,correctHash,salt);
		if (re==0)
			{
			return 1;
			}
	
		}

	fclose(di);
	
	
	return 0;
	}	











