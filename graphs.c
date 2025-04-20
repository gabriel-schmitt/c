#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 15

typedef int **Graph;

void printGraph(Graph G, int n) {
    int i, j;
    for (i=0;i<n;i++) {
        for (j=0;j<n;j++)
            printf("%d ", G[i][j]);
        printf("\n");
    }
}

Graph createGraph(int n) {
    Graph G = (Graph)malloc(n * sizeof(int *));
    int i;
    for (i=0;i<n;i++)
        G[i] = (int *)calloc(n, sizeof(int));

    return G;
}

void fillDirGraph(Graph G, int n, int range, int min) {
    int i,j;
    srand(time(NULL));
    for (i=0;i<n;i++)
        for (j=0;j<n;j++)
            G[i][j] = rand() % range + min;
}

void fillGraph(Graph G, int n, int range, int min) {
    int i,j;
    srand(time(NULL));
    for (i=0;i<n;i++) 
        for (j=i+1;j<n;j++)
            G[i][j] = G[j][i] = rand() % range + min;
}

int *bfs(Graph G, int n, int iv) {
    int level[n];
    int i;
    for (i=0;i<n;i++) level[i] = -1;
    int queue[n], head=0, tail=1;
    queue[0] = iv;
    level[iv] = 0;
    while(head < tail) {
        int v = queue[head++];
        printf("%d: ", v);
        for(i=0;i<n;i++)
            if (G[v][i] && level[i] == -1) {
                printf("%d ", i);
                level[i] = level[v] + 1;
                queue[tail++] = i;
            }
        printf("\n");
    }

    for (i=0;i<n;i++)
        if (level[i] != -1)
            break;
        return NULL;

    return level;
}

int connectedComponents(Graph G, int n, int iv) {
    int cc=0;

    if (bfs(G, n, iv) == NULL) return 0;

    cc++;

    int v = iv;

    while (1) {
        int *level = bfs(G, n, v);
        int i;
        for (i=0;i<n;i++) 
            if (level[i] == -1) { 
                cc++;
                v = i;
                continue;
            }
        break;
    }
}

int main() {
    Graph G = createGraph(N);

    fillGraph(G, N, 2, 0);

    printGraph(G, N);

    connectedComponents(G, N, 0);

    printf("\n\nFim do programa.");

    return 0;
}