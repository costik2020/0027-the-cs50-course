#include<stdio.h>
#include<stdlib.h>
#include<string.h>


char* lookup(char* path);

int main (void)
{
char * path="gedit /home/zen101/CS50/Week8/pset6/2/public/cat.css";
printf("\n");


printf("%s \n",path);

char * test=lookup(path);
printf("%s \n",test);



return 0;
}





char* lookup(char* path)
	{
	// Find extension inside path
	char ext[10];
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
		
	//Return the answer based on extension it finds
	char * A_edata[8]={"css","html","gif","ico","jpg","js","php","png"};
	char * A_root[8]= {"text/css","text/html","image/gif","image/x-icon","image/jpeg","text/javascript","text/x-php","image/png"};

	for (int i=0;i<8;i++)
		{
		if (strcmp(ext,A_edata[i])==0)
			{
			char * answer;
			answer=malloc(sizeof(char)*20);
			strcpy(answer,A_root[i]);
			return answer;
			}
		}



	
	
	return NULL;
	}

