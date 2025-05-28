#include "task4.h"

int abs(int x) { return x < 0 ? -x : x; }

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
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int cnt = 0;
            for (int a = -1; a <= 1; a++) {
                for (int b = -1; b <= 1; b++) {
                    if (a == 0 && b == 0) continue;
                    int ni = i + a, nj = j + b;
                    if (ni >= 0 && ni < n && nj >= 0 && nj < m)
                        cnt += grid[ni][nj];
                }
            }
            if (grid[i][j]) new_grid[i][j] = (cnt == 2 || cnt == 3);
            else new_grid[i][j] = (cnt == 3);
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

int isNeighbor(Coord a, Coord b) {
    return abs(a.row - b.row) <= 1 && abs(a.col - b.col) <= 1 && (a.row != b.row || a.col != b.col);
}

void dfs(int** adj, Coord* coords, int* visited, int* path, int depth, int* best_len, int* best_path, int total) {
    if (depth > *best_len) {
        *best_len = depth;
        for (int i = 0; i <= depth; i++) best_path[i] = path[i];
    }
    for (int i = 0; i < total; i++) {
        if (!visited[i] && adj[path[depth]][i]) {
            visited[i] = 1;
            path[depth + 1] = i;
            dfs(adj, coords, visited, path, depth + 1, best_len, best_path, total);
            visited[i] = 0;
        }
    }
}

void markComponent(int node, int component_id, int* component, int** adj, int total) {
    component[node] = component_id;
    for (int i = 0; i < total; i++) {
        if (adj[node][i] && component[i] == -1)
            markComponent(i, component_id, component, adj, total);
    }
}

void computeHamiltonianPaths(int*** tree, int treeSize, int n, int m) {
    FILE* out = fopen("output.txt", "w");
    for (int t = 0; t < treeSize; t++) {
        Coord coords[n * m];
        int idx = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (tree[t][i][j]) {
                    coords[idx].row = i;
                    coords[idx].col = j;
                    idx++;
                }
            }
        }
        int total = idx;
        if (total == 0) {
            fprintf(out, "-1\n");
            continue;
        }
        int** adj = malloc(total * sizeof(int*));
        for (int i = 0; i < total; i++) adj[i] = calloc(total, sizeof(int));
        for (int i = 0; i < total; i++) {
            for (int j = 0; j < total; j++) {
                if (isNeighbor(coords[i], coords[j])) {
                    adj[i][j] = 1;
                }
            }
        }
        int component[total];
        for (int i = 0; i < total; i++) component[i] = -1;
        int component_id = 0;
        for (int i = 0; i < total; i++) {
            if (component[i] == -1) {
                markComponent(i, component_id, component, adj, total);
                component_id++;
            }
        }
        int printed = 0;
        for (int c = 0; c < component_id; c++) {
            int map[total];
            int rev[total];
            int count = 0;
            for (int i = 0; i < total; i++) {
                if (component[i] == c) {
                    map[count] = i;
                    rev[i] = count;
                    count++;
                }
            }
            int** subadj = malloc(count * sizeof(int*));
            for (int i = 0; i < count; i++) subadj[i] = calloc(count, sizeof(int));
            for (int i = 0; i < count; i++) {
                for (int j = 0; j < count; j++) {
                    if (adj[map[i]][map[j]]) subadj[i][j] = 1;
                }
            }
            int best_len = -1;
            int path[count + 1], best_path[count + 1];
            int visited[count];
            for (int i = 0; i < count; i++) {
                for (int j = 0; j < count; j++) visited[j] = 0;
                visited[i] = 1;
                path[0] = i;
                dfs(subadj, coords, visited, path, 0, &best_len, best_path, count);
            }
            if (best_len == count - 1) {
                fprintf(out, "%d\n", best_len);
                for (int i = 0; i <= best_len; i++) {
                    int r = coords[map[best_path[i]]].row;
                    int c = coords[map[best_path[i]]].col;
                    fprintf(out, "(%d,%d)%s", r, c, (i == best_len ? "\n" : " "));
                }
                printed = 1;
                break;
            }
            for (int i = 0; i < count; i++) free(subadj[i]);
            free(subadj);
        }
        if (!printed) fprintf(out, "-1\n");
        for (int i = 0; i < total; i++) free(adj[i]);
        free(adj);
    }
    fclose(out);
}
