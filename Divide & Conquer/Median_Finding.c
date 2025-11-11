#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b){
    int t = *a;
    *a = *b;
    *b = t;
}

int cmp(const void* a, const void* b){
    return *(int*)a - *(int*)b;
}

int f(int arr[], int n){
    qsort(arr, n, sizeof(int), cmp);
    if(n&1) return arr[n/2];
    else {
        return (arr[n/2]+arr[n/2-1])/2;
    }
}

int findMedian(int arr[], int n){
    for(int i=0 ; i<n-1 ; i++){
        for(int j=i+1 ; j<n ; j++){
            if(arr[j] < arr[i]){
                swap(&arr[i], &arr[j]);
            }
        }
    }
    return arr[n/2];
}

int partition(int arr[], int l, int r, int pivot){
    int i;
    for(int i=l ; i<r ; i++){
        if(arr[i] == pivot){
            swap(&arr[i], &arr[r]);
            break;
        }
    }
    i = l;
    for(int j=l ; j<r ; j++){
        if(arr[j] <= pivot){
            swap(&arr[i], &arr[j]);
            i++;
        }
    }
    swap(&arr[i], &arr[r]);
    return i;
}

int selectKth(int arr[], int l, int r, int k){
    if(k>0 && k<=r-l+1){
        int n = r-l+1;
        int i;
        int num = (n+4)/5;
        int* medians = (int*)malloc(num*sizeof(int));
        for(i=0 ; i<n/5 ; i++){
            medians[i] = findMedian(arr+l+i*5, 5);
        }
        if(i*5 < n){
            medians[i] = findMedian(arr+l+i*5, n%5);
            i++;
        }
        int medofmed;
        if(i == 1) medofmed = medians[i-1];
        else medofmed = selectKth(medians, 0, i-1, i/2);
        free(medians);
        int pos = partition(arr, l, r, medofmed);
        if(pos-l == k-1) return arr[pos];
        if(pos-l > k-1) return selectKth(arr, l, pos-1, k);
        return selectKth(arr, pos+1, r, k-(pos-l+1));
    }
    return -1;
}

int find_Median(int arr[], int n){
    if(n%2 == 1){
        return selectKth(arr, 0, n-1, n/2+1);
    } else {
        int m1 = selectKth(arr, 0, n-1, n/2);
        int m2 = selectKth(arr, 0, n-1, n/2+1);
        return (m1+m2)/2;
    }
}

int main(){
    int n;
    printf("Enter size of the Array : ");
    scanf("%d", &n);
    int arr[n];
    printf("Enter elements of the Array : ");
    for(int i=0 ; i<n ; i++){
        scanf("%d", &arr[i]);
    }
    int median = find_Median(arr, n);
    printf("Median = %d\n", median);
    return 0;
}