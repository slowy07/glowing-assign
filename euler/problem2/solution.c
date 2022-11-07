#include <stdio.h>

int main() {
  int n = 0;
  int sum = 0;
  int i = 1;
  int j = 2;
  int temp;
  scanf("%d", &n);

  while (j <= n) {
    if ((j & 1) == 0) {
      sum += j;
    }
    temp = i;
    i = j;
    j = temp + i;
  }
  printf("%d\n", sum);
  return 0;
}
