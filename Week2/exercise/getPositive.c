#include<stdio.h>

int getPossitive(void);

int main(void)
{
int n;
n= getPossitive();
printf("\n %d \n",n);

return 0;
}
int getPossitive(void)
	{
	int nr;
	
	do 
		{
		printf("\n nr=");
		scanf("%d",&nr);
		}
	while (nr <0);
	
	
	return nr;
	}
