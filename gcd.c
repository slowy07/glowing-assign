#include <stdio.h>

int gcd(int x, int y) {
    if (y == 0)
        return x;
    return gcd(y, x % y);
}

int main() {
    int a, b;
    
    printf("input two number: \n");
    scanf("%d %d", &a, &b);
    printf("gcd: %d\n", gcd(a, b));
    
    return 0;
}
