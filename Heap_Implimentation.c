#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int heap[MAX];
int size = 0;
int isMaxHeap = 1;

int compare(int a, int b){
    return (isMaxHeap) ? (a > b) : (a < b);
}

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void Insert(){
    int x;
    printf("Enter the value to Insert : ");
    scanf("%d", &x);
    if (size >= MAX)
    {
        printf("Heap Overflow !!\n");
        return;
    }
    heap[size++] = x;
    int i = size - 1;
    while (i > 0){
        int par = (i - 1) / 2;
        if (compare(heap[i], heap[par])){
            swap(&heap[i], &heap[par]);
            i = par;
        } else {
            break;
        }
    }
    printf("Inserted %d into the Heap !!\n", x);
}

int main(){
    Insert();
    Insert();
    Insert();
    return 0;
}