#include <stdio.h>

int main(void)
{
int m,b;

do{
printf("minutes:");
scanf("%d",&m);

}while (m<=0);


b=m*12;
printf("bottles:%d  \n",b);







return 0;
}
