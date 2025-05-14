// codigo de usuario: 825667
// Manutencao: 3044

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 400

int **G;
int level[TAM+1];
int low[TAM+1];

void globalVarInit(int n) {
    G = (int**)malloc(n*sizeof(int*));
    for (int i=1;i<n;i++) {
        G[i] = (int*)calloc(n, sizeof(int));
        level[i] = low[i] = -1;
    }
}

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

void dfs(int v, int lev, int n) {
    level[v] = lev;

    for (int i=1; i<n; i++)
        if (G[v][i] == 1 && level[i] == -1) {
            G[v][i] = 2;
            G[i][v] = 0;
            dfs(i, lev+1, n);
        }
}

int lowpt(int v, int n) {
    if (low[v] != -1) return low[v];
    
    low[v] = v;

    for (int i=1; i<n; i++) 
        if (G[v][i] == 2 && level[lowpt(i, n)] < level[low[v]]) 
            low[v] = low[i];
        else if (G[v][i] == 1 && level[i] < level[low[v]])
            low[v] = i;

    return low[v];
}

int main() {
    int M, N, caseIdx = 1;

    char *buffer = NULL;
    size_t size = 0;

    while(1) {
        scanf("%d %d", &N, &M);
        if(M == 0 && N == 0) break;

        globalVarInit(N+1);

        for (int i=0; i<M; i++) {
            int X, Y;
            scanf("%d %d", &X, &Y);

            G[X][Y] = G[Y][X] = 1;
        }

        dfs(1, 0, N+1);
        lowpt(1, N+1);

        int *art = (int*)malloc((N-2) * sizeof(int));
        int head = 0, tail = 0;
        for (int i=1; i<=N; i++) {
            if (level[i] != 0) {
                for (int j=1; j<=N; j++) {
                    if (G[i][j] == 2 && (low[j] == j || low[j] == i)) {
                        art[tail++] = i;
                        break;
                    }
                }
                continue;
            }

            int cont = 0;
            for (int j=1; j<=N; j++) {
                if (G[i][j] == 2) cont++;
                if (cont >= 2) {
                    art[tail++] = i;
                    break;
                }
            }
        }

        char output[1024];
        int offset = snprintf(output, sizeof(output), "Teste %d\n", caseIdx++);
        if (tail == 0) {
            offset += snprintf(output + offset, sizeof(output) - offset, "nenhum\n\n");
        } else {
            qsort(art, tail, sizeof(int), compare);
            while (head != tail) {
                offset += snprintf(output + offset, sizeof(output) - offset, "%d ", art[head++]);
            }
            offset += snprintf(output + offset, sizeof(output) - offset, "\n\n");
        }

        size_t newSize = size + offset + 1;
        buffer = (char*)realloc(buffer, newSize);
        strcpy(buffer + size, output);
        size = newSize - 1;

        free(art);
        free(G);
    }

    printf("%s", buffer);
    
    return 0;
}