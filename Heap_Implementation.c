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

void Heapify(int n, int i){
    int curr = i;
    int left = 2*i+1;
    int right = 2*i+2;
    if(left<n && compare(heap[left], heap[curr])) curr = left;
    if(right<n && compare(heap[right], heap[curr])) curr = right;
    if(curr != i){
        swap(&heap[curr], &heap[i]);
        Heapify(n, curr);
    }
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

void Delete(){
    if(size <= 0){
        printf("Heap Underflow !!\n");
        return;
    }
    printf("Deleted %d from the Heap !!\n", heap[0]);
    heap[0] = heap[--size];
    Heapify(size, 0);
}

void Peek(){
    if(size <= 0){
        printf("Heap is Empty !!\n");
        return;
    }
    if(isMaxHeap){
        printf("Max Element of the Heap : %d\n", heap[0]);
    } else {
        printf("Min Element of the Heap : %d\n", heap[0]);
    }
}

void Display(){
    if(size <= 0){
        printf("Heap is Empty !!\n");
        return;
    }
    printf("Heap Elements : ");
    for(int i=0 ; i<size ; i++){
        printf("%d ", heap[i]);
    }
    printf("\n");
}

void BuildHeap(){
    printf("Enter the size of the Array : ");
    scanf("%d", &size);
    printf("Enter the elements of the Array : ");
    for(int i=0 ; i<size ; i++){
        scanf("%d", &heap[i]);
    }
    for(int i=(size-1)/2 ; i>=0 ; i--){
        Heapify(size, i);
    }
    printf("Built Heap from the given Array !!\n");
}

int main() {
    int choice;
    printf("Choose Heap Type:\n1. Max Heap\n2. Min Heap\nEnter your choice: ");
    scanf("%d", &choice);
    isMaxHeap = (choice == 1);
    while (1) {
        printf("\n===== HEAP MENU =====\n");
        printf("1. Insert\n");
        printf("2. Delete Root\n");
        printf("3. Peek (Top Element)\n");
        printf("4. Build Heap from Array\n");
        printf("5. Display Heap\n");
        printf("6. Exit\n");
        printf("=====================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
        case 1:
            Insert();
            break;

        case 2:
            Delete();
            break;

        case 3:
            Peek();
            break;

        case 4:
            BuildHeap();
            break;

        case 5:
            Display();
            break;

        case 6:
            exit(0);

        default:
            printf("Invalid choice!!\n");
        }
    }
    return 0;
}
