#include <stdio.h>
#include <string.h>
#include <stdbool.h>
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

return 0;
}








/**
 * Loads a file into memory dynamically allocated on heap.
 * Stores address thereof in *content and length thereof in *length.
 */
bool load(FILE* file, BYTE** content, size_t* length)
{
// careful here is one BYTE pointer and one FILE pointer , it may be a problem
// the function works but gives a little bit bigger sizes maybe because i use 512 block
*content=file;
int size=0;

    while (!feof(file))
    	{
    	char block[BYTES];
    	fread(block,BYTES,1,file);
    	size++;
    	}
    
  size=size*BYTES;
  if (size!=0)
  	{
  	*length=size;
  	return true;
  	}  
    
    
    return false;
}

