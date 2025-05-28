#include "task2.h"

void initialize(int rows, int cols, int grid[100][100], int initial_state[100][100]) {
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            grid[i][j] = initial_state[i][j];
}

void copyGrid(int rows, int cols, int dest[100][100], int src[100][100]) {
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            dest[i][j] = src[i][j];
}

void nextGeneration(int rows, int cols, int grid[100][100]) {
    int new_grid[100][100];
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int neighbors = countNeighbors(rows, cols, grid, i, j);
            if (grid[i][j] == 1) {
                new_grid[i][j] = (neighbors == 2 || neighbors == 3) ? 1 : 0;
            } else {
                new_grid[i][j] = (neighbors == 3) ? 1 : 0;
            }
        }
    }
    copyGrid(rows, cols, grid, new_grid);
}

int countNeighbors(int rows, int cols, int grid[100][100], int x, int y) {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;
            int nx = x + i, ny = y + j;
            if (nx >= 0 && nx < rows && ny >= 0 && ny < cols)
                count += grid[nx][ny];
        }
    }
    return count;
}

Stack* createStack() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->top = NULL;
    return stack;
}

void push(Stack* stack, CellChange* changes, int count) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->changes = (CellChange*)malloc(count * sizeof(CellChange));
    for (int i = 0; i < count; i++)
        node->changes[i] = changes[i];
    node->change_count = count;
    node->next = stack->top;
    stack->top = node;
}

void destroyStack(Stack* stack) {
    Node* current = stack->top;
    while (current) {
        Node* temp = current;
        current = current->next;
        free(temp->changes);
        free(temp);
    }
    free(stack);
}

CellChange* computeChanges(int rows, int cols, int prev[100][100], int curr[100][100], int* count) {
    CellChange* changes = (CellChange*)malloc(rows * cols * sizeof(CellChange));
    *count = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (prev[i][j] != curr[i][j]) {
                changes[*count].row = i;
                changes[*count].col = j;
                (*count)++;
            }
        }
    }
    return changes;
}

void printStackToFile(Stack* stack, const char* filename) {
    FILE* out = fopen(filename, "w");
    if (!out) return;

    Stack* reverse = createStack();
    Node* current = stack->top;
    while (current) {
        push(reverse, current->changes, current->change_count);
        current = current->next;
    }

    current = reverse->top;
    int gen = 1;
    while (current) {
        for (int i = 0; i < current->change_count; i++) {
            fprintf(out, "%d %d %d\n", gen, current->changes[i].row, current->changes[i].col);
        }
        current = current->next;
        gen++;
    }

    destroyStack(reverse);
    fclose(out);
}
