#include "myLibrary.h"

int main(void)
{
FILE * di=fopen("words","r");
char * str =malloc(sizeof(100));
while ( 1 )
	{
	int isEnd=fscanf(di,"%s",str);
	if(isEnd==EOF)
		break;
	printf("%s",str);
	printf("\n");
	} 

return 0;
}
