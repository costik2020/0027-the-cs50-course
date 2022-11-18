#include "myLibrary.h"


char bigL(char letter);

int main (void)
{
//User Input

char * name=malloc(sizeof(char));
scanf("%[^\n]s",name);
printf("\n");
int i=0;
while(!(name[i]=='\0'))
	{
	if (i==0)
		{
		printf("%c",bigL(name[i]) );
		}
	if (name[i-1]==' ')
		{
		printf("%c",bigL(name[i]) );
		}
	i++;			
	
	}

printf("\n");
return 0;
}

// Convert small to big letter
char bigL(char letter)
	{
	if (letter>='a')
		{
		char bL=letter-('a'-'A');
		return bL;
		}
	else
		{
		return letter;
		
		}
	
	
	}
	
