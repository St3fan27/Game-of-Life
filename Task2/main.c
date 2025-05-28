#include "task2.h"

int main() {
    FILE* in = fopen("input.txt", "r");
    if (!in) {
        perror("Cannot open input file");
        return 1;
    }

    int T, N, M, K;
    fscanf(in, "%d", &T);
    fscanf(in, "%d %d", &N, &M);
    fscanf(in, "%d", &K);

    int initial[100][100];
    int grid[100][100];
    int prev[100][100];

    for (int i = 0; i < N; i++) {
        char buffer[110];
        fscanf(in, "%s", buffer);
        for (int j = 0; j < M; j++) {
            initial[i][j] = (buffer[j] == 'X') ? 1 : 0;
        }
    }
    fclose(in);

    Stack* stack = createStack();
    initialize(N, M, grid, initial);

    for (int k = 0; k < K; k++) {
        copyGrid(N, M, prev, grid);
        nextGeneration(N, M, grid);
        int count;
        CellChange* changes = computeChanges(N, M, prev, grid, &count);
        push(stack, changes, count);
        free(changes);
    }

    printStackToFile(stack, "output.txt");
    destroyStack(stack);
    return 0;
}
