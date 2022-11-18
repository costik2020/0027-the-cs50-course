/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       

#include "helpers.h"
#include "myHeader.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
	{
	
	
	
	return biSearchRec(value,values,0,n-1) ;
	}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
	{
	int s=0;
	int locOf=0;
	int willSwap=0;

	for (int i=0-s;i<n;i++)
		{
		int min=values[i];
	
		for(int j=i;j<n;j++)
			{
			if (min>=values[j])
				{
				min=values[j];
				locOf=j;
				willSwap=1;
				}
			
			}
		// Swap
		if (willSwap==1)
			{
			swapInt(&values[i],&values[locOf]);
			}
	
		
		}
	
		
	return;
	}
