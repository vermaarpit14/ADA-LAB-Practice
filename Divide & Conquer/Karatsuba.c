#include <stdio.h>
#include <math.h>

typedef unsigned long long ull;

int dig(ull n){
    return (n==0)?1:log10(n)+1;
}

ull karatsuba(ull x, ull y){
    if(x<10 || y<10) return x*y;
    int n = fmax(dig(x), dig(y));
    int m = n/2;
    ull pow_of_10 = 1;
    for(int i=0 ; i<m ; i++) pow_of_10 *= 10;
    ull h1 = x/pow_of_10;
    ull l1 = x%pow_of_10;
    ull h2 = y/pow_of_10;
    ull l2 = y%pow_of_10;

    ull z0 = karatsuba(l1, l2);
    ull z1 = karatsuba((l1+h1), (l2+h2));
    ull z2 = karatsuba(h1, h2);

    return z2*pow_of_10*pow_of_10 + (z1-z2-z0)*pow_of_10 + z0;
}

int main(){
    ull a, b;
    printf("Enter two Numbers : ");
    scanf("%llu%llu", &a, &b);
    ull result = karatsuba(a, b);
    printf("Final Ans = %llu\n", result);
}