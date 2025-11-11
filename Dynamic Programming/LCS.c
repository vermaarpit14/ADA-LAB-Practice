#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int max(int a, int b){
    return (a>=b)? a : b;
}

void printResult(char* X, char* Y, int n, int m, int lcs, int** dp){
    char ans[100];
    int idx = lcs;
    ans[lcs] = '\0';
    idx -= 1;
    while(n>0 && m>0){
        if(X[n-1] == Y[m-1]){
            ans[idx--] = X[n-1];
            n -= 1;
            m -= 1;
        } else if(dp[n-1][m] >= dp[n][m-1]){
            n -= 1;
        } else {
            m -= 1;
        }
    }
    printf("Final LCS : %s\n", ans);
}

int f(int i, int j, char* X, char* Y, int** dp){
    if(i==0 || j==0) return 0;
    if(dp[i][j] != -1) return dp[i][j];
    if(X[i-1] == Y[j-1]) dp[i][j] = 1 + f(i-1, j-1, X, Y, dp);
    else dp[i][j] = max(f(i-1, j, X, Y, dp), f(i, j-1, X, Y, dp));
    return dp[i][j];
}

int f_Memo(char* X, char* Y, int n, int m){
    int** dp = (int**)malloc((n+1)*(sizeof(int*)));
    for(int i=0 ; i<=n ; i++){
        dp[i] = (int*)calloc((m+1), sizeof(int));
        for(int j=0 ; j<=m ; j++){
            dp[i][j] = -1;
        }
    }
    int len = f(n, m, X, Y, dp);
    printResult(X, Y, n, m, len, dp);
    return len;
}

int f_Tab(char* X, char* Y, int n, int m){
    int** dp = (int**)malloc((n+1)*(sizeof(int*)));
    for(int i=0 ; i<=n ; i++){
        dp[i] = (int*)calloc((m+1), sizeof(int));
    }
    for(int i=1 ; i<=n ; i++){
        for(int j=1 ; j<=m ; j++){
            if(X[i-1] == Y[j-1]){
                dp[i][j] = 1 + dp[i-1][j-1];
            } else {
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }
    int len = dp[n][m];
    printResult(X, Y, n, m, len, dp);
    return len;
}

int main(){
    char X[100], Y[100];
    printf("Enter the 1st string : ");
    scanf("%s", &X);
    printf("Enter the 2nd string : ");
    scanf("%s", &Y);
    int n = strlen(X), m = strlen(Y);
    int mx1 = f_Memo(X, Y, n, m);
    printf("Length of LCS (Memo) : %d\n", mx1);
    int mx2 = f_Tab(X, Y, n, m);
    printf("Length of LCS (Tab) : %d\n", mx2);
}