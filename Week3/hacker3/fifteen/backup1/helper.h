


// constants
#define DIM_MIN 3
#define DIM_MAX 3

// board
int board[DIM_MAX][DIM_MAX];
int copyb[DIM_MAX][DIM_MAX];
int branchA[DIM_MAX][DIM_MAX];


//Array that holds the numbers that i can move
int ok[4];
int okLength;

// dimensions
int d;
int branchW;

// FOUND BUG copyb is the size DIM_MAX ... my copy function goes mad :)
// My functions



// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);
void AutoMix(int n);
void godMode1();
void copyNow(int arr1[d][d],int arr2[d][d]);
void okToMove(void);
int countWrrong(int arr[][d]);


