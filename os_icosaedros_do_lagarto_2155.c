// https://chatgpt.com/share/684e2fc0-7590-8002-8a60-89ca50cc7619

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define INF 1000000.0

#define N 7

double dist[N+1][N+1];

double dp[1 << N][N+1];
int pai[1 << N][N+1];

double menorCusto;
int ultimoVertice;

void caminhoHamiltoniano(int s) {
    int subcon, i, j;

    for (subcon = 1; subcon < (1 << N); subcon++)
        for (i = 1; i <= N; i++) {
            dp[subcon][i] = INF;
            pai[subcon][i] = -1;
        }

    for (i = 1; i <= N; i++) {
        if (i == s) continue;
        dp[1 << (i - 1)][i] = dist[s][i]; // 1 << (i - 1) traduz para o subcon que só pussui i
        pai[1 << (i - 1)][i] = s; // o pai de i no subcon é s
    }

    for (subcon = 1; subcon < (1 << N); subcon++)
        for (i = 1; i <= N; i++) {
            if (!(subcon & (1 << (i - 1)))) continue; // se i não está no subconjunto

            for (j = 1; j <= N; j++) {
                if (j == i || !(subcon & (1 << (j - 1)))) continue; // se j não está no subconjunto ou é igual a i

                int subconSemI = subcon ^ (1 << (i - 1)); // remove i do subconjunto
                double novoCusto = dp[subconSemI][j] + dist[j][i];

                if (novoCusto < dp[subcon][i]) {
                    dp[subcon][i] = novoCusto; // atualiza o custo mínimo
                    pai[subcon][i] = j; // atualiza o pai de i no subconjunto
                } else if (fabs(novoCusto - dp[subcon][i]) < 1e-9) { // empate de custo
                    if (j < pai[subcon][i] || pai[subcon][i] == -1) { // verifica ordem lexicográfica
                        pai[subcon][i] = j;
                    }
                }
            }
        }

        for (i = 1; i <= N; i++) {
            if (i == s) continue; // sem o vértice s
            double custo = dp[((1 << N) - 1) ^ (1 << (s - 1))][i] + dist[i][s]; // onde (1 << N) - 1 ^ (1 << (s - 1)) significa o subconjunto com todos os vértices menos uma máscara que tira o vértice s
            if (custo < menorCusto) {
                menorCusto = custo;
                ultimoVertice = i;
            } else if (fabs(custo - menorCusto) < 1e-9) {
                if (i < ultimoVertice || ultimoVertice == -1) {
                    ultimoVertice = i;
                }
            }
        }
}

void printaCaminho(int s, int ultimo, int subcon) {
    if (subcon == 0) {
        printf("%d->", s);
        return;
    }
    printaCaminho(s, pai[subcon][ultimo], subcon ^ (1 << (ultimo - 1)));
    printf("%d->", ultimo);
}

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
        menorCusto = INF;
        ultimoVertice = -1;

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

        caminhoHamiltoniano(4);

        printf("Caso %d:\n", k + 1);
        printaCaminho(4, ultimoVertice, ((1 << N) - 1) ^ (1 << (4 - 1)));
        printf("4: %.5f\n", menorCusto);
    }

    return 0;
}