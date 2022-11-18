#include "myLibrary.h"

int main(void)
{
FILE * di=fopen("words","r");
while ( 1 )
	{
	char r= fgetc(di);
	if(r==EOF)
		break;
	printf("%c",r);
	} 

return 0;
}
