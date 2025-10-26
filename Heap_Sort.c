#include <stdio.h>
#include <stdlib.h>

#define MAX 100

struct Process {
    int pid;
    int priority;
};

struct Process heap[MAX];
int size = 0;
int isMaxHeap = 1;

int compare(int a, int b) {
    return (isMaxHeap) ? (a > b) : (a < b);
}

void swap(struct Process *a, struct Process *b) {
    struct Process temp = *a;
    *a = *b;
    *b = temp;
}

void Heapify(int n, int i) {
    int curr = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && compare(heap[left].priority, heap[curr].priority))
        curr = left;
    if (right < n && compare(heap[right].priority, heap[curr].priority))
        curr = right;
    if (curr != i) {
        swap(&heap[curr], &heap[i]);
        Heapify(n, curr);
    }
}

void BuildHeap(int n) {
    for (int i = (n / 2) - 1; i >= 0; i--)
        Heapify(n, i);
}

void Display() {
    if (size <= 0) {
        printf("Priority Queue is Empty !!\n");
        return;
    }
    for (int i = 0; i < size; i++)
        printf("(PID=%d, Priority=%d) ", heap[i].pid, heap[i].priority);
    printf("\n");
}

void HeapSort() {
    if (size <= 0) {
        printf("No elements to sort !!\n");
        return;
    }
    BuildHeap(size);
    int n = size;
    for (int i = n - 1; i > 0; i--) {
        swap(&heap[0], &heap[i]);
        Heapify(i, 0);
    }
    printf("\nAfter Sorting : \n");
    for (int i = 0; i < n; i++)
        printf("(PID=%d, Priority=%d) ", heap[i].pid, heap[i].priority);
    printf("\n");
}

int main() {
    int choice;
    printf("Choose Heap Type:\n1. Max Heap (Sort Descending)\n2. Min Heap (Sort Ascending)\nEnter your choice: ");
    scanf("%d", &choice);
    isMaxHeap = (choice == 1);
    printf("Enter number of processes: ");
    scanf("%d", &size);
    for (int i = 0; i < size; i++) {
        printf("Enter Process ID and Priority for Process %d: ", i + 1);
        scanf("%d %d", &heap[i].pid, &heap[i].priority);
    }
    printf("\nBefore Sorting : \n");
    Display();
    HeapSort();
    return 0;
}
