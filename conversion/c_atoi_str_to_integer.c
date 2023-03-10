#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int c_atoi(const char *str) {
  int i;
  int sign;
  long value;
  long prev;

  i = 0;
  sign = 0;
  value = 0;

  while (((str[i] <= 13 && str[i] >= 9) || str[i] == 32) && str[i] != '\0')
    ++i;

  if (str[i] == '-') {
    sign = -1;
    i++;
  } else if (str[i] == '+') {
    sign = 1;
    i++;
  }

  while (str[i] >= 48 && str[i] <= 57 && str[i] != '\0') {
    prev = value;
    value = value * 10 + sign * (str[i] - '0');

    if (sign == 1 && prev > value)
      return (-1);
    else if (sign == -1 && prev < value)
      return (0);
    i++;
  }
  return (value);
}

void test_c_atoi() {
  printf("<<<< TEST FUNCTION >>>>\n");
  assert(c_atoi("123") == atoi("123"));
  assert(c_atoi("-123") == atoi("-123"));
  assert(c_atoi("") == atoi(""));
  assert(c_atoi("-h23") == atoi("-h23"));
  assert(c_atoi("         23") == atoi("         23"));
  assert(c_atoi("999999999") == atoi("999999999"));
  printf("<<<< TEST DONE >>>>\n");
}

int main(int argc, char **argv) {
  test_c_atoi();

  if (argc == 2) {
    printf("number + 5 %d \n", c_atoi(argv[1]) + 5);
    return (0);
  }
  printf("wrong number\n");
  return (1);
}
