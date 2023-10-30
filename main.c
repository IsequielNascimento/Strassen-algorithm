#include <stdio.h>
#include <stdlib.h>

#define N 60

void add(int A[N][N], int B[N][N], int C[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

void subtract(int A[N][N], int B[N][N], int C[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}

void strassen_multiply(int A[N][N], int B[N][N], int C[N][N]) {
    if (N <= 60) {
        // Usa a multiplicação de matrizes padrão
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                C[i][j] = 0;
                for (int k = 0; k < N; k++) {
                    C[i][j] += A[i][k] * B[k][j];
                }
            }
        }
    } else {
        // Aplica o algoritmo de Strassen para matrizes maiores
        int newSize = N / 2;

        int A11[newSize][newSize], A12[newSize][newSize], A21[newSize][newSize], A22[newSize][newSize];
        int B11[newSize][newSize], B12[newSize][newSize], B21[newSize][newSize], B22[newSize][newSize];
        int C11[newSize][newSize], C12[newSize][newSize], C21[newSize][newSize], C22[newSize][newSize];

        int M1[newSize][newSize], M2[newSize][newSize], M3[newSize][newSize], M4[newSize][newSize], M5[newSize][newSize];
        int M6[newSize][newSize], M7[newSize][newSize];
        int temp1[newSize][newSize], temp2[newSize][newSize];

        // Divide as matrizes em submatrizes
        for (int i = 0; i < newSize; i++) {
            for (int j = 0; j < newSize; j++) {
                A11[i][j] = A[i][j];
                A12[i][j] = A[i][j + newSize];
                A21[i][j] = A[i + newSize][j];
                A22[i][j] = A[i + newSize][j + newSize];

                B11[i][j] = B[i][j];
                B12[i][j] = B[i][j + newSize];
                B21[i][j] = B[i + newSize][j];
                B22[i][j] = B[i + newSize][j + newSize];
            }
        }

        // Calcula os 7 produtos de strassen
        strassen_multiply(A11, B11, M1);
        strassen_multiply(A12, B21, M2);
        strassen_multiply(A11, B12, M3);
        strassen_multiply(A12, B22, M4);
        strassen_multiply(A21, B11, M5);
        strassen_multiply(A22, B12, M6);
        strassen_multiply(A21, B22, M7);

        // Calcula as submatrizes C usando a fórmula de Strassen
        // C11
        add(M1, M2, temp1);
        subtract(temp1, M4, temp2);
        add(temp2, M6, C11);

        // C12
        add(M3, M4, C12);

        // C21
        add(M5, M6, C21);

        // C22
        subtract(M1, M3, temp1);
        add(temp1, M5, temp2);
        add(temp2, M7, C22);

        // Combina as submatrizes C em C final
        for (int i = 0; i < newSize; i++) {
            for (int j = 0; j < newSize; j++) {
                C[i][j] = C11[i][j];
                C[i][j + newSize] = C12[i][j];
                C[i + newSize][j] = C21[i][j];
                C[i + newSize][j + newSize] = C22[i][j];
            }
        }
    }
}

int main() {
    FILE *input, *output;
    input = fopen("input.txt", "r");
    output = fopen("output.txt", "w");

    if (input == NULL || output == NULL) {
        printf("Não foi possível abrir os arquivos.\n");
        return 1;
    }

    int numero;
    int matrizA[N][N], matrizB[N][N], matrizC[N][N];

    // Lê as matrizes de input do arquivo
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (fscanf(input, "%d", &numero) == EOF) {
                break;
            }
            matrizA[i][j] = numero;
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (fscanf(input, "%d", &numero) == EOF) {
                break;
            }
            matrizB[i][j] = numero;
        }
    }

    // Aplica o algoritmo de Strassen para multiplicar as matrizes
    strassen_multiply(matrizA, matrizB, matrizC);

    // Exporta a matriz resultante para o arquivo de saída
    fprintf(output, "Matriz C \n \n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            fprintf(output, "%d ", matrizC[i][j]);
        }
        fprintf(output, "\n");
    }

    fclose(input);
    fclose(output);

    return 0;
}
