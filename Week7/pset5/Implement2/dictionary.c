/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>

#include "dictionary.h"

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    int hi;
    char * lword = convertWord(word);
    hi=hashIndex(lword);
    if (hashTable[hi]==NULL)
    	{
    	return false;
    	}
    else
    	{
    	node * current;
    	current=hashTable[hi];
    	
    		
    	while(current !=NULL)
    		{
    		if (strcmp(lword,current->word)==0)
    			{
    			return true;
    			}
    		else
    			{
    			current=current->nextNode;
    			}	
    		}
    	}
    	
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
	// Initiate the Hash Table with NULL pointers
	for (int i=0;i<HASH_SIZE;i++)
		{
		hashTable[i]=NULL;
		}    
    FILE * dictP=fopen(dictionary,"r");
    if (dictP==NULL)
    	{
    	printf("Sorry could not open the dictionary file");
    	return false;
    	}
    
    while (feof(dictP)==0)
    	{
    	//word is an array but hashIndex accepts char * ... so se if it works
    	char* word;
    	word=malloc(sizeof(char)*LENGTH);
    	fscanf(dictP,"%s",word);
    	int hi=hashIndex(word);
    	// Insert the word in the hash table 
    	// count variable counts the number of words in the dictionary
    	if (hashTable[hi]==NULL)
    		{
    		node * list=malloc(sizeof(node));
    		strcpy(list->word,word);
    		list->nextNode=NULL;
    		hashTable[hi]=list;
    		count++;
    		}
    	else
    		{
    		node * list=malloc(sizeof(node));
    		strcpy(list->word,word);
    		list->nextNode=hashTable[hi];
    		hashTable[hi]=list; 
    		count++;
    		}	
    	}
    
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    
    return count;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    for (int i=0;i<HASH_SIZE;i++)
    	{
    	if (hashTable[i] != NULL)
    		{
    		node *current;
    		node *next;
    		current=hashTable[i];
    		next=current->nextNode;
    		while(next !=NULL)
    			{
    			free(current);
    			current=next;
    			next=current->nextNode;
    			}
    		
    		
    		
    		
    		}
    	
    	if (i==HASH_SIZE-1)
    		{
    		return true;
    		}	
    	}
    
    return false;
}

// Creates only the index where the value is stored in the hash table

int hashIndex(const char * str)
	{
	int sum = 0;
	
	
	for (int i =0;str[i] != '\0';i++)
		{
		sum=sum+str[i];
		}
	int hindex= sum % HASH_SIZE;
	return hindex;
	
	
	}

char * convertWord(const char * word)
	{
	char * string1;
	string1=malloc(sizeof(char)*LENGTH+1);
	strcpy(string1,word);
	int n =strlen(string1);



	for (int i=0;i<n;i++)
		{
		string1[i]=tolower(string1[i]);
	
		}

	
	return string1;
	}



















