
#include"myHeader.h"

int main(void)
{
int arr[2][3][3];


int matrix[3][3];


printf("arr is %p \n",arr);

printf("///////////////////////// \n");

// Fill the arry with 2d arrays ..
for (int i=0;i<2;i++)
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
for (int i=0;i<2;i++)
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
// copy to the matrix	
for (int j=0;j<3;j++)
		{
		for (int k=0;k<3;k++)
			{
			matrix[j][k]=arr[0][j][k];
			}
		
		}	
	
	
	
	
// Print one matrix
printf("This is a new 2d coppy from 3d Array \n");
for (int j=0;j<3;j++)
		{
		for (int k=0;k<3;k++)
			{
			printf("%d ",matrix[j][k]);
			}
		printf("\n");
		}


return 0;
}
