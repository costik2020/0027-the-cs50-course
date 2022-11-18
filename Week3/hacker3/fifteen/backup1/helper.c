#define _XOPEN_SOURCE 500

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<stdbool.h>

#include"helper.h"
#include"myHeader.h"








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
	int sum=d*d-1;
		for (int i=0;i<d;i++)
			{
			for (int j=0;j<d;j++)
				{
				if(sum==0)
					{
					board[i][j]=99;
					break;
					}
				
				board[i][j]=sum;
				sum--;
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
bool move(int tile)
	{
	int tl=0;
	int tc=0;
	bool found=false;
    // Find i and j of the tile
    for (int i=0;i<d;i++)
    	{
    	for (int j=0;j<d;j++)
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
    	return false;
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
    	swapInt(&board[tl][tc],&board[sl][sc]);
    	return true;
    	}
    // Tile is in collumn neighbour with space
    if ( (tc==sc)&&(abs(tl-sl)==1  ) )
    	{
    	swapInt(&board[tl][tc],&board[sl][sc]);
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
			if   ( move(valPick[rand_i]) )
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
			if   ( move(valPick[rand_i]) )
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

















