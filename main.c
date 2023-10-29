#include <stdio.h>
#include <stdlib.h>
#define N 40

void strassen_multiply(float A[N][N], float B[N][N], float C[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main() {
    FILE *entrada, *saida;
    entrada = fopen("entrada.txt", "r");
    saida = fopen("saida.txt", "w");

    if (entrada == NULL || saida == NULL) {
        printf("Não foi possível abrir os arquivos.\n");
        return 1;
    }

    float numero;
    float matrizA[N][N], matrizB[N][N], matrizC[N][N];

    // Ler os números do arquivo e organizar em matrizes 40x40
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (fscanf(entrada, "%f", &numero) == EOF) {
                break;
            }
            matrizA[i][j] = numero;
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (fscanf(entrada, "%f", &numero) == EOF) {
                break;
            }
            matrizB[i][j] = numero;
        }
    }

    // Aplicar o algoritmo de multiplicação de matrizes
    strassen_multiply(matrizA, matrizB, matrizC);

    // Exportar a matriz resultante para o arquivo de saída
    fprintf(saida, "TESTE AAAAAAAAAAAAAAA \n \n", N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            fprintf(saida, "%.2f ", matrizC[i][j]);
        }
        fprintf(saida, "\n");
    }

    fclose(entrada);
    fclose(saida);

    return 0;
}
