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

void Insert() {
    if (size >= MAX) {
        printf("Heap Overflow !!\n");
        return;
    }
    struct Process p;
    printf("Enter Process ID and Priority : ");
    scanf("%d %d", &p.pid, &p.priority);
    heap[size] = p;
    int i = size;
    size++;
    while (i > 0) {
        int par = (i - 1) / 2;
        if (compare(heap[i].priority, heap[par].priority)) {
            swap(&heap[i], &heap[par]);
            i = par;
        } else
            break;
    }
    printf("Inserted Process (PID=%d, Priority=%d) into the Queue !!\n", p.pid, p.priority);
}

void Delete() {
    if (size <= 0) {
        printf("Heap Underflow !!\n");
        return;
    }
    printf("Deleted Process (PID=%d, Priority=%d) from the Queue !!\n", heap[0].pid, heap[0].priority);
    heap[0] = heap[--size];
    Heapify(size, 0);
}

void Peek() {
    if (size <= 0) {
        printf("Priority Queue is Empty !!\n");
        return;
    }
    if (isMaxHeap)
        printf("Highest Priority Process : (PID=%d, Priority=%d)\n", heap[0].pid, heap[0].priority);
    else
        printf("Lowest Priority Process : (PID=%d, Priority=%d)\n", heap[0].pid, heap[0].priority);
}

void Display() {
    if (size <= 0) {
        printf("Priority Queue is Empty !!\n");
        return;
    }
    printf("Processes in Priority Queue:\n");
    for (int i = 0; i < size; i++)
        printf("(PID=%d, Priority=%d) ", heap[i].pid, heap[i].priority);
    printf("\n");
}

void ChangePriority() {
    int pid, newPriority;
    printf("Enter Process ID whose priority you want to change: ");
    scanf("%d", &pid);
    printf("Enter new Priority: ");
    scanf("%d", &newPriority);
    int found = 0;
    for (int i = 0; i < size; i++) {
        if (heap[i].pid == pid) {
            found = 1;
            heap[i].priority = newPriority;
            printf("Updated PID=%d with new Priority=%d\n", pid, newPriority);
            int par = (i - 1) / 2;
            if (i > 0 && compare(heap[i].priority, heap[par].priority)) {
                while (i > 0 && compare(heap[i].priority, heap[par].priority)) {
                    swap(&heap[i], &heap[par]);
                    i = par;
                    par = (i - 1) / 2;
                }
            } else {
                Heapify(size, i);
            }
            break;
        }
    }
    if (!found)
        printf("Process with PID=%d not found !!\n", pid);
}

int main() {
    int choice;
    printf("Choose Priority Queue Type:\n1. Max Priority Queue\n2. Min Priority Queue\nEnter your choice: ");
    scanf("%d", &choice);
    isMaxHeap = (choice == 1);

    while (1) {
        printf("\n===== PRIORITY QUEUE MENU =====\n");
        printf("1. Insert Process\n");
        printf("2. Delete Top Process\n");
        printf("3. Peek (Top Priority Process)\n");
        printf("4. Change Priority of Process\n");
        printf("5. Display Queue\n");
        printf("6. Exit\n");
        printf("===============================\n");
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
            ChangePriority();
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
