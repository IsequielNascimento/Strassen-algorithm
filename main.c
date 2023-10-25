#include <stdio.h>
#define N 2

void strassen_multiply(int A[N][N], int B[N][N], int C[N][N]) {
    int M1, M2, M3, M4, M5, M6, M7;

    M1 = (A[0][0] + A[1][1]) * (B[0][0] + B[1][1]);
    M2 = (A[1][0] + A[1][1]) * B[0][0];
    M3 = A[0][0] * (B[0][1] - B[1][1]);
    M4 = A[1][1] * (B[1][0] - B[0][0]);
    M5 = (A[0][0] + A[0][1]) * B[1][1];
    M6 = (A[1][0] - A[0][0]) * (B[0][0] + B[0][1]);
    M7 = (A[0][1] - A[1][1]) * (B[1][0] + B[1][1]);

    C[0][0] = M1 + M4 - M5 + M7;
    C[0][1] = M3 + M5;
    C[1][0] = M2 + M4;
    C[1][1] = M1 - M2 + M3 + M6;
}

int main() {
    FILE *entrada, *saida;
    entrada = fopen("entrada.txt", "r");
    saida = fopen("saida.txt", "w");

    if (entrada == NULL || saida == NULL) {
        printf("Não foi possível abrir os arquivos.\n");
        return 1;
    }

    int numero;
    int matrizA[2][2], matrizB[2][2], matrizC[2][2];

    // Ler os números do arquivo e organizar em matrizes 2x2
    while (fscanf(entrada, "%d", &numero) != EOF) {
        matrizA[0][0] = numero;
        fscanf(entrada, "%d", &numero);
        matrizA[0][1] = numero;
        fscanf(entrada, "%d", &numero);
        matrizA[1][0] = numero;
        fscanf(entrada, "%d", &numero);
        matrizA[1][1] = numero;

        fscanf(entrada, "%d", &numero);
        matrizB[0][0] = numero;
        fscanf(entrada, "%d", &numero);
        matrizB[0][1] = numero;
        fscanf(entrada, "%d", &numero);
        matrizB[1][0] = numero;
        fscanf(entrada, "%d", &numero);
        matrizB[1][1] = numero;

        // Aplicar o algoritmo de Strassen
        strassen_multiply(matrizA, matrizB, matrizC);

        // Exportar a matriz resultante para o arquivo de saída
         fprintf(saida, "\n Resultado Matriz: \n");
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                fprintf(saida, "%d ", matrizC[i][j]);
            }
            fprintf(saida, "\n");
        }
       
    }

    fclose(entrada);
    fclose(saida);

    return 0;
}
