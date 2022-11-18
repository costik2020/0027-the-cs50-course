#include"myLibrary.h"

int main(void)
{
printf("Please insert your personal password: \n");
char * myPassword=malloc(sizeof(char)*20);
scanf("%s",myPassword);

FILE* di=fopen("10MillPass.txt","r");
if (di==NULL)
	{
	printf("Can't open the file \n");
	return 1;
	}
char * word=malloc(sizeof(char)*30);	
while( fscanf(di,"%s",word) != EOF )
	{
	
	
	if (strcmp(word,myPassword)==0)
		{
		printf(" !!!! Your password is in Dictionary !!!!!! \n");
		return 1;
		}	
	
	
	}
printf(" NOT FOUND :) \n");	
fclose(di);
return 1;
}
