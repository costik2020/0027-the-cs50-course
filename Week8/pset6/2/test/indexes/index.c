#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

char* indexes(const char* path);

int main (void)
{

//  A path  /home/zen101/CS50/Week8/pset6/2/test/indexes
// Another path  /home/zen101/CS50/Week8/pset6/2/public/test
const char* path="/home/zen101/CS50/Week8/pset6/2/test/indexes";
char* returnpath=indexes(path);
printf("newpath=%s \n",returnpath);

return 0;
}










char* indexes(const char* path)
{
// I hard coded 200 in malloc () to alocate memory for newpath


DIR* pdir;
// Or i can use . notation to express the current directory
pdir=opendir(path);
if (pdir==NULL)
	{
	printf("Unable to open the directory pointer \n");
	return NULL;
	}


struct dirent *sdirectories;

while ((sdirectories=readdir(pdir) )!= NULL   )
	{
	// printf("%s  \n",sdirectories->d_name);
	// ((strcmp(name,"index.php")==0)
	char name[50];
	strcpy(name,sdirectories->d_name);
	if (strcmp(name,"index.html")==0)                        
		{
		char* newpath=malloc(sizeof(char)*200);
		strcat(newpath,path);
		strcat(newpath,"/index.html");
		return newpath;
		}
		else if  (strcmp(name,"index.php")==0)
		{
		char* newpath=malloc(sizeof(char)*200);
		strcat(newpath,path);
		strcat(newpath,"/index.php");
		return newpath;
		}
	
	
	}


    
    
    
    
    return NULL;
}





