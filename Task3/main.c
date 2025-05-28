#include "task3.h"

int main() {
    int** root;
    int n, m, k;
    readInput(&root, &n, &m, &k);
    int treeSize = (1 << (k + 1)) - 1;
    int*** tree = malloc(treeSize * sizeof(int**));
    tree[0] = allocateMatrix(n, m);
    copyMatrix(tree[0], root, n, m);
    for (int i = 0; i < (1 << k) - 1; i++) {
        int** original = allocateMatrix(n, m);
        copyMatrix(original, tree[i], n, m);
    
        int** left = allocateMatrix(n, m);
        int** right = allocateMatrix(n, m);
    
        copyMatrix(left, original, n, m);
        copyMatrix(right, original, n, m);
    
        applyRuleB(left, n, m);
        applyStandardRules(right, n, m);
    
        tree[2 * i + 1] = left;
        tree[2 * i + 2] = right;
    
        freeMatrix(original, n);
    }
    preorderWrite(tree, treeSize, n, m);
    for (int i = 0; i < treeSize; i++) freeMatrix(tree[i], n);
    free(tree);
    freeMatrix(root, n);
    return 0;
}