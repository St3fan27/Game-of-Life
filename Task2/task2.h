#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int row, col;
} CellChange;

typedef struct Node {
    CellChange* changes;
    int change_count;
    struct Node* next;
} Node;

typedef struct {
    Node* top;
} Stack;

void initialize(int rows, int cols, int grid[100][100], int initial_state[100][100]);
void nextGeneration(int rows, int cols, int grid[100][100]);
void copyGrid(int rows, int cols, int dest[100][100], int src[100][100]);
int countNeighbors(int rows, int cols, int grid[100][100], int x, int y);

Stack* createStack();
void push(Stack* stack, CellChange* changes, int count);
void destroyStack(Stack* stack);
CellChange* computeChanges(int rows, int cols, int prev[100][100], int curr[100][100], int* count);
void printStackToFile(Stack* stack, const char* filename);
