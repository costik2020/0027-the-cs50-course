#include <stdio.h>
#include<stdlib.h>

int main (void)
{
// User input
//int n=40;
int n;
char * in=malloc(sizeof(char));
int completeInput=0;
while (completeInput==0)
	{
	printf("Height: \n");
	scanf("%s",in);
	n=atoi(in);
	if ((n>0)&&(n<=23))
		{
		completeInput=1;
		}
	}




printf("\n");
for (int i =1;i<=n;i++)
	{
	//Print the line
	for (int j=0;j<n-i;j++)
		{
		printf(" ");
		}
	for (int k=0;k<i;k++)
		{
		printf("#");
		}
	printf("  ");
	for (int k=0;k<i;k++)
		{
		printf("#");
		}
	for (int j=0;j<n-i;j++)
		{
		printf(" ");
		}
	printf("\n");			
		
	}


return 0;
}
