#include <stdio.h>
#include <stdlib.h>

int main () 
{
// get the height
char input[10];
int n;
do {

scanf("%s",input);
n=atoi(input);
}while ( (n<=0)||(n>23) );


int A=2; // represents # number
for (int i=0;i<n;i++)
	{
	// print rows ...
	//Print spaces first _
	for (int j=0,hold=(n+1)-(A+i);j<hold;j++)
		{
		printf(" ");
		}
	// Print # 
	for (int k=0;k<A+i;k++)
		{
		printf("#");
		}	
	printf("\n");
	}


return 0;
}
