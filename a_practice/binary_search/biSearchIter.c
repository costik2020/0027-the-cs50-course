#include"myHeader.h"


int main (void)
{
////   index  0 1 2 3 4 5 6  7  8  9
int list[10]={1,3,4,5,7,9,12,13,17,21};

if (biSearchRec(7,list,0,9))
	{
	printf("found \n");
	}
else
	{
	printf("NOT FOUND\n");
	}	




return 0;
}



















