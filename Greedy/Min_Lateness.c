#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    float t; 
    float d; 
} Job;

int cmp(const void *a, const void *b) {
    float d1 = ((Job*)a)->d;
    float d2 = ((Job*)b)->d;
    if (d1 > d2) return 1;
    else if (d1 < d2) return -1;
    else return 0;
}

void f(Job *J, int n) {
    qsort(J, n, sizeof(Job), cmp);
    float time = 0.0;
    float maxLateness = 0.0;
    printf("\nJob Schedule (Earliest Deadline First):\n");
    printf("ID\tProc.Time\tDeadline\tFinish\tLateness\n");
    for (int i = 0; i < n; i++) {
        time += J[i].t;
        float lateness = time - J[i].d;
        if (lateness < 0) lateness = 0;
        if (lateness > maxLateness) maxLateness = lateness;
        printf("%d\t%.2f\t\t%.2f\t\t%.2f\t%.2f\n", J[i].id, J[i].t, J[i].d, time, lateness);
    }
    printf("\nMinimum possible maximum lateness = %.2f\n", maxLateness);
}

int main() {
    int n;
    printf("Enter the number of jobs: ");
    scanf("%d", &n);
    Job *J = (Job*)malloc(n * sizeof(Job));
    printf("Enter job details (id processing_time deadline):\n");
    for (int i = 0; i < n; i++) {
        scanf("%d%f%f", &J[i].id, &J[i].t, &J[i].d);
    }
    f(J, n);
    free(J);
    return 0;
}
