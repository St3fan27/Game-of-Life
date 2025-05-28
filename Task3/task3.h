#include <stdio.h>
#include <stdlib.h>

int isValid(int x, int y, int n, int m);
int** allocateMatrix(int n, int m);
void freeMatrix(int** mat, int n);
void readInput(int*** matrix, int* n, int* m, int* k);
void applyStandardRules(int** grid, int n, int m);
void applyRuleB(int** grid, int n, int m);
void copyMatrix(int** dest, int** src, int n, int m);
void preorderWrite(int*** tree, int treeSize, int n, int m);
