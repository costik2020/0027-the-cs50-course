//CHALANGE: The largest world in a string
// There is still alot of work to be done to make this work  
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int string_length( char * word );

int main(void){
printf("Please insert a string: \n");
char st[30];
scanf("%[^\n]s",st);
// Add a space to the end of imput
int stLength=string_length(st);
st[stLength+1]=' ';




char* pWord;
pWord= malloc(sizeof(char)*10) ;
int pwLength=0;//it will allways stay 0
char* cWord;
cWord= malloc(sizeof(char)*10) ;
int cwLength=0;

int i =0;
while (st[i] !='\0')
	{
	
	if (st[i] !=' ')
		{
		 
		cWord[cwLength]=st[i]; //HERE !! 2
		cwLength++;
		
		} 
		else if (cwLength > pwLength )
		{
		
		
		cWord[i+1]='\0';
		pWord= malloc(sizeof(char)*10) ; 
		strcpy(pWord,cWord);
		pwLength = string_length(pWord);
		cWord=malloc(sizeof(char)*10) ; // AFTER RESETS HERE 1
		cwLength=0;
		
		} 
			
	i++;
	
	}

printf("\n");
printf("The longest word is : %s with a length of %d",pWord,pwLength+1);
printf("\n");
}

int string_length( char * word )
	{
	int length;
	
	for(int i=0;word[i] !='\0';i++)
		{
		length=i;
	
		}

	
	
	return length;
	//off by one
	
	}

//bla bla bla 
