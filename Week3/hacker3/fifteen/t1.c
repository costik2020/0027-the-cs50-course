#include "myHeader.h"

int main (void)
{
int arr[10][3][3];

// Fill the arry with 2d arrays ..
for (int i=0;i<10;i++)
	{
	for (int j=0;j<3;j++)
		{
		for (int k=0;k<3;k++)
			{
			arr[i][j][k]=i;
			}
		}
	}


// Print this fun small database
for (int i=0;i<10;i++)
	{
	for (int j=0;j<3;j++)
		{
		for (int k=0;k<3;k++)
			{
			printf("%d ",arr[i][j][k]);
			}
		printf("\n");
		}
		
	printf("\n");
	}



return 0;
}
