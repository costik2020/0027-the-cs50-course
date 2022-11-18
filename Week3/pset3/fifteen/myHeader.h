// #define _XOPEN_SOURCE

#include<unistd.h>
#include<crypt.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<time.h>
#include<stdbool.h>




typedef char* string;


extern const int INT_MAX;


//My useful functions
char* GetString(void);
int GetInt(void);
void swapInt(int* a,int* b);
bool searchIntR(int list[],int searchVal ,int beginIndex,int endIndex);
bool biSearchIter(int searchVal,int list[],int length);
bool biSearchRec(int searchVal,int arr[],int bi,int ei);
