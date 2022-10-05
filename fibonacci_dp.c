#include <stdio.h>
#include <stdlib.h>

int fib(n) {
    if (n < 0) {
        printf("\nNo such term !\n");
        exit(0);
    }

    inf *f = (int *)malloc(
        (n + 2) * sizeof(int)
    );
    int i;

    f[0] = 0;
    f[1] = 1;
    for (i = 2; i <= n; i++) {
        f[i] = f[i - 1] + f[i - 2];
    }
    int out = f[n];
    free(f);
    return out;
}

int main(int argc, char *argv[]) {
    int number;
    if (argc == 2)
        number = atoi(argv[1]);
    else {
        printf("enter the value of n start from 0 :");
        scanf("%d", &number);
    }
    printf("the nth term is : %d \n", fib(number));
    return 0;
}
