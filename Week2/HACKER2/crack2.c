#include "myLibrary.h"

int check(char* s, char* correctHash, char* salt);
int dictionary(char* filename,char* correctHash,char* salt);
int addNumToWord(char* filename,char *correctHash,char*salt);

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


//Add numbers to dictionary
if(addNumToWord("10MillPass.txt",correctHash,salt) == 1)
	return 1; 



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
// Try some numbers only LAST OPTION
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

// Go through dictionary and add some numbers to the begining of the word
// And after take the word again and add numbers at the end of the same word
int addNumToWord(char* filename,char *correctHash,char*salt)
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
		// Here i add numbers to the word
		while(1)
			{
			//Add number befor the word
			for (int i=0; i<1000;i++)
				{
				printf("%c \n",str[0]);
				char* addNumber=malloc(sizeof(6));
				sprintf(addNumber,"%d",i);
				char* result=malloc(strlen(key)+strlen(addNumber)+1);
				strcpy(result,addNumber);
				strcat(result,key);
				
				int re=check(result,correctHash,salt);
				if (re==0)
					{
					return 1;
					}
				
				}
			
			//Add number after the word
			
			for (int i=0; i<1000;i++)
				{
				printf("%c \n",str[0]);
				char* addNumber=malloc(sizeof(6));
				sprintf(addNumber,"%d",i);
				char* result=malloc(strlen(key)+strlen(addNumber)+1);
				strcpy(result,key);
				strcat(result,addNumber);
				
				int re=check(result,correctHash,salt);
				if (re==0)
					{
					return 1;
					}
				
				}
			
			break; 
			
			}
		
		
	
		}

	fclose(di);
	
	
	return 0;
	}











