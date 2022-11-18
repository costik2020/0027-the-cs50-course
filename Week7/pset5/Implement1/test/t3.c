#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
int main (void)
{
char * string1;
string1=malloc(sizeof(char)*20);
strcpy(string1,"Dreams Work");
int n =strlen(string1);



for (int i=0;i<n;i++)
	{
	string1[i]=tolower(string1[i]);
	
	}

printf("%s \n",string1);	


return 0;
}
