#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void printResult(int **S, int i, int j) {
    if (i == j) {
        printf("A%d", i);
    } else {
        printf("(");
        printResult(S, i, S[i][j]);
        printResult(S, S[i][j] + 1, j);
        printf(")");
    }
}

int main(){
    int n;
    printf("Enter the no of Matrices : ");
    scanf("%d", &n);
    n += 1;
    int *p = (int*)malloc(n*(sizeof(int)));
    for(int i=1 ; i<n ; i++){
        int r, c;
        printf("\nEnter the dimensions of Matrix %d : ", i);
        scanf("%d%d", &r, &c);
        if(i == 1){
            p[0] = r;
            p[1] = c;
        } else {
            p[i] = c;
        }
    }
    int **M = (int**)malloc(n*(sizeof(int*)));
    int **S = (int**)malloc(n*(sizeof(int*)));
    for(int i=0 ; i<n ; i++){
        M[i] = (int*)calloc(n, (sizeof(int)));
        S[i] = (int*)calloc(n, (sizeof(int)));
    }
    for(int d=1 ; d<n-1 ; d++){
        for(int i=1 ; i<n-d ; i++){
            int j = i+d;
            int mn = INT_MAX;
            for(int k=i ; k<=j-1 ; k++){
                int cost = M[i][k] + M[k+1][j] + p[i-1]*p[k]*p[j];
                if(cost < mn){
                    mn = cost;
                    S[i][j] = k;
                }
            }
            M[i][j] = mn;
        }
    }
    printf("\nMin Cost for the multiplication : %d\n", M[1][n-1]);
    printf("\n");
    printResult(S, 1, n-1);
    printf("\n");
    for(int i=0 ; i<n ; i++){
        free(M[i]);
        free(S[i]);
    }
    free(M);
    free(S);
    free(p);
}