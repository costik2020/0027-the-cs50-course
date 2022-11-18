// Implement bubble sort :)
#include<stdio.h>

int main(void)
{
int arrNrs[]={1,32,5,76,3,976,6,65,43,75};
int length=10;
int swap=0;
int i=0;
while (1)
	{
	
	if (arrNrs[i]>arrNrs[i+1])
		{
		int aux =arrNrs[i];
		arrNrs[i]=arrNrs[i+1];
		arrNrs[i+1]=aux;
		swap++;		
		}
	i++;
	
	if ((i==length-1) && (swap==0))
		{
		printf("List sorted \n");
		break;
		}
	if (i==length-1)
		{
		i=0;
		swap=0;
		}  	
		
	}
for (int i ;i<length;i++)
	{
	printf("%d  ",arrNrs[i]);
	
	}


return 0;
}
