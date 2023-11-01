#include <stdio.h>
//Este trecho inclui a biblioteca padrão de entrada e saída (stdio.h) e define uma constante N com o valor 65. Declara três variáveis: tamanho_Matrix (usada para armazenar o tamanho da matriz), sub_M (uma matriz 2x2) e t (uma variável inteira).
#define N 65
int tamanho_Matrix, sub_M[2][2], t;
////////////////////////////////////////////


/* É definida a função 'add', que aceitará duas matrizes 'ad1' e 'ad2', com tamanho definido por 'int w', e armazenará o resultado na matriz 'arr' de tamanho N.*/
void add(int ad1[][N], int ad2[][N], int w, int arr[N][N]) {
    int i, j;
    for (i = 0; i < w; i++) {
        for (j = 0; j < w; j++) {
            arr[i][j] = ad1[i][j] + ad2[i][j];
        }
    }
}
////////////////////////////////////////////
/* A seguir é definida a função sub. Funciona de forma semelhante à função add, mas subtrai elementos correspondentes das matrizes ad1 e ad2, armazenando o resultado em sarr. */
void sub(int ad1[][N], int ad2[][N], int w, int sarr[N][N]) {
    int i, j;
    for (i = 0; i < w; i++) {
        for (j = 0; j < w; j++) {
            sarr[i][j] = ad1[i][j] - ad2[i][j];
        }
    }
}

////////////////////////////////////////////

/* Aqui começa a definição da função strassen. Ela aceita duas matrizes a e b de tamanho N e realiza a multiplicação de Strassen, armazenando o resultado em strtmp.*/
void strassen(int a[N][N], int b[N][N], int n, int strtmp[N][N]) {

    /* Nesta parte, várias matrizes e variáveis auxiliares são declaradas. Essas matrizes são usadas para dividir as matrizes a e b em submatrizes menores e realizar as operações da multiplicação de Strassen.*/
    int a11[N][N], a12[N][N], a21[N][N], a22[N][N], b11[N][N];
    int b12[N][N], b21[N][N], b22[N][N];
    int i, j, cc11[N][N], cc12[N][N], cc21[N][N], cc22[N][N];
    int p[N][N], q[N][N], r[N][N], s[N][N], t[N][N], u[N][N], v[N][N];
    int ap, aq, ar, as, at, au, av;
    int tmpad1[N][N], tmpad2[N][N], tmpsb1[N][N], tmpsb2[N][N];
    ////////////////////////////////////////////

//Esta linha verifica se o tamanho n é igual a 1, o que indica que as matrizes são matrizes 1x1 e a multiplicação é direta.
    if (n == 1) {
        /*A seguir é calculado os produtos parciais necessários para a multiplicação de Strassen quando n é igual a 1.*/
        ap = (a[0][0] + a[1][1]) * (b[0][0] + b[1][1]);
        aq = (a[1][0] + a[1][1]) * b[0][0];
        ar = a[0][0] * (b[0][1] - b[1][1]);
        as = a[1][1] * (b[1][0] - b[0][0]);
        at = (a[0][0] + a[0][1]) * b[1][1];
        au = (a[1][0] - a[0][0]) * (b[0][0] + b[0][1]);
        av = (a[0][1] - a[1][1]) * (b[1][0] + b[1][1]);

        //A seguir é calculado o resultado da multiplicação de Strassen.
        sub_M[0][0] = ap + as - at + av;
        sub_M[0][1] = ar + at;
        sub_M[1][0] = aq + as;
        sub_M[1][1] = ap + ar - aq + au;

        //A seguir é armazenado o resultado da multiplicação de Strassen na matriz strtmp.
        for (i = 0; i < 2; i++) {
            for (j = 0; j < 2; j++) {
                strtmp[i][j] = sub_M[i][j];
            }
        }
        return;
    }

// Se n não for igual a 1, as matrizes a e b são divididas em quatro submatrizes menores.
//Esses loops dividem as matrizes a e b em submatrizes menores (a11, a12, a21, a22, b11, b12, b21, b22).
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            a11[i][j] = a[i][j];
            a12[i][j] = a[i][j + n];
            a21[i][j] = a[i + n][j];
            a22[i][j] = a[i + n][j + n];
            b11[i][j] = b[i][j];
            b12[i][j] = b[i][j + n];
            b21[i][j] = b[i + n][j];
            b22[i][j] = b[i + n][j + n];
        }
    }


/*As linhas a seguir calculam a submatriz p usando a multiplicação de Strassen nas submatrizes apropriadas.*/
// p = (a11+a22) * (b11+b22)
    add(a11, a22, n, tmpad1);
    add(b11, b22, n, tmpad2);
    strassen(tmpad1, tmpad2, n / 2, p); // p

