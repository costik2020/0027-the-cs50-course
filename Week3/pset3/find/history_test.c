#include"myHeader.h"

int main(void)
{
int arrNr[10]={8,12,15,20,22,34,38,41,47,50};

//Implement binary search

bool value =searchIntR(15,arrNr,0,9);
if (value)
	{
	printf("Found \n");
	}
else
	{
	printf("Not Found \n");
	}	


printf("\n");
	
// Print the sorted array

for (int i=0 ;i<10;i++)
	{
	printf("%d,",arrNr[i]);
	}
printf("\n");		
	
	
return 1;
}
/////////////////////////////////////////////////////////////////////////////////

