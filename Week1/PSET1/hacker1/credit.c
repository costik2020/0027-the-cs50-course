#include <stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>


void checkIssuer(int cnr[],int size);
//This global var will hold the Issuer name
char type[20];

int main (void)
{
long long input=0;

// User input
int userInput=0;
// Validate that i have an string of integers
char * strInp=malloc(sizeof(char));
while(userInput==0)
	{
	printf("Please enter the card nr: \n");
	scanf("%s",strInp);
	int i=0;
	while( !(strInp[i]=='\0') )
		{
		if (isdigit(strInp[i])==0)
			{
			userInput=0;
			printf("Retry \n");
			break;
			}
		 
		i++;	
		}
	
	if (strInp[i]=='\0')
		{
		userInput=1;
		}
	
	}
//Convert the string of integers to an actual long long integer nr	
if (userInput==1)
	{
	 int i=0;
	
	while ( !(strInp[i]=='\0') )
		{
		int di;
		di= (int)strInp[i]-'0';
		if (i==0)
			{
			input=di;
			}
		else
			{
			input=(input*10)+di;
			
			}
		i++;		
		} 
	
	
	}	




// long long input=378282246310005;

long long card_nr=input;
//Convert the long long to an array of numbers
// Find the length of the long number ...
int length=0;
while(card_nr != 0)
	{
	card_nr=card_nr /10;
	length++;
	
	}
// printf("%d \n",length);	
// Put the long long into and array of integers
int card[length];
card_nr=input;

for (int i=length-1;i>=0;i--)
	{
	card[i]=card_nr % 10;
	card_nr=card_nr / 10;
	
	}
// Just print the array
for (int i=0;i<length;i++)
	{
	printf("%d",card[i]);
	}
printf("\n");	
// My check function 
checkIssuer(card,length);
printf("%s \n",type);

if (strcmp(type,"INVALID")==0)
	{
	printf("The number is total invalid !!! \n");
	return 0;
	}
// Special math Luhn card formula

int product=1;
int total=0;
for(int i=1;i<length;i=i+2)
	{
	product=card[i]*2;
	if (product<10)
		{
		total=total +product;
		}
		else
			{
			total=total+product/10;
			total=total+product%10;
			}
	}
int sumS=0;
for(int i=0;i<length;i=i+2)
	{
	sumS=sumS+card[i];
	}
	
total=total + sumS;
if(total % 10==0)
	{
	printf("Card is legit :) \n");
	}
	else
		{
		printf("Card is NOT legit :( \n");
		}



return 0;
}


// Will put the name of the issuer in a global variable
void checkIssuer(int cnr[],int size)
	{
	if (  (cnr[0]==4) && ((size==13)||(size==16))  )
		{
		strcpy(type,"VISA");
		}
		else if (  (size==15)&&( cnr[0]==3)  )
			{
			if(   (cnr[1]==4) || (cnr[1]==7)   )
				{
				strcpy(type,"AMEX");
				}
			
			
			}
			else if (   (size==16) && (cnr[0]==5)   )
				{
				if (  (cnr[1]==1)||(cnr[1]==2)||(cnr[1]==3)||(cnr[1]==4)||(cnr[1]==5)  )
					{
					strcpy(type,"MASTERCARD");
					}
				
				}
				else
					{
					strcpy(type,"INVALID");
					}   
	
	
	
	return;
	}