// q = (a21+a22) * b11
    add(a21, a22, n, tmpad1);
    strassen(tmpad1, b11, n / 2, q); // q

    // r = a11 * (b12-b22)
    sub(b12, b22, n, tmpsb1);
    strassen(a11, tmpsb1, n / 2, r); // r

    // s = a22 * (b21-b11)
    sub(b21, b11, n, tmpsb1);
    strassen(a22, tmpsb1, n / 2, s); // s

    // t = (a11+a12) * b22
    add(a11, a12, n, tmpad1);
    strassen(tmpad1, b22, n / 2, t); // t

    // u = (a21-a11) * (b11+b12)
    sub(a21, a11, n, tmpsb1);
    add(b11, b12, n, tmpad1);
    strassen(tmpsb1, tmpad1, n / 2, u); // u

    // v = (a12-a22) * (b21+b22)
    sub(a12, a22, n, tmpsb1);
    add(b21, b22, n, tmpad1);
    strassen(tmpsb1, tmpad1, n / 2, v); // v

    /* A seguir são combinado as submatrizes intermediárias p, q, r, s, t, u e v para calcular as submatrizes cc11, cc12, cc21 e cc22, que representam a parte superior esquerda, superior direita, inferior esquerda e inferior direita do resultado final.*/
    add(p, s, n, tmpad1);
    add(tmpad1, v, n, tmpad2);
    sub(tmpad2, t, n, cc11);
    add(r, t, n, cc12);
    add(q, s, n, cc21);
    add(p, r, n, tmpad1);
    add(tmpad1, u, n, tmpad2);
    sub(tmpad2, q, n, cc22);
    
    
    // Esses loops reorganizam as submatrizes cc11, cc12, cc21 e cc22 na matriz final strtmp.
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            strtmp[i][j] = cc11[i][j];
            strtmp[i][j + n] = cc12[i][j];
            strtmp[i + n][j] = cc21[i][j];
            strtmp[i + n][j + n] = cc22[i][j];
        }
    }
}

int main(int argc, char *argv[]) {
    /* Nesta parte, são declarados ponteiros de arquivo para abrir e manipular arquivos. São criados ponteiros para os arquivos de entrada entrada_A e entrada_B (leitura) e para os arquivos de saída matriz_A, matriz_B e saida (escrita).*/
    FILE *entrada_A, *entrada_B, *matriz_A, *matriz_B, *saida;
    entrada_A = fopen("entrada_A.txt", "r");
    entrada_B = fopen("entrada_B.txt", "r");
    matriz_A = fopen("matrizA.txt", "w");
    matriz_B = fopen("matrizB.txt", "w");
    saida = fopen("saida.txt", "w");

    // declaração de variáveis de loop
    int i, j;

    //A seguir, são declaradas matrizes ae, be e ce para armazenar os valores lidos e o resultado da multiplicação.
    int ae[N][N], be[N][N], ce[N][N];

    //É solicitado ao usuário que insira o tamanho da matriz de potência 2 e armazena-o na variável tamanho_Matrix.
    printf("Tamanho da matriz :");
    scanf("%d", &tamanho_Matrix);

/* Nesses loops aninhados, o programa lê os valores da matriz A do arquivo entrada_A, armazena-os na matriz ae e os escreve no arquivo matriz_A. A variável count é incrementada para acompanhar a quantidade de valores lidos. */
for (i = 0; i < tamanho_Matrix; i++) {
    for (j = 0; j < tamanho_Matrix; j++) {
        fscanf(entrada_A, "%d", &ae[i][j]);  // Lê um valor do arquivo entrada_A e armazena em ae[i][j].
        fprintf(matriz_A, "%d ", ae[i][j]);  // Escreve o valor lido em matriz_A.
    }
    fprintf(matriz_A, "\n");  // Move para uma nova linha no arquivo matriz_A.
}
 fclose(entrada_A); // Fecha o arquivo entrada_A.
 fclose(matriz_A); // Fecha o arquivo matriz_A.

for (i = 0; i < tamanho_Matrix; i++) {
    for (j = 0; j < tamanho_Matrix; j++) {
        fscanf(entrada_B, "%d", &be[i][j]);  // Lê um valor do arquivo entrada_B e armazena em be[i][j].
        fprintf(matriz_B, "%d ", be[i][j]);  // Escreve o valor lido em matriz_B.
    }
    fprintf(matriz_B, "\n");  // Move para uma nova linha no arquivo matriz_B.
}
fclose(entrada_B); // Fecha o arquivo entrada_B.
fclose(matriz_B); // Fecha o arquivo matriz_B.
    
    strassen(ae, be, tamanho_Matrix / 2, ce); /* strassen(ae, be, tamanho_Matrix / 2, ce): Chama a função strassen para multiplicar as matrizes ae e be e armazena o resultado na matriz ce.*/
fprintf(saida, "Multiplicação das Matrizes\n");
for (i = 0; i < tamanho_Matrix; i++) {
    for (j = 0; j < tamanho_Matrix; j++) {
        fprintf(saida, "%d ", ce[i][j]);  // Escreve o resultado da multiplicação de matrizes em "saida".
    }
    fprintf(saida, "\n");  // Move para uma nova linha no arquivo "saida".
}

fclose(saida);  // Fecha o arquivo "saida".
   
    
    
    return 0; // return 0;: Encerra a função main e indica que o programa foi executado com sucesso, retornando 0 como código de saída.
}
