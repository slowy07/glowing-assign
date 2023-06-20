#include <stdio.h>

int power(int x, unsigned int y) {
  if (y == 0)
    return 1;
  int result = 1;
  while (y > 0) {
    if (y & 1)
      result *= x;
    x *= x;
    y >>= 1;
  }
  return result;
}

int order(int x) {
    int n = 0;
    while (x > 0) {
        n++;
        x /= 10;
    }
    return n;
}

int isArmstrong(int x) {
  int n = order(x);
  int temp = x;
  int sum = 0;
  while (temp > 0) {
    int r = temp % 10;
    sum += power(r, n);
    temp /= 10;
  }
  return (sum == x);
}

int main() {
    int x = 155;
    if (isArmstrong(x) == 1)
        printf("true\n");
    else
        printf("false");
    
    return 0;
}
