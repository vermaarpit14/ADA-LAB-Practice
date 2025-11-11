#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int id;
    int weight;
    int value;
} Item;

int max(int a, int b){
    return (a >= b) ? a : b;
}

int f(int i, int w, Item* items, int** dp, int n){
    if(i==0) return 0;
    if(dp[i][w] != -1){
        return dp[i][w];
    }
    if(items[i-1].weight > w){
        dp[i][w] = f(i-1, w, items, dp, n);
    } else {
        int take = f(i-1, w-items[i-1].weight, items, dp, n) + items[i-1].value;
        int not_take = f(i-1, w, items, dp, n);
        dp[i][w] = max(take, not_take);
    }
    return dp[i][w];
}

void printResult(int n, int w, Item* items, int** dp){
    printf("\nItems picked are : ");
    while(n>0 && w>0){
        if(dp[n][w] != dp[n-1][w]){
            printf("(%d, %d, %d), ", items[n-1].id, items[n-1].weight, items[n-1].value);
            w -= items[n-1].weight;
        }
        n -= 1;
    }
    printf("\n");
}

int f_Memo(int w, Item* items, int n){
    int** dp = (int**)malloc((n+1)*(sizeof(int*)));
    for(int i=0 ; i<=n ; i++){
        dp[i] = (int*)calloc((w+1), sizeof(int));
        for(int j=0 ; j<=w ; j++){
            dp[i][j] = -1;
        }
    }
    int mx = f(n, w, items, dp, n);
    printResult(n, w, items, dp);
    return mx;
}

int f_Tab(int w, Item* items, int n){
    int** dp = (int**)malloc((n+1)*(sizeof(int*)));
    for(int i=0 ; i<=n ; i++){
        dp[i] = (int*)calloc(w+1, sizeof(int));
    }
    for(int i=1 ; i<=n ; i++){
        for(int j=1 ; j<=w ; j++){
            if(items[i-1].weight <= j){
                dp[i][j] = max((items[i-1].value+dp[i-1][j-items[i-1].weight]), dp[i-1][j]);
            } else {
                dp[i][j] = dp[i-1][j];
            }
        }
    }
    printResult(n, w, items, dp);
    return dp[n][w];
}

int main(){
    int n, w;
    printf("Enter the no of Items : ");
    scanf("%d", &n);
    printf("Enter the capacity of Knapsack : ");
    scanf("%d", &w);
    Item* items = (Item*)malloc(n*(sizeof(Item)));
    for(int i=0 ; i<n ; i++){
        printf("Enter the details of the Item %d : ", i+1);
        scanf("%d%d%d", &items[i].id, &items[i].weight, &items[i].value);
    }
    int mx1 = f_Memo(w, items, n);
    printf("Max. found from f_Memo : %d\n", mx1);
    int mx2 = f_Tab(w, items, n);
    printf("Max. found from f_Tab : %d\n", mx2);
}