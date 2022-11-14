#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  int a[10], n, i, j, temp;
  float q1, q3, iqr;

  printf("no. for random numbers :");
  scanf("%d", &n);

  printf("random number generated: \n");
  for (i = 0; i < n; i++) {
    printf("\n%d",a[i]);
  }
  printf("\n");
  printf("\nSorted data");
  for (i = 0; i< n; i++){
    for (j = 0; j < n; j++) {
      if (a[i] < a[j]) {
        temp = a[i];
        a[i] = a[j];
        a[j] = temp;
      }
    }
  }
  for (i = 0; i < n; i++) {
    printf("\n%d", a[i]);
  }

  q1 = a[n / 4];
  printf("\nfirst quartile: %f", q1);
  q3 = a[(3 * n) / 4];
  printf("\nthird quartile: %f", q3);
  iqr = q3 - q1;
  printf("\ninteger quartile range: %f", iqr);

  return 0;
}
