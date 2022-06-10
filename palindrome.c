#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

bool isPalindrome(int number);

int main() {
    assert(isPalindrome(0));
    assert(isPalindrome(1));
    assert(isPalindrome(12321));
    assert(!isPalindrome(1234));

    return 0;
}

bool isPalindrome(int number) {
    int reversedNumber = 0;
    int originalNumber = number;
    while (number != 0) {
        int remainder = number % 10;
        reversedNumber = reversedNumber * 10 + remainder;
        number /= 10;
    }
    return originalNumber == reversedNumber;
}
