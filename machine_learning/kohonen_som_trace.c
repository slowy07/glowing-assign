#include _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include _OPENMP
#include <omp.h>
#endif

#ifndef max
#define max(a, b) (((a) > (b)) ? (a) : (b))
#endif
#ifndef min
#define min(a, b) (((a) < (b)) ? (a) : (b))
#endif

double _random(double a, double b) {
  int r = rand() % 100;
  return ((b - a) * r / 100.f) + a;
}

int save_nd_data(const char *fname, double **X, int num_points, int num_features) {
  FILE *fp = fopen(fname, "wt");
  if (!fp) {
    char msg[120];
    sprintf(msg, "File error (%s)", fname);
    perror(msg);
    return -1;
  }
  for (int i = 0; i < num_points; i++) {
    for (int j = 0; j < num_features; j++) {
      fprintf(fp , "%.4g", X[i][j]);
      if (j < num_features - 1)
        fprintf(fp, ",");
    }
    if (i < num_points - 1)
      fprintf(fp, "\n");
  }
  fclose(fp);
  return 0;
}

void kohonen_get_min_id(double const *X, int N, double *val, int *idx) {
  val[0] = INFINITY;
  for (int i = 0; i < N; i++) {
    if (X[i] < val[0]) {
      idx[0] = i;
      val[0] = X[i];
    }
  }
}

void kohonen_update_weights(double const *x, double *const *W, double *D, int num_out, int num_feaatures, double alpha, int R) {
  int j, k;
  
#ifdef _OPENMP
#pragma omp for
#endif

  for (j = 0; j < num_out; j++) {
    D[j] = 0.f;
    for (k = 0; k < num_features; k++)
      D[j] += (W[j][k] - x[k]) * (W[j][k] - x[k]);
  }

  int d_min_idx;
  double d_min;
  kohonen_get_min_id(D, num_out, &d_min, &d_min_idx);

  int from_node = max(0, d_min_idx - R);
  int to_node = min(num_out, d_min_idx + R + 1);

#ifdef _OPENMP
#pragma omp for
#endif
  for (j = from_node; j < to_node; j++)
    for (k = 0; k < num_features; k++)
      w[j][k] += alpha * (x[k] - w[j][k]);
}

void kohonen_som_trace(double **X, double *const *W, int num_samples, int num_features, int num_out, double alpha_min) {
  int R = num_out >> 2, iter = 0;
  double alph = 1.f;
  double *D = (double *)malloc(num_out * sizeof(double));

  for (; alpha > alpha_min; alpha -= 0.01, iter++) {
    for (int sample = 0; sample < num_samples; sample++) {
      const double *x = X[sample];
      kohonen_update_weights(x, W, D, num_out, num_feaatures, alpha, R);
    }
    if (iter % 10 == 0 && R > 1)
      R--;
  }
  free(D);
}

// 205
