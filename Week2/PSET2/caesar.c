#include "myLibrary.h"

char encrypt(char p ,int key);

int main (int argc,char * argv[])
{
// User input
if (argc != 2)
	{
	printf("Hey !! too many/few arguments \n");
	return 1;
	}
int k= atoi(argv[1]); 	
char * plain=malloc(sizeof(char));
scanf("%[^\n]s",plain);

int length=strlen(plain);
for (int i=0;i<length;i++)
	{
	
	// Function that returns the encripted char
	
	printf("%c",encrypt(plain[i],k));
	}


printf("\n");
return 0;
}
// Function that returns the encripted char
char encrypt(char p ,int key)
	{
	if ( !(isalpha(p)) )
		{
		return p ;
		}
	int indexL=0;
	int calc=0;
	char cy;	
	// See big or small letter ?
	if (p >='a')
		{
		//Big
		indexL=p-'a';
		calc=(indexL+key)%26;
		cy='a'+calc;
		return cy;
		
		}
	else
		{
		//Small
		indexL=p-'A';
		calc=(indexL+key)%26;
		cy='A'+calc;
		return cy;
		}	
	
	
	}

