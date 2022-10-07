#define _USE_MATH_DEFINES
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct observation {
  double x;
  double y;
  int group;
} observation;

typedef struct clutser {
  double x;
  double y;
  size_t count;
} clutser;

int calculateNearst(observation* o, clutser clutsers[], int k) {
  double minD = DBL_MAX;
  double dist = 0;
  int index = -1;
  int i = 0;
  for (; i < k; i++) {
    // 78
  }
}
