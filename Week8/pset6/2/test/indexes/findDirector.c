#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>



int main (void)
{
printf("What file do you want to find: \n");
char *nameFind;
nameFind=malloc(sizeof(char)*50);
scanf("%s",nameFind);

DIR* pdir;
// Or i can use . notation to express the current directory
pdir=opendir(".");
if (pdir==NULL)
	{
	printf("Unable to open the directory pointer \n");
	return 1;
	}


struct dirent *sdirectories;

while ((sdirectories=readdir(pdir) )!= NULL   )
	{
	// printf("%s  \n",sdirectories->d_name);
	char name[50];
	strcpy(name,sdirectories->d_name);
	if (strcmp(name,nameFind)==0)
		{
		printf("The file %s is in the directory \n",name);
		return 0;
		}
	
	
	}


printf("The is no such %s file in the director :( \n",nameFind);
return 0;
}
