#include"myHeader.h"

int d=3;


void draw(int array[d][d]);
void copyNow(int arr1[d][d],int arr2[d][d]);
int main(void)
{
int a1[3][3]={
		{1,2,3},
		{4,5,6},
		{7,8,9}

		};
int a2[3][3]={
		{0,0,0},
		{0,0,0},
		{0,0,0}

		};



draw(a1);
draw(a2);		
copyNow(a2,a1);	

draw(a1);
draw(a2);	


return 0;
}


void draw(int array[d][d])
	{
		for (int i=0;i<d;i++)
			{
			for (int j=0;j<d;j++)
				{
				if (array[i][j]==99)
					{
					printf("__");
					}
				else
					{
					printf("%2d ",array[i][j]);
					}	
				
				}
			printf("\n");	
			printf("\n");
			}
		
	printf("///////////////////////////////// \n");
	}
	
	
void copyNow(int arr1[d][d],int arr2[d][d])
	{
	int temp[d*d];
	int it=0;
	// Copy values to an one dimentional temp array
	for(int i=0;i<d;i++)
		{
		for (int j=0;j<d;j++)
			{
			temp[it]=arr2[i][j];
			it++;
			}
		}
	// Copy values to the destination array(2d)
	it=0;
	for(int i=0;i<d;i++)
		{
		for (int j=0;j<d;j++)
			{
			 arr1[i][j]=temp[it];
			it++;
			}
		}
		
	}
	
	
		

