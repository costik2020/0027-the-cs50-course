#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>


int main(void)
{
FILE* pf;
pf=fopen ("hello.php","r");

while (feof(pf)==0)
	{
	printf("%c",fgetc(pf));
	
	}
//clearerr(pf);
fseek(pf,0,SEEK_SET);	
while (feof(pf)==0)
	{
	printf("%c",fgetc(pf));
	}	

fclose(pf);
// test assignement string 
char query[10];
// you CAN'T do that:  query='f';
char c1='\0';
strncat(query,&c1,1);
//strcpy(query,'f');

printf("\n\nquery=%s \n",query);



return 0;
}
