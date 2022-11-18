#include <stdio.h>
#include <string.h>



int main(void)
{
printf("Pointer !!! :) \n");

char c1='a';
printf("  \n");
printf("c1= %c \n",c1);
printf("c1 %p  \n",&c1);

printf("/////////////  \n");
char * c2="abcd";
printf("c2= %s \n",c2 );
printf("c2= %p \n",c2 );
printf("c2= %c \n",*c2 );

printf("/////////////  \n");
int nr1=42;
printf("nr1=%d  \n",nr1);
printf("nr1=%p  \n",&nr1);

printf("/////////////  \n");
int * nr2= &nr1;
printf("nr2=%p  \n",nr2);
printf("nr2=%d  \n",*nr2);




printf("/////////// \n");
// Returns the size in Bytes
printf("sizeof(int) = %lu Bytes  \n", sizeof(int));
printf("sizeof(int*) = %lu Bytes  \n", sizeof(int*));
printf("sizeof(char) = %lu Bytes  \n", sizeof(char));
printf("sizeof(char*) = %lu Bytes  \n", sizeof(char*));
printf("sizeof(long unsigned) = %lu Bytes  \n", sizeof(long unsigned));
printf("sizeof(size_t) = %lu Bytes  \n", sizeof(size_t));
printf("sizeof(FILE*) = %lu Bytes  \n", sizeof(FILE*));

printf("/////////////  \n");
// What is going on here ?
//int ** nr3=&nr2;
int ** nr3 ;
nr3=&nr2;
printf("nr3=%p  \n",nr3);
printf("nr3=%d  \n",**nr3);

printf("/////////////  \n");
int *** nr4;
nr4=&nr3;
printf("nr4=%p  \n",nr4);
printf("nr4=%d  \n",***nr4);
printf("/////////////  \n");

int x=5;
int *p;
p=&x;
*p=6;
int ** q;
q=&p;
int*** r=&q; 


printf("  =%d  \n",*p);
printf("  =%p  \n",*q);
printf("  =%d  \n",**q);




return 0;
}
