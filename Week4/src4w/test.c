#include "myLibrary.h"
void what(int arr[]);
int main(void)
{

int numbers[5]={4,42,10,687,1};


printf("%d \n",numbers[0]);

what(numbers);

printf("%d \n",numbers[0]);





return 0;
}

void what(int arr[])
	{
	arr[0]=1000;
	return;
	}


///////////////////////////////////////////////////////////////////////////


//char * str =malloc(sizeof(char)*20);
//scanf("%[^\n]s",str);

/*
char * arraOfWord[10];
for (int i=0;i<2;i++)
	{
	arraOfWord[i]=GetString();

	
	}

for (int i=0;i<2;i++)
	{
	printf("%s \n",arraOfWord[i]);
	
	
	}

*/
