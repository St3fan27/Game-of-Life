#include "gameoflife.h"
#include <stdio.h>

int main() {
    int N, M, K;
    const char *input_filename = "input.txt";
    const char *output_filename = "output.txt";
    
    FILE *input_file = fopen(input_filename, "r");
    if (!input_file) 
    {
        perror("Error opening input file");
        return 1;
    }
    
    fscanf(input_file, "%d", &K);
    fscanf(input_file, "%d %d", &N, &M); 
    
    int **grid = createGrid(N, M);
    int **initial_state = createGrid(N, M);
    
    for (int i = 0; i < N; i++) 
    {
        for (int j = 0; j < M; j++) 
        {
            char c;
            fscanf(input_file, " %c", &c);
            if (c == 'X') 
                initial_state[i][j] = 1;
            else
                initial_state[i][j] = 0;
        }
    }
    fclose(input_file);
    
    FILE *output_file = fopen(output_filename, "w");
    if (!output_file) 
    {
        perror("Error opening output file");
        return 1;
    }
    
    initialize(grid, initial_state, N, M);
    display(grid, output_file, N, M);
    
    for (int gen = 1; gen <= K; gen++) 
    {
        fprintf(output_file, "\n");
        nextGeneration(grid, N, M);
        display(grid, output_file, N, M);
    }
    
    fclose(output_file);
    
    freeGrid(grid, N);
    freeGrid(initial_state, N);
    
    return 0;
}
