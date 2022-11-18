#define _XOPEN_SOURCE

#include<unistd.h>
#include<crypt.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<time.h>
#include<stdbool.h>
// FOR DEBUGING ...
int c_test=3;

int d;





// Implementation of CS50 GetString ... not acutal function but close to..
const int INT_MAX=2147483647;
char* GetString(void)
	{
	char line[256];

   char * arg1=malloc(sizeof(char)*200);
   int isint;

   while (1) 
       {
		
		fgets(line, sizeof (line), stdin);
		isint = sscanf(line, "%[^\n]s",arg1);
		if (isint) break;

		printf("Retry: \n");
	  }
	
	return arg1;
	}


// GetInt function
int GetInt(void)
	{
	char line[40];

   int arg1=0;
   int isint;

   while (1) 
       {
		
		fgets(line, sizeof (line), stdin);
		isint = sscanf(line, "%d",&arg1);
		// If there is no input just Enter
		if (isint == -1)
			{
			return INT_MAX;
			break;
			}
		if (isint==1)
			{
			break;
			}
			
			

		printf("Retry: \n");
	  }
	
	return arg1;
	}

		
// Swaps two integers values
void swapInt (int* a,int* b)
	{
	int aux= *a;
	*a= *b;
	*b= aux;
	return;
	}


// Does a binary search by recursion to a sorted list of numbers
// the function doesn't work
bool searchIntR(int list[],int searchVal ,int bi,int ei)
	{
	// indexes
	int mi=(bi+ei)/2;
	
	if (list[mi]==searchVal)
		{
		return true;
		}
	if (bi==ei)
		{
		return false;
		}
		
	if (searchVal>list[mi])
		{
		// Right
		return searchIntR(list,searchVal,mi+1,ei);
		}
	else
		{
		// Left
		return searchIntR(list,searchVal,bi,mi-1);
		}		
		
		
	
		
	
	
	
	
	return false;
	}


// Binary Search of integer array by iteration 
bool biSearchIter(int searchVal,int list[],int length)
	{	
	int lowi,highi,midi;
	lowi=0;
	highi=length-1;
	midi=(lowi+highi)/2;
	bool found=false;
	while (1)
		{
		if(searchVal==list[midi])
			{
			found=true;
			break;
			}
	
		if (lowi>=highi)
			{
			found=false;
			break;
			}	
	
		if (searchVal>list[midi])
			{
			lowi=midi+1;
			midi=(lowi+highi)/2;	
			}
		else if (searchVal<list[midi])
			{
			highi=midi-1;
			midi=(lowi+highi)/2;
			}
					
		}
	return found;

	}

// Binary Search of Integer array using Recursion 
// bi and ei are begining and end index 
bool biSearchRec(int searchVal,int arr[],int bi,int ei)
	{
	int mi=(bi+ei)/2;
	if (searchVal==arr[mi])
		{
		return true;
		}
	if (bi>=ei)
		{
		return false;
		}	
	if (searchVal>arr[mi])
		{
		return biSearchRec(searchVal,arr,mi+1,ei);
		}
	else if (searchVal<arr[mi])
		{
		return biSearchRec(searchVal,arr,bi,mi-1);
		}	
		
	
	
	return false;
	}

// A test function that can help me for debuging

void  debugTest(int arr[][c_test])
	{
	for (int i=0;i<d;i++)
			{
			for (int j=0;j<d;j++)
				{
				if (arr[i][j]==99)
					{
					printf("__");
					}
				else
					{
					printf("%2d ",arr[i][j]);
					}	
				
				}
			printf("\n");	
			printf("\n");
			}
		
	
	printf("//////////////////////////////////////////////////// \n");
	}

void  debugTest2(int arr[9][9])
	{
	for (int i=0;i<9;i++)
			{
			for (int j=0;j<9;j++)
				{
				if (arr[i][j]==99)
					{
					printf("__");
					}
				else
					{
					printf("%2d ",arr[i][j]);
					}	
				
				}
			printf("\n");	
			printf("\n");
			}
		
	
	printf("//////////////////////////////////////////////////// \n");
	sleep(1);
	}


// This function will add value n  to the queue
void enque(int n,int arr[10],int* front,int* rear)
	{
	
	// -1 means an empty queue
	if ((*front==-1) && (*rear==-1))
		{
		*front=*front+1;
		*rear=*rear+1;
		arr[*front]=n;
		}
	else if (*rear==10)
			{
			printf("Queue is full \n");
			}
		else	
			{
			*rear=*rear+1;
			arr[*rear]=n;
			}	
	return;
	}

//This func will return the element in front of the Queue

int dequeue(int arr[10],int* front,int* rear)
	{
	if ((*front==-1)&&(*rear==-1))
		{
		printf("Queue is empty !\n");
		return -1;
		}
	else
		{
		int value=arr[*front];
		*front=*front+1;
		return value;
		}	
	
	return -1;
	}

// Prints an Queue
void printQ(int arr[10],int* front,int* rear)
	{
	
	for (int i=*front;i<= *rear;i++)
		{
		printf("%d  ",arr[i]);
		}
	printf("\n");	
	return;
	}





























