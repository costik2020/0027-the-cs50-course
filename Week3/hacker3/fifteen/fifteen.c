/**
 * fifteen.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

//#include"myHeader.h"
#include"helper.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>






int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();
    
    AutoMix(6);
    

	
    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = GetInt();
        
        // God mod implementation
        if (tile==99)
        	{
        	
        	// THE BUG IS IN THE copyNow() temporar fix with 3 everywhere
        	copyNow(copyb,board);
        	// prevTile is the previus tile that i touced therefore i 
        	//Can't move it again 
        	int prevTile=600;
        	//int prevTileBranch=500;
        	branchW=777;
        	while(1)
        		{
        		// Check for winning
        		if (won())
        			{
        			printf("you win \n");
        			break;
        			}
        		if (branchW==0)
    				{
    				printf("You solve");
    				break;
    				}		
        		// Quich and dirty check if i am at first step in loop
        		if (branchW==777)
        			{
        			okToMove();       			
        			}
        		else 
        			{
        			//popQue is going to return me the next matrix to be 
        			//calculated in my Que
        			
        			dequeue();
        			prevTile=dequeue_PrNr();
        			copyNow(branchA,deqRes);
        			
        			copyNow(board,branchA);
        			okToMove();
        			copyNow(copyb,branchA);
        			
        			}	
        		
        		
        		
        		
        		for(int o=0;o<okLength;o++)
        			{
        			
        			copyNow(board,copyb);
        			
        			// prevTile shows 500 something is a BUG ...
        			if (!(ok[o]==prevTile) )
        				{
        				move(ok[o],board);
        				int result =countWrrong(board);
        				
        				// I will take a copy of the board in a que dataset 
        				copyNow(branchA,board);
        				
        				enqueue(branchA);
        				enqueue_PrNr(ok[o]);
        				branchW=result;
        				printQ();
        				}
        			if (branchW==0)
        				{
        				printf("You solve");
        				break;
        				}	
        			}
        		}
        			
        	
        	
        	}

        // move if possible, else report illegality
        if (!move(tile,board))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }

    // success
    return 0;
}
























 
















