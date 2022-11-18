#include<unistd.h>
#include<crypt.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<time.h>
#include<stdbool.h>

// GLOBAL variables
int d=3;
int s=3;
int const QMAX= 9;
int q[100000][QMAX][QMAX];
int front=-1;
int rear=-1;
int deqRes[3][3];

void draw(int arra[d][d]);
void printQ(void);
void copyToQue(int arr2[d][d]);
//copyFromQue puts its value in deqRes[][]
void copyFromQue(void); 




void enqueue(int arr[s][s]);
//dequeue() returns its value in deqRes[][] with the help of copyFromQue()
void dequeue(void);






int main(void)
{
// Queue
int input[3][3];

for (int i =0;i<10;i++)
	{
	for (int j=0;j<3;j++)
		{
		for(int k=0;k<3;k++)
			{
			input[j][k]=i;
			}
		}
	
	enqueue(input);
	}


printQ();



	


return 0;
}

// This function will add value n  to the queue
void enqueue(int arr[s][s])
	{
	
	// -1 means an empty queue
	if ((front==-1) && (rear==-1))
		{
		front=front+1;
		rear=rear+1;
		// add the matrinx n to the Queue
		copyToQue(arr);
		}
	else if (rear==10)
			{
			printf("Queue is full \n");
			}
		else	
			{
			rear=rear+1;
			copyToQue(arr);
			
			}	
	return;
	}

//This func will return the element in front of the Queue
// Will put the value in deqRes[][]

void dequeue()
	{
	if ((front==-1)&&(rear==-1))
		{
		printf("Queue is empty !\n");
		return ;
		}
	else
		{
		// arr[front][0][0];
		copyFromQue();
		
		 
		front=front+1;
		return  ;
		}	
	
	return ;
	}

// Prints an Queue
void printQ(void)
	{
	
	for (int i=front;i<= rear;i++)
		{
		
		int temp =front;
		front=i;
		copyFromQue();
		draw(deqRes);
		front=temp;
		}
	printf("\n");	
	return;
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
	
	
//Makes a copy of the board for ...
//arr1 is the destination arr2 is the source
void copyToQue(int arr2[d][d])
	{

	
	// Copy values to an one dimentional temp array
	for(int i=0;i<d;i++)
		{
		for (int j=0;j<d;j++)
			{
			q[rear][i][j]=arr2[i][j];
			}
		}
	
	
		
	}
	
	
	
void copyFromQue(void)	
{

	
	
	for(int i=0;i<d;i++)
		{
		for (int j=0;j<d;j++)
			{
			deqRes[i][j]=q[front][i][j];
			}
		}
	
	
		
	}
	























	

