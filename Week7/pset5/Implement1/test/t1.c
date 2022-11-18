// Linked list of 10 elements
#include<stdio.h>
#include<stdlib.h>

typedef struct node
	{
	int val;
	struct node * nextAdress;	
	}node;


int main(void)
{
node * list;
list=malloc(sizeof(node));
(*list).nextAdress=NULL;

node * head=list;

int  n;
n=10;
for (int i=0;i<n;i++)
	{
	
	(*list).val=i;
	(*list).nextAdress=malloc(sizeof(node));
	list=(*list).nextAdress;

	}
list =head;	
node * curent=list;
while ((*curent).nextAdress != NULL)
	{
	printf("val= %d \n",(*curent).val);
	curent=(*curent).nextAdress;
	}

/*
int table[n];
for (int i=0 ;i<n;i++)
	{
	table[i]=i;
	}

for (int i=0;i<n;i++)
	{
	printf("%d \n",table[i]);
	}	
	
*/


return 0;
}
