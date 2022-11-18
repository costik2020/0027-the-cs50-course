#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

typedef char BYTE;
// number of bytes for buffers
#define BYTES 512

bool load(FILE* file, BYTE** content, size_t* length);

int main(void)
{
BYTE* content;
size_t length;
content=NULL;
length=0;

FILE* file;
file=fopen ("hello.php","r");
if (file==NULL)
	{
	printf("File doesn't exist \n");
	return 1;
	}
load(file,&content,&length);
printf("content=%p \n",content);
printf("length=%lu Bytes\n",length);

printf("The file to a string is : \n");
printf("%s \n",content);	

return 0;
}








/**
 * Loads a file into memory dynamically allocated on heap.
 * Stores address thereof in *content and length thereof in *length.
 */
bool load(FILE* file, BYTE** content, size_t* length)
{

int size=0;
FILE* bufile=file;


// Find out how many Bytest does the file have
while (!feof(file))
	{
	
	fgetc(file);
	size++;
	
	
	}
// Reset the cursor at the begining of the file	
fseek(file,0,SEEK_SET);

char* storebyte=malloc(sizeof(char)*size+10);
//Loop again and store the byte array in the memory on the heap

while (!feof(file))
	{
	char c ;
	c=fgetc(file);
	// i need to concate char to the string 
	strncat(storebyte,&c,1);
	
	
	} 

//"Return" the locatioin of the string
*content=storebyte;
  
  if (size!=0)
  	{
  	*length=size;
  	return true;
  	}  
    
    
    return false;
}

