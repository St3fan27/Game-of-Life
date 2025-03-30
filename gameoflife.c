#include "gameoflife.h"
#include <stdlib.h>

void initialize(int **grid, int **initial_state, int N, int M) 
{
    for (int i = 0; i < N; i++) 
    {
        for (int j = 0; j < M; j++) 
        {
            grid[i][j] = initial_state[i][j];
        }
    }
}

void display(int **grid, FILE *file, int N, int M) 
{
    for (int i = 0; i < N; i++) 
    {
        for (int j = 0; j < M; j++) 
        {
            if (grid[i][j] == 1) 
                fprintf(file, "X ");
            else 
                fprintf(file, "+ ");
        }
        fprintf(file, "\n");
    }
}

void nextGeneration(int **grid, int N, int M) 
{
    int **new_grid = createGrid(N, M);
    for (int i = 0; i < N; i++) 
    {
        for (int j = 0; j < M; j++) 
        {
            int neighbors = countNeighbors(grid, i, j, N, M);
            if (grid[i][j] == 1) 
            {
                if (neighbors == 2 || neighbors == 3)
                    new_grid[i][j] = 1;
                else
                    new_grid[i][j] = 0;
            }
            else 
            {
                if (neighbors == 3)
                    new_grid[i][j] = 1;
                else
                    new_grid[i][j] = 0;
            }
        }
    }
    for (int i = 0; i < N; i++) 
    {
        for (int j = 0; j < M; j++) 
        {
            grid[i][j] = new_grid[i][j];
        }
    }
    freeGrid(new_grid, N);
}

int countNeighbors(int **grid, int x, int y, int N, int M) 
{
    int count = 0;
    for (int i = -1; i <= 1; i++) 
    {
        for (int j = -1; j <= 1; j++) 
        {
            if (i == 0 && j == 0) 
                continue;
            int nx = x + i, ny = y + j;
            if (nx >= 0 && nx < N && ny >= 0 && ny < M) 
                count += grid[nx][ny];
        }
    }
    return count;
}

void readInitialState(int **grid, const char *filename, int N, int M) 
{
    FILE *file = fopen(filename, "r");
    if (!file) 
    {
        perror("Error opening file");
        return;
    }

    for (int i = 0; i < N; i++) 
    {
        for (int j = 0; j < M; j++) 
        {
            char c;
            fscanf(file, " %c", &c);
            if (c == 'X') 
                grid[i][j] = 1;
            else 
                grid[i][j] = 0;
        }
    }

    fclose(file);
}

void writeGridToFile(int **grid, const char *filename, int N, int M) 
{
    FILE *file = fopen(filename, "w");
    if (!file) 
    {
        perror("Error opening file");
        return;
    }

    for (int i = 0; i < N; i++) 
    {
        for (int j = 0; j < M; j++) 
        {
            if (grid[i][j] == 1) 
                fprintf(file, "X ");
            else 
                fprintf(file, "+ ");
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

int** createGrid(int N, int M) 
{
    int **grid = (int **)malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++) 
        grid[i] = (int *)malloc(M * sizeof(int));
    return grid;
}

void freeGrid(int **grid, int N) 
{
    for (int i = 0; i < N; i++) 
        free(grid[i]);
    free(grid);
}
