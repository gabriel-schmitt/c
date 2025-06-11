// ACCEPTED!!!

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAXN 100
#define MAXM 100
#define MAXV 202
#define INF 1000000000

#define cont(i,j) F[j][i]
#define dir(i,j) (cap[i][j] - F[i][j])

int cap[MAXV][MAXV];
int F[MAXV][MAXV];
int visited[MAXV];

double gx[MAXN], gy[MAXN];
double hx[MAXM], hy[MAXM];

int n, m, s, v;
int S, T, V=MAXV;

double dist(double x1, double y1, double x2, double y2) {
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

void add_edge(int v, int w) {
    cap[v][w] = 1;
}

int dfs(int s, int t, int min) {
    visited[s] = 1;
    if (s == t) return min;
    int i;
    for (i = 0; i < MAXV; i++) {
        if (visited[i]) continue;
        int contrario = cont(s, i);
        int direto = dir(s, i);
        if (contrario || direto) {
            int maior = contrario < direto ? direto : contrario;
            int minaresta;
            if ((minaresta = dfs(i, t, maior < min ? maior : min))) {
                if (direto >= minaresta) F[s][i] += minaresta;
                else F[i][s] -= minaresta;
                return minaresta;
            }
        }
    }
    return 0;
}

int main() {
    while (scanf("%d %d %d %d", &n, &m, &s, &v) != EOF) {
        S = 0;
        T = 1;
        V = 2 + n + m;
        int g_offset = 2;
        int h_offset = 2 + n;

        memset(cap, 0, sizeof(cap));
        memset(F, 0, sizeof(F));

        int i;
        for (i = 0; i < n; i++)
            scanf("%lf %lf", &gx[i], &gy[i]);
        for (i = 0; i < m; i++)
            scanf("%lf %lf", &hx[i], &hy[i]);

        double max_dist = s * v;

        for (i = 0; i < n; i++)
            add_edge(S, g_offset + i);

        for (i = 0; i < m; i++)
            add_edge(h_offset + i, T);

        for (i = 0; i < n; i++) {
            int j;
            for (j = 0; j < m; j++) {
                if (dist(gx[i], gy[i], hx[j], hy[j]) <= max_dist) {
                    add_edge(g_offset + i, h_offset + j);
                }
            }
        }

        int escaped = 0;
        while (1) {
            memset(visited, 0, sizeof(visited));
            int flow = dfs(S, T, INF);
            if (flow == 0) break;
            escaped += flow;
        }
        printf("%d\n", n - escaped);
    }

    return 0;
}