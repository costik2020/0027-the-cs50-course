#include<stdbool.h>
#include<time.h>

typedef char* string;
// constants
#define DIM_MIN 3
#define DIM_MAX 3
#define QMAT 3
#define QSIZE  10000
#define SQSIZE 10000

// board
int board[DIM_MAX][DIM_MAX];
int copyb[DIM_MAX][DIM_MAX];
int branchA[DIM_MAX][DIM_MAX];
int deqRes[3][3]; 





//Array that holds the numbers that i can move
int ok[4];
int okLength;

// dimensions
int d;
int branchW;
int extern s;



// Queue functions ...
void drawM(int arra[d][d]);
void printQ(void);
void copyToQue(int arr2[d][d]);
//copyFromQue puts its value in deqRes[][]
void copyFromQue(void); 
void enqueue(int arr[s][s]);
//dequeue() returns its value in deqRes[][] with the help of copyFromQue()
void dequeue(void);

// Second queue that traks my last nr step
void enqueue_PrNr(int n);
int dequeue_PrNr(void);


// FOUND BUG copyb is the size DIM_MAX ... my copy function goes mad :)
// My functions



// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile,int arrNr[d][d]);
bool won(void);
void AutoMix(int n);
void godMode1();
void copyNow(int arr1[d][d],int arr2[d][d]);
void okToMove(void);
int countWrrong(int arr[][d]);
char* GetString(void);
int GetInt(void);
void swapInt (int* a,int* b);


