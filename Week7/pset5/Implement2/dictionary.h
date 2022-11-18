/**
 * dictionary.h
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Declares a dictionary's functionality.
 */

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>


// maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45
#define HASH_SIZE 2000
// declare a linked list structure
typedef struct node
	{
	char word[LENGTH];
	struct node* nextNode;
	
	}node;
// declare the Hash Table full pointers to begining of linked lists or NULL	
node * hashTable[HASH_SIZE];	
// number of words in a dictionary
extern int count;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word);

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary);

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void);

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void);

//Return a the same index for the same pice of data 
int hashIndex(const char * str);

//Convert the word to all low case
char * convertWord(const char * word);



#endif // DICTIONARY_H
