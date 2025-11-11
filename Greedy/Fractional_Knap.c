#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    float w;
    float v;
    float r;
} Item;

int cmp(const void *a, const void *b) {
    float r1 = ((Item*)a)->r;
    float r2 = ((Item*)b)->r;
    if (r1 < r2) return 1;
    else if (r1 > r2) return -1;
    else return 0;
}

void f(Item *items, int n, float cap) {
    qsort(items, n, sizeof(Item), cmp);
    float tot = 0.0;
    float rem = cap;
    printf("\nItems taken into Knapsack:\n");
    printf("ID\tWeightTaken\tValueTaken\n");
    for (int i = 0; i < n && rem > 0; i++) {
        if (items[i].w <= rem) {
            tot += items[i].v;
            rem -= items[i].w;
            printf("%d\t%.2f\t\t%.2f\n", items[i].id, items[i].w, items[i].v);
        } else {
            float frac = rem / items[i].w;
            tot += items[i].v * frac;
            printf("%d\t%.2f\t\t%.2f (%.2f fraction)\n",
                   items[i].id, rem, items[i].v * frac, frac);
            rem = 0;
        }
    }
    printf("\nMaximum value in Knapsack = %.2f\n", tot);
}

int main() {
    int n;
    float cap;
    printf("Enter the number of items: ");
    scanf("%d", &n);
    Item *items = (Item*)malloc(n * sizeof(Item));
    printf("Enter the capacity of the knapsack: ");
    scanf("%f", &cap);
    printf("Enter item details (id weight value):\n");
    for (int i = 0; i < n; i++) {
        scanf("%d%f%f", &items[i].id, &items[i].w, &items[i].v);
        items[i].r = items[i].v / items[i].w;
    }
    f(items, n, cap);
    free(items);
    return 0;
}
