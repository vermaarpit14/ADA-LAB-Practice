#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

typedef struct {
    double x, y;
} Point;

int cmpX(const void* a, const void* b){
    double x1 = ((Point*)a)->x;
    double x2 = ((Point*)b)->x;
    if (x1 < x2) return -1;
    if (x1 > x2) return 1;
    return 0;
}

int cmpY(const void* a, const void* b){
    double y1 = ((Point*)a)->y;
    double y2 = ((Point*)b)->y;
    if (y1 < y2) return -1;
    if (y1 > y2) return 1;
    return 0;
}


double distance(Point a, Point b){
    return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}

double bruteForce(Point points[], int n, Point *p1, Point *p2){
    double mn = DBL_MAX;
    for(int i=0 ; i<n ; i++){
        for(int j=i+1 ; j<n ; j++){
            double dis = distance(points[i], points[j]);
            if(dis < mn){
                mn = dis;
                *p1 = points[i];
                *p2 = points[j];
            }
        }
    }
    return mn;
}

double stripClosest(Point strip[], int sz, double d, Point *sp1, Point *sp2){
    double min = d;
    qsort(strip, sz, sizeof(Point), cmpY);
    for (int i = 0; i < sz; ++i) {
        for (int j = i + 1; j < sz && (strip[j].y - strip[i].y) < min; ++j) {
            double dis = distance(strip[i], strip[j]);
            if (dis < min) {
                min = dis;
                *sp1 = strip[i];
                *sp2 = strip[j];
            }
        }
    }
    return min;
}

double closest(Point Px[], Point Py[], int n, Point *p1, Point *p2){
    if(n <= 3){
        return bruteForce(Px, n, p1, p2);
    }
    int mid = n/2;
    Point midPoint = Px[mid];
    Point Pyl[mid + 1];
    Point Pyr[n - mid - 1];
    int li = 0, ri = 0;
    for (int i = 0; i < n; i++) {
        if (Py[i].x <= midPoint.x)
            Pyl[li++] = Py[i];
        else
            Pyr[ri++] = Py[i];
    }
    Point p1_left, p2_left, p1_right, p2_right;
    double dl = closest(Px, Pyl, mid, &p1_left, &p2_left);
    double dr = closest(Px + mid, Pyr, n - mid, &p1_right, &p2_right);
    double d;
    if (dl < dr) {
        d = dl;
        *p1 = p1_left;
        *p2 = p2_left;
    } else {
        d = dr;
        *p1 = p1_right;
        *p2 = p2_right;
    }
    Point strip[n];
    int j = 0;
    for (int i = 0; i < n; i++)
        if (fabs(Py[i].x - midPoint.x) < d)
            strip[j++] = Py[i];
    Point sp1, sp2;
    double d_strip = stripClosest(strip, j, d, &sp1, &sp2);
    if (d_strip < d) {
        *p1 = sp1;
        *p2 = sp2;
        d = d_strip;
    }
    return d;
}

double f(Point points[], int n, Point *p1, Point *p2){
    Point Px[n], Py[n];
    for(int i=0 ; i<n ; i++){
        Px[i] = points[i];
        Py[i] = points[i];
    }
    qsort(Px, n, sizeof(Point), cmpX);
    qsort(Py, n, sizeof(Point), cmpY);
    return closest(Px, Py, n, p1, p2);
}

int main(){
    int n;
    printf("Enter the no of Points : ");
    scanf("%d", &n);
    Point points[n];
    for(int i=0 ; i<n ; i++){
        printf("Enter the Point %d : ", i+1);
        scanf("%lf %lf", &points[i].x, &points[i].y);
    }
    Point p1, p2;
    double ans = f(points, n, &p1, &p2);
    printf("Min distance is = %.2lf\nPair = (%.2lf, %.2lf) and (%.2lf, %.2lf)\n", ans, p1.x, p1.y, p2.x, p2.y);
    return 0;
}