#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    float s; 
    float e;
} Interval;

int cmp(const void *a, const void *b) {
    return (((Interval*)a)->e) - (((Interval*)b)->e);
}

void f(Interval *I, int n) {
    qsort(I, n, sizeof(Interval), cmp);
    printf("\nIntervals selected:\n");
    printf("ID\tStart\tEnd\n");
    int count = 0;
    float last_end = -1;
    for (int i = 0; i < n; i++) {
        if (I[i].s >= last_end) {
            printf("%d\t%.2f\t%.2f\n", I[i].id, I[i].s, I[i].e);
            last_end = I[i].e;
            count++;
        }
    }
    printf("\nMaximum number of non-overlapping intervals = %d\n", count);
}

int main() {
    int n;
    printf("Enter the number of intervals: ");
    scanf("%d", &n);
    Interval *I = (Interval*)malloc(n * sizeof(Interval));
    printf("Enter interval details (id start end):\n");
    for (int i = 0; i < n; i++) {
        scanf("%d%f%f", &I[i].id, &I[i].s, &I[i].e);
    }
    f(I, n);
    free(I);
    return 0;
}