#include <stdio.h>

#define N = 5

void multiplicacao_matriz(int A[N][N], int B[N][N], int C[N][N]) {
    int i, j, k;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            C[i][j] = 0;
            for (k = 0; k < N; k++) {
                // C[i][j] = A[i][0] * B[0][j] + A[i][1] * B[1][j] + ... + A[i][N-1] * B[N-1][j]
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void multiplicaca_strassen(int A[N][N], int B[N][N], int C[N][N]) {
    if ( M <= 5){
        multiplicacao_matriz(A, B, C);
        return;
}

int A11[N/2][N/2], A12[N/2][N/2], A21[N/2][N/2], A22[N/2][N/2];
int B11[N/2][N/2], B12[N/2][N/2], B21[N/2][N/2], B22[N/2][N/2];
int C11[N/2][N/2], C12[N/2][N/2], C21[N/2][N/2], C22[N/2][N/2];
// P1 = (A11 + A22) * (B11 + B22)
int P1[N/2][N/2], P2[N/2][N/2], P3[N/2][N/2], P4[N/2][N/2], P5[N/2][N/2], P6[N/2][N/2], P7[N/2][N/2];

}