#include <stdio.h>
#include <stdlib.h>

int **allocMatrix(int n) {
    int **mat = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
        mat[i] = (int *)calloc(n, sizeof(int));
    return mat;
}

void freeMatrix(int **mat, int n) {
    for (int i = 0; i < n; i++)
        free(mat[i]);
    free(mat);
}

void addMatrix(int **A, int **B, int **C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}

void subMatrix(int **A, int **B, int **C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
}

void strassen(int **A, int **B, int **C, int n){
    if(n == 1){
        C[0][0] = A[0][0]*B[0][0];
        return;
    }
    int k = n/2;
    int **A11 = allocMatrix(k);
    int **A12 = allocMatrix(k);
    int **A21 = allocMatrix(k);
    int **A22 = allocMatrix(k);
    int **B11 = allocMatrix(k);
    int **B12 = allocMatrix(k);
    int **B21 = allocMatrix(k);
    int **B22 = allocMatrix(k);
    for(int i=0 ; i<k ; i++){
        for(int j=0 ; j<k ; j++){
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + k];
            A21[i][j] = A[i + k][j];
            A22[i][j] = A[i + k][j + k];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + k];
            B21[i][j] = B[i + k][j];
            B22[i][j] = B[i + k][j + k];
        }
    }
    int **M1 = allocMatrix(k);
    int **M2 = allocMatrix(k);
    int **M3 = allocMatrix(k);
    int **M4 = allocMatrix(k);
    int **M5 = allocMatrix(k);
    int **M6 = allocMatrix(k);
    int **M7 = allocMatrix(k);
    int **T1 = allocMatrix(k);
    int **T2 = allocMatrix(k);

    addMatrix(A11, A22, T1, k);
    addMatrix(B11, B22, T2, k);
    strassen(T1, T2, M1, k);

    addMatrix(A21, A22, T1, k);
    strassen(T1, B11, M2, k);

    subMatrix(B12, B22, T2, k);
    strassen(A11, T2, M3, k);

    subMatrix(B21, B11, T2, k);
    strassen(A22, T2, M4, k);

    addMatrix(A11, A12, T1, k);
    strassen(T1, B22, M5, k);

    subMatrix(A21, A11, T1, k);
    addMatrix(B11, B12, T2, k);
    strassen(T1, T2, M6, k);

    // M7 = (A12 - A22) * (B21 + B22)
    subMatrix(A12, A22, T1, k);
    addMatrix(B21, B22, T2, k);
    strassen(T1, T2, M7, k);

    // Combine results
    int **C11 = allocMatrix(k);
    int **C12 = allocMatrix(k);
    int **C21 = allocMatrix(k);
    int **C22 = allocMatrix(k);

    // C11 = M1 + M4 - M5 + M7
    addMatrix(M1, M4, T1, k);
    subMatrix(T1, M5, T2, k);
    addMatrix(T2, M7, C11, k);

    // C12 = M3 + M5
    addMatrix(M3, M5, C12, k);

    // C21 = M2 + M4
    addMatrix(M2, M4, C21, k);

    // C22 = M1 - M2 + M3 + M6
    subMatrix(M1, M2, T1, k);
    addMatrix(T1, M3, T2, k);
    addMatrix(T2, M6, C22, k);

    // Combine 4 submatrices into C
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            C[i][j] = C11[i][j];
            C[i][j + k] = C12[i][j];
            C[i + k][j] = C21[i][j];
            C[i + k][j + k] = C22[i][j];
        }
    }

    // Free all matrices
    freeMatrix(A11, k); freeMatrix(A12, k); freeMatrix(A21, k); freeMatrix(A22, k);
    freeMatrix(B11, k); freeMatrix(B12, k); freeMatrix(B21, k); freeMatrix(B22, k);
    freeMatrix(M1, k); freeMatrix(M2, k); freeMatrix(M3, k); freeMatrix(M4, k);
    freeMatrix(M5, k); freeMatrix(M6, k); freeMatrix(M7, k);
    freeMatrix(C11, k); freeMatrix(C12, k); freeMatrix(C21, k); freeMatrix(C22, k);
    freeMatrix(T1, k); freeMatrix(T2, k);
}

void printMatrix(int **mat, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%d ", mat[i][j]);
        printf("\n");
    }
}

int main() {
    int n;
    printf("Enter matrix size (power of 2): ");
    scanf("%d", &n);
    int **A = allocMatrix(n);
    int **B = allocMatrix(n);
    int **C = allocMatrix(n);
    printf("Enter matrix A:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &A[i][j]);

    printf("Enter matrix B:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &B[i][j]);
    strassen(A, B, C, n);
    printf("\nResultant matrix (A x B):\n");
    printMatrix(C, n);
    freeMatrix(A, n);
    freeMatrix(B, n);
    freeMatrix(C, n);
    return 0;
}