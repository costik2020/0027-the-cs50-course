#include <stdio.h>

int main () 
{
// get the height
int n;
scanf("%d",&n);
int A=2; // represents # number
for (int i=0;i<n;i++)
	{
	// print rows ...
	//Print spaces first _
	for (int j=0;j<(n+1)-(A+i);j++)
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
