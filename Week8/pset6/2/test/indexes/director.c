#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>



int main (void)
{
DIR* pdir;
// Or i can use . notation to express the current directory
pdir=opendir(".");
if (pdir==NULL)
	{
	printf("Unable to open the directory pointer \n");
	return 1;
	}

printf("Files in curent DIRECTORY are : \n");
struct dirent *sdirectories;

while ((sdirectories=readdir(pdir) )!= NULL   )
	{
	printf("%s  \n",sdirectories->d_name);
	
	
	
	}



return 0;
}
