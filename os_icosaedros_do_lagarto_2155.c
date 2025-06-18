// 825667

// Os Icosaedros do Lagarto - URI Online Judge 2155

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define INF 1000000.0

#define N 7

double dist[N+1][N+1];

double dp[1 << N][N+1];
int pai[1 << N][N+1];

// Adicione para armazenar o caminho parcial de cada estado
int caminhoDP[1 << N][N+1][N+1]; // [máscara][último][posição]
int tamCaminhoDP[1 << N][N+1];

double menorCusto;
int ultimoVertice;

int melhorCaminho[N+2]; // caminho lexicograficamente menor
int caminhoAtual[N+2];  // caminho temporário
int tamMelhorCaminho;

void salvaCaminho(int s, int ultimo, int subcon, int *idx) {
    if (subcon == 0) {
        caminhoAtual[(*idx)++] = s;
        return;
    }
    salvaCaminho(s, pai[subcon][ultimo], subcon ^ (1 << (ultimo - 1)), idx);
    caminhoAtual[(*idx)++] = ultimo;
}

int comparaCaminho(int len) {
    for (int i = 0; i < len; i++) {
        if (caminhoAtual[i] < melhorCaminho[i]) return -1;
        if (caminhoAtual[i] > melhorCaminho[i]) return 1;
    }
    return 0;
}

void caminhoHamiltoniano(int s) {
    int subcon, i, j;

    for (subcon = 1; subcon < (1 << N); subcon++)
        for (i = 1; i <= N; i++) {
            dp[subcon][i] = INF;
            pai[subcon][i] = -1;
            tamCaminhoDP[subcon][i] = 0;
        }

    for (i = 1; i <= N; i++) {
        if (i == s) continue;
        dp[1 << (i - 1)][i] = dist[s][i];
        pai[1 << (i - 1)][i] = s;
        caminhoDP[1 << (i - 1)][i][0] = s;
        caminhoDP[1 << (i - 1)][i][1] = i;
        tamCaminhoDP[1 << (i - 1)][i] = 2;
    }

    for (subcon = 1; subcon < (1 << N); subcon++)
        for (i = 1; i <= N; i++) {
            if (!(subcon & (1 << (i - 1)))) continue;
            for (j = 1; j <= N; j++) {
                if (j == i || !(subcon & (1 << (j - 1)))) continue;
                int subconSemI = subcon ^ (1 << (i - 1));
                double novoCusto = dp[subconSemI][j] + dist[j][i];
                if (novoCusto < dp[subcon][i]) {
                    dp[subcon][i] = novoCusto;
                    pai[subcon][i] = j;
                    // Copia caminho anterior e adiciona i
                    int tam = tamCaminhoDP[subconSemI][j];
                    for (int k = 0; k < tam; k++)
                        caminhoDP[subcon][i][k] = caminhoDP[subconSemI][j][k];
                    caminhoDP[subcon][i][tam] = i;
                    tamCaminhoDP[subcon][i] = tam + 1;
                } else if (fabs(novoCusto - dp[subcon][i]) < 1e-9) {
                    // Empate: compara caminhos
                    int tamA = tamCaminhoDP[subconSemI][j];
                    int tamB = tamCaminhoDP[subcon][i];
                    int menor = 0;
                    for (int k = 0; k < tamA; k++) {
                        if (k >= tamB) { menor = -1; break; }
                        if (caminhoDP[subconSemI][j][k] < caminhoDP[subcon][i][k]) { menor = -1; break; }
                        if (caminhoDP[subconSemI][j][k] > caminhoDP[subcon][i][k]) { menor = 1; break; }
                    }
                    if (menor == 0 && tamA < tamB) menor = -1;
                    if (menor < 0) {
                        pai[subcon][i] = j;
                        for (int k = 0; k < tamA; k++)
                            caminhoDP[subcon][i][k] = caminhoDP[subconSemI][j][k];
                        caminhoDP[subcon][i][tamA] = i;
                        tamCaminhoDP[subcon][i] = tamA + 1;
                    }
                }
            }
        }

    menorCusto = INF;
    ultimoVertice = -1;
    tamMelhorCaminho = 0;
    for (i = 1; i <= N; i++) {
        if (i == s) continue;
        double custo = dp[((1 << N) - 1) ^ (1 << (s - 1))][i] + dist[i][s];
        int tam = tamCaminhoDP[((1 << N) - 1) ^ (1 << (s - 1))][i];
        // Monta caminho completo
        for (int k = 0; k < tam; k++)
            caminhoAtual[k] = caminhoDP[((1 << N) - 1) ^ (1 << (s - 1))][i][k];
        caminhoAtual[tam] = s;
        int tamTotal = tam + 1;
        if (custo < menorCusto) {
            menorCusto = custo;
            ultimoVertice = i;
            tamMelhorCaminho = tamTotal;
            for (int k = 0; k < tamTotal; k++) melhorCaminho[k] = caminhoAtual[k];
        } else if (fabs(custo - menorCusto) < 1e-9) {
            if (comparaCaminho(tamTotal) < 0) {
                tamMelhorCaminho = tamTotal;
                for (int k = 0; k < tamTotal; k++) melhorCaminho[k] = caminhoAtual[k];
            }
        }
    }
}

void printaMelhorCaminho() {
    for (int i = 0; i < tamMelhorCaminho; i++) {
        if (i > 0) printf("->");
        printf("%d", melhorCaminho[i]);
    }
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
        printaMelhorCaminho();
        printf(": %.5f\n", menorCusto);
    }

    return 0;
}