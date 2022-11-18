// I still need to improve the user input block ... doesn't detect letters :)
#include<stdio.h>
#include<math.h>

int main()
{
// Get the change in float
// User input
float iChange;
int change;
do 
	{
	scanf("%f",&iChange);
	// Convert it to integer
	iChange=iChange*100;
	change=ceilf(iChange);


	}while( (change>100)||(change<0) );

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
