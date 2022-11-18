#define _XOPEN_SOURCE 500

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<stdbool.h>

#include"helper.h"
//#include"myHeader.h"

// GLOBAL variables for queue
int d=3;
int s=3;
int q[QSIZE][QMAT][QMAT];

int front=-1;
int rear=-1;
// Queue Previous Numbers .... step
int qPrNr[SQSIZE];
int fpn=-1;
int rpn=-1;









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






/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    printf("For GOD mode input 99 \n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(void)
	{
	int sum=1;
		for (int i=0;i<d;i++)
			{
			for (int j=0;j<d;j++)
				{
				if(sum==d*d)
					{
					board[i][j]=99;
					break;
					}
				
				board[i][j]=sum;
				sum++;
				}
			}
	if (d%2 ==0)
		{
		swapInt(&board[d-1][d-1-2],&board[d-1][d-1-1]);
		}
	}

/**
 * Prints the board in its current state.
 */
void draw(void)
	{
		for (int i=0;i<d;i++)
			{
			for (int j=0;j<d;j++)
				{
				if (board[i][j]==99)
					{
					printf("__");
					}
				else
					{
					printf("%2d ",board[i][j]);
					}	
				
				}
			printf("\n");	
			printf("\n");
			}
		
	}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile,int arrNr[d][d])
	{
	int tl=0;
	int tc=0;
	bool found=false;
    // Find i and j of the tile
    for (int i=0;i<d;i++)
    	{
    	for (int j=0;j<d;j++)
    		{
    		if (tile==arrNr[i][j])
    			{
    			tl=i;
    			tc=j;
    			found=true;
    			break;
    			}
    		}
    	
    	}
    	
    if (!(found))
    	{ 
    	return false;
    	}
    	
    // Find i and j of the white space
    int sl=0;
    int sc=0;
    for (int i=0;i<d;i++)
    	{
    	for (int j=0;j<d;j++)
    		{
    		if (99==arrNr[i][j])
    			{
    			sl=i;
    			sc=j;
    			break;
    			}
    		}
    	
    	}
    // At this point i know where tail nr and space are
    // Tile is line neighbor with space
    if ( (tl==sl) && (abs(tc-sc)==1 ) )
    	{
    	swapInt(&arrNr[tl][tc],&arrNr[sl][sc]);
    	return true;
    	}
    // Tile is in collumn neighbour with space
    if ( (tc==sc)&&(abs(tl-sl)==1  ) )
    	{
    	swapInt(&arrNr[tl][tc],&arrNr[sl][sc]);
    	return true;
    	
    	}
    
    
    
    	return false;
	}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
	{	

		// Fill the array of check values 
		int length =d*d;
		int arrayCheck[length];
		int value=1;
		for (int i=0;i<length-1;i++)
			{
			arrayCheck[i]=value;
			value++;
			}
		arrayCheck[length-1]=99;
			
		int l=0;
		bool win=false;
		for (int i=0;i<d;i++)
			{
			for (int j=0;j<d;j++)
				{
				if ( !(board[i][j]==arrayCheck[l]))
					{
					return win;
					}
				l++;	
				}
			}
		
		win = true;
		return win;
	}


// Will mix the table by itself a n number of steps...
void AutoMix(int n)
	{
	int valPick[d*d-1];
	int val=1;
	for (int i=0;i<d*d-1;i++)
		{
		valPick[i]=val;
		val++;
		
		}
	// Move n times
	srand(time(NULL));
	for (int i=0;i<n;i++)
		{
		int rand_i=rand()%(d*d-1);
		while(1)
			{
			if   ( move(valPick[rand_i],board) )
				{
				break;
				}
			rand_i=rand()%(d*d-1);	 
			}
		
		}
	
	
	
	}

// First attempt to automaticaly solve the game of 
//fifteen puzzlo by random move works with n of 3 x 3
void godMode1()
	{
	int valPick[d*d-1];
	int val=1;
	for (int i=0;i<d*d-1;i++)
		{
		valPick[i]=val;
		val++;
		
		}
	// Move n times
	srand(time(NULL));
	while(1)
		{
		int rand_i=rand()%(d*d-1);
		while(1)
			{
			if   ( move(valPick[rand_i],board) )
				{
				if(won())
					{
					break;
					}
				
				}
			rand_i=rand()%(d*d-1);	 
			}
		if ( won())
			{
			break;
			}	
		
		}
	
	
	
	}


