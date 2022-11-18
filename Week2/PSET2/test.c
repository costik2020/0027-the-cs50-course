
#include "myLibrary.h"



int main (void)
{
char * kword="green";

int ikw=kword[0]-'a';
printf("%d \n",ikw);

for (int i=0;i<12;i++)
	{
	int c=i%strlen(kword);
	printf("%c \n",kword[c]);
	}



return 0;
}


