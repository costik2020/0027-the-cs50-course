#include <stdio.h>
#include <string.h>

#define size 20

int main(void)
{

//int size=20;
char s1[size]="aaaaaaaaaaa";
char s2[size]="bbb";

printf("s1=%s \n",s1);
printf("s2=%s \n",s2);
printf("///////////////////// \n");

for (int i=0;i<size;i++)
	{
	s1[i]='\0';
	}

for (int i=0;i<3;i++){
  s1[i]=s2[i];
  
  
  

}
printf("s1=%s \n",s1);
printf("s2=%s \n",s2);

return 0;
}



