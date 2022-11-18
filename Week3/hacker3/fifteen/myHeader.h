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
extern int c_test;


//My useful functions
char* GetString(void);
int GetInt(void);
void swapInt(int* a,int* b);
bool searchIntR(int list[],int searchVal ,int beginIndex,int endIndex);
bool biSearchIter(int searchVal,int list[],int length);
bool biSearchRec(int searchVal,int arr[],int bi,int ei);
//Queue
// Hard coded the max size of queue
void enque(int n,int arr[10],int* front,int* rear);
int dequeue(int arr[10],int* front,int* rear);
void printQ(int arr[10],int* front,int* rear);

//DEBUG
void  debugTest(int arr[][c_test]);
void  debugTest2(int arr[9][9]);
