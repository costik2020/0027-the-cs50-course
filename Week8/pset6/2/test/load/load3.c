#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>



typedef char BYTE;
// number of bytes for buffers
//#define BYTES 512

bool load(FILE* file, BYTE** content, size_t* length);

int main(void)
{
BYTE* content;
size_t length;
content=NULL;
length=0;
// Open the pipe 
//FILE* file;
//file=fopen ("hello.php","r");
char command[]="ls -l";
FILE* file =popen (command,"r");



if (file==NULL)
	{
	printf("File doesn't exist \n");
	return 1;
	}

// Open the return from popen
/*
printf("Result: \n");
char c =fgetc(file);
while (c != EOF )
	{
	
	printf("%c",c);
	c =fgetc(file);
	}

*/






//Call to load



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

size_t size=0;
FILE* pf=file;
if (pf==NULL)
	{
	printf("File is NULL \n");
	return  false;
	}

char* storebytes;
//BYTE is 8 bits
char buffer;
int nrOfItems=0;
while (true)
	{
	// Read 8 bits into the buffer from the file
	nrOfItems=fread(&buffer,sizeof(BYTE),1,pf);
	
	//Check for file read errors
	if (ferror(pf) !=0 )
		{
		if (storebytes != NULL)
			{
			free(storebytes);
			storebytes=NULL;
			}
		return false;
		}
	//If you read something add the buffer into the array of bytes
	if (nrOfItems > 0)
		{
		storebytes=realloc(storebytes,size+nrOfItems);
		if (storebytes==NULL)
			{
			printf("Something went wrrong with memory reallocation \n");
			return false;
			}
		// i think is a bug here memcpy(body + size, buffer, octets); old server
		//I think storebytes+size is pointer arithmetic to not overwrritet
		//But to copy at the end of the storebytes array somehow
		memcpy(storebytes+size,&buffer,nrOfItems);
		size=size + nrOfItems;
		}
	
	//Check for end of file
	if (feof(pf) !=0)
		{
		break;
		}
		
		
	}



//"Return" the location of the string
*content=storebytes;

// "Return" length of the string in memory   
  if (size!=0)
  	{
  	*length=size;
  	return true;
  	}  
    
    
    return false;
}

