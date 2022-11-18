#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int main (void)
{
char * path="gedit /home/zen101/CS50/Week8/pset6/2/public/cat.html";
printf("\n");
char ext[10];

printf("%s \n",path);
int i=0;
while (path[i] != '\0')
	{
	
	
	
	if (path[i]=='.')
		{
		i++;
		int j=0;
		while(path[i] != '\0')
			{
			
			
			ext[j]=path[i];
			j++;
			i++;
			}
		ext[j]='\0';
		break;
		}
	i=i+1;
	}

char * root;
root= malloc(sizeof(char)*10);
char * edata="html";




if (strcmp(ext,edata) ==0)
	{
	
	
	strcpy(root,"text/");
	printf("%s%s \n",root,ext);
	}





return 0;
}
