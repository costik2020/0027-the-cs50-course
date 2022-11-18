#include <stdio.h>

int myfunction (int var1,int var2 ,char * name);
int main (void)
{
printf("Test :) \n");
int var1=1;
int var2=2;
char * name="Rebeka";
printf("%s \n",name);

printf("%d \n",myfunction (10,var2,name));

return 0;
}

int myfunction (int var1,int var2 ,char * name)
{
return var1 + var2;
// return 999999;

}
