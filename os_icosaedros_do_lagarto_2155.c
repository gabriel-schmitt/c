// https://chatgpt.com/share/684e2fc0-7590-8002-8a60-89ca50cc7619

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 7

double dist[N+1][N+1];

int dp[1 << N][N];
int pai[1 << N][N];

void caminhoHamiltoniano() {}

double calculate_distance(int coord1[2], int coord2[2]) {
    int dx = coord1[0] - coord2[0];
    int dy = coord1[1] - coord2[1];
    return sqrt(dx * dx + dy * dy);
}

int main() {
    int C;
    scanf("%d", &C);
    int k;
    for (k = 0; k < C; k++) {
        int coord[N+1][2];

        int X, Y;
        scanf("%d %d", &X, &Y);

        coord[4][0] = X;
        coord[4][1] = Y;

        int i;
        for (i = 0; i < N-1; i++) {
            int n, x, y;
            scanf("%d %d %d", &n, &x, &y);
            coord[n][0] = x;
            coord[n][1] = y;
        }
        
        for (i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                dist[i][j] = (i == j) ? 0 : calculate_distance(coord[i], coord[j]);
            }
        }

        caminhoHamiltoniano();
    }

    return 0;
}