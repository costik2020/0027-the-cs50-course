#include "myHeader.h"

typedef struct 
{
	int nr;
	char * sentence;
	
	
}
block;

void modifyStruct(block* mody );
int main(void)
{
block t;

t.nr=1;
t.sentence="Hey look !!";
modifyStruct(&t);

printf(" %d  %s ",t.nr ,t.sentence);




return 0;
}

void modifyStruct(block* mody )
	{
	mody->nr=42;
	mody->sentence="I am that bear.. ";
	
	}
