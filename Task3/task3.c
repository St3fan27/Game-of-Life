#include "task3.h"

int isValid(int x, int y, int n, int m) {
    return x >= 0 && x < n && y >= 0 && y < m;
}

int** allocateMatrix(int n, int m) {
    int** mat = malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) mat[i] = calloc(m, sizeof(int));
    return mat;
}

void freeMatrix(int** mat, int n) {
    for (int i = 0; i < n; i++) free(mat[i]);
    free(mat);
}

void copyMatrix(int** dest, int** src, int n, int m) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            dest[i][j] = src[i][j];
}

void readInput(int*** matrix, int* n, int* m, int* k) {
    FILE* f = fopen("input.txt", "r");
    int t;
    fscanf(f, "%d", &t);
    fscanf(f, "%d %d", n, m);
    fscanf(f, "%d", k);
    *matrix = allocateMatrix(*n, *m);
    fgetc(f);
    char line[256];
    for (int i = 0; i < *n; i++) {
        fgets(line, sizeof(line), f);
        int col = 0;
        for (int j = 0; line[j] && col < *m; j++) {
            if (line[j] == 'X' || line[j] == '+') {
                (*matrix)[i][col] = (line[j] == 'X');
                col++;
            }
        }
    }
    fclose(f);
}

void applyStandardRules(int** grid, int n, int m) {
    int** new_grid = allocateMatrix(n, m);
    int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int cnt = 0;
            for (int d = 0; d < 8; d++) {
                int ni = i + dx[d], nj = j + dy[d];
                if (isValid(ni, nj, n, m)) cnt += grid[ni][nj];
            }
            if (grid[i][j])
                new_grid[i][j] = (cnt == 2 || cnt == 3);
            else
                new_grid[i][j] = (cnt == 3);
        }
    }
    copyMatrix(grid, new_grid, n, m);
    freeMatrix(new_grid, n);
}

void applyRuleB(int** grid, int n, int m) {
    int** new_grid = allocateMatrix(n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int cnt = 0;
            if (i > 0 && j > 0) cnt += grid[i - 1][j - 1];
            if (i > 0) cnt += grid[i - 1][j];
            if (i > 0 && j < m - 1) cnt += grid[i - 1][j + 1];
            if (j > 0) cnt += grid[i][j - 1];
            if (j < m - 1) cnt += grid[i][j + 1];
            if (i < n - 1 && j > 0) cnt += grid[i + 1][j - 1];
            if (i < n - 1) cnt += grid[i + 1][j];
            if (i < n - 1 && j < m - 1) cnt += grid[i + 1][j + 1];
            if (grid[i][j] == 1)
                new_grid[i][j] = 1;
            else if (cnt == 2)
                new_grid[i][j] = 1;
            else
                new_grid[i][j] = 0;
        }
    }
    copyMatrix(grid, new_grid, n, m);
    freeMatrix(new_grid, n);
}

void preorderWrite(int*** tree, int treeSize, int n, int m) {
    FILE* out = fopen("output.txt", "w");
    for (int t = 0; t < treeSize; t++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                fputc(tree[t][i][j] ? 'X' : '+', out);
            }
            fputc('\n', out);
        }
        fputc('\n', out);
    }
    fclose(out);
}