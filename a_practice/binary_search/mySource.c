#define _XOPEN_SOURCE

#include<unistd.h>
#include<crypt.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<time.h>
#include<stdbool.h>






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
bool biSearchIterate(int searchVal,int list[],int length)
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
































