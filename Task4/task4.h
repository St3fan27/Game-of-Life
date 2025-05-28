#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int row;
    int col;
} Coord;

int abs(int x);
int** allocateMatrix(int n, int m);
void freeMatrix(int** mat, int n);
void copyMatrix(int** dest, int** src, int n, int m);
void readInput(int*** matrix, int* n, int* m, int* k);
void applyStandardRules(int** grid, int n, int m);
void applyRuleB(int** grid, int n, int m);
int isNeighbor(Coord a, Coord b);
void dfs(int** adj, Coord* coords, int* visited, int* path, int depth, int* best_len, int* best_path, int total);
void markComponent(int node, int component_id, int* component, int** adj, int total);
void computeHamiltonianPaths(int*** tree, int treeSize, int n, int m);
