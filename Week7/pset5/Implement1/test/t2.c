#include<stdio.h>

int main (void)
{
FILE* fp=fopen("small","r");
char word[20];
while (1)
	{
	if (!(0==feof(fp)))
		{
		break;
		}
	
	
	fscanf(fp,"%s",word);
	printf("%s \n",word);
	
	
	}



return 0;
}
