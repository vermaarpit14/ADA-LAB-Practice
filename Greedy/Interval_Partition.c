#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    float s;
    float e;
} Interval;

int cmp(const void *a, const void *b) {
    return (((Interval*)a)->s) - (((Interval*)b)->s);
}

void f(Interval *I, int n) {
    qsort(I, n, sizeof(Interval), cmp);
    float roomEnd[100];
    int roomCount = 0;
    int roomAssigned[100];
    for (int i = 0; i < n; i++) {
        int assigned = 0;
        for (int r = 0; r < roomCount; r++) {
            if (roomEnd[r] <= I[i].s) {
                roomEnd[r] = I[i].e;
                roomAssigned[i] = r + 1;
                assigned = 1;
                break;
            }
        }
        if (!assigned) {
            roomEnd[roomCount] = I[i].e;
            roomAssigned[i] = roomCount + 1;
            roomCount++;
        }
    }
    printf("\nIntervals Scheduled:\n");
    printf("ID\tStart\tEnd\tRoom\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%.2f\t%.2f\t%d\n", I[i].id, I[i].s, I[i].e, roomAssigned[i]);
    }
    printf("\nMinimum number of rooms required = %d\n", roomCount);
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
