#include <stdio.h>
#include<string.h>

struct Stud
	{
	char name[20];
	int age;
	char subject[30];
	
	
	};


int main (void)
{
struct Stud person;

strcpy(person.name,"Joe");
person.age=25;
strcpy(person.subject,"Social Science");

printf("%s \n",person.name);
printf("%d \n",person.age);
printf("%s \n",person.subject);


return 0;
}
