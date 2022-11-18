//CHALANGE: The largest world in a string 
#include<stdio.h>

int main(void){
printf("Please insert a string: \n");
char st[30];
scanf("%s",st);

char pWord[10];
pWord="a";
int pwLength=0;
char cWord[10];
cWord="a";
int cwLength=0;

int i =0;
while (st[i] !='\0')
	{
	if (st[i] !=' ')
		{
		cWord[cwLength]=st[i];
		cwLength++;
		
		} 
		else if (cwLength > pwLength )
		{
		pWord=cWord;
		cWord="a";
		cwLength=0;
		} 
			
	}

printf("\n");
printf("The longest word is : %s with a length of %d",pWord,pwLength+1);
}







