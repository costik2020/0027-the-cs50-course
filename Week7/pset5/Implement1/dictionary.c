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
    // convert the word to low case 
    char * lword=convertWord(word);
    node* current;
    current=list;
    while (!(current->nextNode==NULL))
    	{
    	
    	if (strcmp(lword,current->word)==0)
    		{
    		return true;
    		}
    	current=current->nextNode;	
    	}
    
    
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
	// count=0;
    FILE * dictP=fopen(dictionary,"r");
    if (dictP==NULL)
    	{
    	printf("Sorry could not open the dictionary file");
    	return false;
    	}
    
    char stringLine[LENGTH];
    // node * list;
    // node * head;
    node * current;
    list=malloc(sizeof(node));
    list->nextNode=NULL;
    // head=list;
    current=list;
    while(1)
    	{
    	if (!(feof(dictP)==0))
    		{
    		break;
    		}
    	count=count+1;
    	fscanf(dictP,"%s",stringLine);
    	strcpy(current->word,stringLine);
    	current->nextNode =malloc(sizeof(node));
    	current=current->nextNode;
    	
    	
    	
    	
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
    node*current;
    node* next;
    current =list;
    
    while (!(current->nextNode==NULL))
    	{
    	next=current->nextNode;
    	free(current);
    	current=next;
    	
    	}
    
    if (current->nextNode==NULL)
    	{
    	return true;
    	}
    return false;
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



















