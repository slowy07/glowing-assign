#include <complex.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ACCURACY 1e-10

long double complex poly_function(long double *coeffs, unsigned int degree, long double complex x) {
  long double complex out = 0.;
  unsigned int n;
  for (n = 0; n < degree; n++) out += coeffs[n] * cpow(x, degree - n - 1);
  return out;
}

const char *complex_str(long double complex x) {
  static char msg[50];
  double r = creal(x);
  double c = cimag(x);

  sprintf(msg, "% 7.04g%+7.04gj", r, c);
  return msg;
}

char check_termination(long double delta) {
  static long double past_delta = INFINITY;
  if (fabsl(past_delta - delta) <= ACCURACY || delta < ACCURACY)
    return 1;
  past_delta = delta;
  return 0;
}

int main(int argc, char **argv) {
  long double *coeffs = NULL;
  long double complex *s0 = NULL;
  unsigned int degree = 0;
  unsigned int n, i;
  
  if (argc < 2) {
    printf("pass the coefficient of polynomial as commandline argument\n.");
    return 0;
  }

  degree = argc - 1;
  coeffs = (long double *)malloc(
    degree * sizeof(long double));
  s0 = (long double complex *)malloc(
    (degree - 1) *
    sizeof(long double complex));

  srand(time(NULL));

  if (!coeffs || !s0) {
    perror("unable to allocate memory");
    if (coeffs)
      free(coeffs);
    if (s0)
      free(s0);
    return EXIT_FAILURE;
  }

#if defined(DEBUG) || !defined(NODEBUG)
  FILE *log_file = fopen("durand_kerner.log.csv", "wt");
  if (!log_file) {
    perror("unable to create log files");
    free(coeffs);
    free(s0);
    return EXIT_FAILURE;
  }
  fprintf(log_file, "iter#,");
#endif

  printf("computing the roots for:\n\t");
  for (n = 0; n < degree; n++) {
    coeffs[n] = strtod(argv[n + 1], NULL);
    if (n < degree - 1 && coeffs[n] != 0)
      printf("(%Lg) x^%d + ", coeffs[n], degree - n - 1);
    else if (coeffs[n] != 0)
      printf("(%Lg) x^%d = 0\n", coeffs[n], degree - n - 1);

    double tmp;
    if (n > 0) 
      coeffs[n] /= tmp;
    else {
      tmp = coeffs[0];
      coeffs[0] = 1;
    }
    
    if (n < degree - 1) {
      s0[n] = (long double)rand() + (long double)rand() * I;
#if defined(DEBUG) || !defined(NDEBUG)
      fprintf(log_file, "root_%d,", n);
#endif
    }
  }
#if defined(DEBUG) || !defined(NDEBUG)
  fprintf(log_file, "avg. correction");
  fprintf(log_file, "\n0,");
  for (n = 0; n < degree - 1; n++)
    fprintf(log_file, "%s,", complex_str(s0[n]));
#endif
  double tol_condition = 1;
  unsigned long iter = 0;

  clock_t end_time, start_time = clock();
  while(!check_termination(tol_condition) && iter < INT_MAX) {
    long double complex delta = 0;
    tol_condition = 0;
    iter++;
    
#if defined(DEBUG) || !defined(NDEBUG)
    fprintf(log_file, "\n%ld", iter);
#endif
    for (n = 0; n < degree - 1; n++) {
      long double complex numerator =
        poly_function(coeffs, degree, s0[n]);
      long double complex denominator = 1.0;
      for (i = 0; i < degree - 1; i++)
        if (i != n)
          denominator *= s0[n] - s0[i];
      delta = numerator / denominator;

      if (isnan(cabsl(delta)) || isinf(cabsl(delta))) {
        printf("\noverflow/underrun error - get val = %Lg", cabsl(delta));
        goto end;
      }
      s0[n] -= delta;
      tol_condition = fmaxl(tol_condition, fabsl(cabsl(delta)));

#if defined(DEBUG) || !defined(NDEBUG)
      fprintf(log_file, "%s,", complex_str(s0[n]));
#endif
    }

#if defined(DEBUG) || !defined(NDEBUG)
    if (iter % 500 == 0) {
      printf("iter %lu\t", iter);
      for (n = 0; n < degree - 1; n++) printf("\t%s", complex_str(s0[n]));
      printf("\t\tabsolute average change: %.4g\n", tol_condition);
    }
    fprintf(log_file, "%.4g", tol_condition);
#endif
  }
end:
  end_time = clock();

#if defined(DEBUG) || !defined(NDEBUG)
  fclose(log_file);
#endif

  printf("\niteration: %lu\n", iter);
  for(n = 0; n < degree - 1; n++) printf("\t%s\n", complex_str(s0[n]));
  printf("absolute average change: %.4g\n", tol_condition);
  printf("Time taken: %.4g sec\n",
      (end_time - start_time) / (double)CLOCKS_PER_SEC);
  free(coeffs);
  free(s0);

  return 0;
}