//Makes a copy of the board for ...
//arr1 is the destination arr2 is the source
void copyNow(int arr1[d][d],int arr2[d][d])
	{
	int temp[d*d];
	int it=0;
	// Copy values to an one dimentional temp array
	for(int i=0;i<d;i++)
		{
		for (int j=0;j<d;j++)
			{
			temp[it]=arr2[i][j];
			it++;
			}
		}
	// Copy values to the destination array(2d)
	it=0;
	for(int i=0;i<d;i++)
		{
		for (int j=0;j<d;j++)
			{
			 arr1[i][j]=temp[it];
			it++;
			}
		}
		
	}
	

// This function supose to affect ok[] array with the good number
void okToMove(void)
	{
	 	// Fill the array ok with check values around blank tile
		int length =d*d;
		int arrayCheck[length];
		int value=1;
		for (int i=0;i<length-1;i++)
			{
			arrayCheck[i]=value;
			value++;
			}
		arrayCheck[length-1]=99;
		
		// Now add to my ok array the llegal numbers
		okLength=0;
		 for (int i=0 ;i<length-1-1;i++)
		 	{
			int tile =arrayCheck[i];
			
			int tl=0;
			int tc=0;
			bool found=false;
			// Find i and j of the tile
			for (int i=0;i<d;i++)
				{
				for (int j=0;j<d;j++) //why j is 3 here ?
					{
					if (tile==board[i][j])
						{
						tl=i;
						tc=j;
						found=true;
						break;
						}
					}
			
				}
			
			if (!(found))
				{ 
				return;
				}
			
			// Find i and j of the white space
			int sl=0;
			int sc=0;
			for (int i=0;i<d;i++)
				{
				for (int j=0;j<d;j++)
					{
					if (99==board[i][j])
						{
						sl=i;
						sc=j;
						break;
						}
					}
			
				}
			// At this point i know where tail nr and space are
			// Tile is line neighbor with space
			
		   if ( (tl==sl) && (abs(tc-sc)==1 ) )
				{
				ok[okLength]=tile;
				okLength++;
				}
			// Tile is in collumn neighbour with space
			if ( (tc==sc)&&(abs(tl-sl)==1  ) )
				{
				ok[okLength]=tile;
				okLength++;
			
				}
    		
    			
		 	
		 	
		 	
		 	}
	
	
	}	

// This function will return how many tiles are in the wroong position 
// Including the space tile ... (the less the better ) for my algo

int countWrrong(int arr[][d])
	{
	// Fill the array of check values 
		int length =d*d;
		int arrayCheck[length];
		int value=1;
		for (int i=0;i<length-1;i++)
			{
			arrayCheck[i]=value;
			value++;
			}
		arrayCheck[length-1]=99;
			
		int l=0;
		// Count the tiles that are not in the right position
		int countW=0;
		for (int i=0;i<d;i++)
			{
			for (int j=0;j<d;j++)
				{
				if ( !(board[i][j]==arrayCheck[l]))
					{
					countW++;
					}
				l++;	
				}
			}
		
		
		return countW;
	
	
	}

///////////////////////////////////////////////////////////////////
///          QUEUE  FUNCTIONS DEFINITIONS      /////


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
	else if ( (rear+1)%QSIZE==front)
			{
			printf("Queue is full \n");
			printf("rear=%d \n",rear);
			}
		else	
			{
			rear=(rear+1)%QSIZE;
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
		
		 
		front=(front+1)%QSIZE;
		return  ;
		}	
	
	return ;
	}

// Prints an Queue
void printQ(void)
	{
	printf("//////////////////// \n");
	for (int i=front;i<= rear;i++)
		{
		
		int temp =front;
		front=i;
		copyFromQue();
		drawM(deqRes);		
		front=temp;
		}
	printf("//////////////////// \n");
	printf("\n");	
	return;
	}


void drawM(int array[d][d])
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
		
	printf(" \n");
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
	

// Previus number traking ... a second queue

// This function will add value n  to the queue
void enqueue_PrNr(int n)
	{
	
	// -1 means an empty queue
	//  (rear+1)%QSIZE==front
	if ((fpn==-1) && (rpn==-1))
		{
		fpn=fpn+1;
		rpn=rpn+1;
		qPrNr[fpn]=n;
		}
	else if ((rpn+1)%SQSIZE==fpn)
			{
			printf("Queue is full for PrNr \n");
			}
		else	
			{
			rpn=(rpn+1)%QSIZE;
			qPrNr[rpn]=n;
			}	
	return;
	}

//This func will return the element in front of the Queue

int dequeue_PrNr(void)
	{
	if ((fpn==-1)&&(rpn==-1))
		{
		printf("Queue is empty ! for PrNr\n");
		return -1;
		}
	else
		{
		int value=qPrNr[fpn];
		fpn=(fpn+1)%QSIZE;
		return value;
		}	
	
	return -1;
	}















