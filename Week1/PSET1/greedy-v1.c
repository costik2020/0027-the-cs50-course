
#include<stdio.h>
#include<math.h>
#include<stdlib.h>

int main()
{
// Get the change in float
// User input
char  iChange[10];
float iChangeF;
int change;
do 
	{
	printf("Input a float please : \n");
	scanf("%s",iChange);
	// Check if there are letters
	iChangeF=strtof(iChange,NULL);
	if ((iChangeF)==0.0 ){
		printf("Hey  !!! ");
	}
	else
		{
		
		iChangeF=iChangeF*100;
		change=ceilf(iChangeF);
		}
	// Convert it to integer
	
	


	}while( (change>100)||(change<=0) );

int coinCount=0;
// Test the coin and dispense it 
while(change>=25)
	{
	change=change-25;
	coinCount++;
	
	}
while(change>=10)
	{
	change=change-10;
	coinCount++;
	
	}
while(change>=5)
	{
	change=change-5;
	coinCount++;
	
	}	
while(change>=1)
	{
	change=change-1;
	coinCount++;
	
	}			

printf("%d \n",coinCount);

return 0;
}
