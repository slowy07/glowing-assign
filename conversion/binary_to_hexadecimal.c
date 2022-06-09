#include <stdio.h>

int main() {
    long int binary, hexa = 0, i = 1, remainder;

    printf("enter binary number: ");
    scanf("%ld", &binary);

    while (binary != 0) {
        remainder = binary % 10;
        hexa = hexa + remainder * i;
        i = i * 2;
        binary = binary / 10;
    }
    printf("the equivalent hexadecimal: a%lX", hexa);

    return 0;
}