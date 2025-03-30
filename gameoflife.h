#include <stdio.h>
#include <stdlib.h>

void initialize(int **grid, int **initial_state, int N, int M);
void display(int **grid, FILE *file, int N, int M);
void nextGeneration(int **grid, int N, int M);
int countNeighbors(int **grid, int x, int y, int N, int M);
void readInitialState(int **grid, const char *filename, int N, int M);
void writeGridToFile(int **grid, const char *filename, int N, int M);
int** createGrid(int N, int M);
void freeGrid(int **grid, int N);
