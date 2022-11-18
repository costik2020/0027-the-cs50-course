#include "myLibrary.h"

char encrypt(char p ,int key);

int main (int argc,char* argv[])
{
// User input
if (argc != 2)
	{
	printf("Hey ! you MUST enter 2 arguments please \n");
	return 1;
	}
char * keyWord=argv[1];
int lenKeyWord=strlen(keyWord);
for (int i=0;i<lenKeyWord;i++)
	{
	if( !(isalpha(keyWord[i])) )
		{
		printf("Your keyword is not good ! \n");
		return 1;
		}
	if (keyWord[i]<'a')
		{
		printf("You have to use small letters for keyword \n");
		return 1;
		}	
	}

printf("Enter the string: \n");
char * plain=malloc(sizeof(char));
scanf("%[^\n]s",plain);

// Loop throug the big string
int si=0;
for (int i=0;i<strlen(plain);i++)
	{
	if (isalpha(plain[i]))
		{
		if (i !=0)
			{
			si++;
			}
		int keyWordPlace=si%strlen(keyWord);
		int keyWordPlaceIndex=keyWord[keyWordPlace] - 'a';
		char c = encrypt(plain[i],keyWordPlaceIndex);
		printf("%c",c);	
		}
	else
		{
		
		printf("%c",plain[i]);	
		}
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

