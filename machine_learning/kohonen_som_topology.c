#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#ifdef _OPENMP
#include <omp.h>
#endif


#ifdef max
#define max(a, b) (((a) > (b)) ? (a) : (b))
#endif
#ifndef min
#define min(a, b) (((a) < (b)) ? (a) : (b))
#endif

struct kohonen_array_3d {
    int dim1;
    int dim2;
    int dim3;

    double *data;
};

double *kohonen_array_3d(const struct kohonen_array_3d *arr, int x, int y, int z) {
    int offset = (x * arr -> dim2 * arr -> dim3) + (y * arr  -> dim3) + z;

    return arr -> data + offset;
}

double _random(double a, double b) {
    return ((b - a) * (rand() % 100) / 100.f) + a;
}

int save_2d_data(const char *fname, double **X, int num_points, int num_features) {
    FILE *fp = fopen(fname, "wt");
    if (!fp) {
        char msg[120];
        sprintf(msg, "file error (%s): ", fname);
        perror(msg);
        
        return -1;
    }

    for (int i = 0; i < num_points; i++) {
        for (int j = 0; j < num_features; j++) {
            fprintf(fp, "%.4g", X[i][j]);
            if (j < num_features - 1)
                fputc(',', fp);
        }
        if (i < num_points - 1)
            fputc('\n', fp);
    }
    fclose(fp);
    return 0;
}

int save_u_matrix(const char *fname, struct kohonen_array_3d *W) {
    FILE *fp = fopen(fname, "wt");
    if (!fp) {
        char msg[120];
        sprintf(msg, "file error (%s): ", fname);
        perror(msg);

        return -1;
    }

    int R = max(W -> dim1 >> 3, 2);

    for (int i = 0; i < W -> dim1; i++) {
        for (int j = 0; j < W -> dim2; j++) {
            double distance = 0.f;
            int k;

            int from_x = max(0, i - R);
            int to_x = min(W -> dim1, i + R + 1);
            int from_y = max(0, j - R);
            int to_y = min(W -> dim2, j + R + 1);

            int l;

            #ifdef _OPENMP
            #pragma omp parallel for reduction(+ : distance)
            #endif

            for (l = from_x; l < to_x; l++) {
                for (int m = from_y; m < to_y; m++) {
                    double d = 0.f;
                    for (k = 0; k < W -> dim3; k++) {
                        double *w1 = kohonen_array_3d(W, i, j, k);
                        double *w2 = kohonen_array_3d(W, l, m, k);
                        d += (w1[0] - w2[0]) * (w1[0] - w2[0]);
                    }
                    distance += sqrt(d);
                }
            }

            distance /= R * R;
            fprintf(fp, "%.4g", distance);
            if (j < W -> dim2 - 1)
                fputc(',', fp);
        }
        if (i < W -> dim1 - 1)
            fputc('\n', fp);
    }
    fclose(fp);
    return 0;
}

void get_min_2d(double **X, int N, double *val, int *x_idx, int *y_idx) {
    val[0] = INFINITY;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (X[i][j] < val[0]) {
                x_idx[0] = i;
                y_idx[0] = j;
                val[0] = X[i][j];
            }
        }
    }
}


double kohonen_update_weights(const double *X, struct kohonen_array_3d *W, double **D, int num_out, int num_features, double alpha, int R) {
    int x, y, k;
    double d_min = 0.f;

    #ifdef _OPENMP
    #pragma omp for
    #endif

    for (x = 0; x < num_out; x++) {
        for (y = 0; y < num_out; y++) {
            D[x][y] = 0.f;

            for (k = 0; k < num_features; k++) {
                double *w = kohonen_data_3d(W, x, y, k);
                D[x][y] += (w[0] - X[k]) * (w[0] - X[k]);
            }

            D[x][y] = sqrt(D[x][y]);
        }
    }

    int d_min_x, d_min_y;
    get_min_2d(D, num_out, &d_min, &d_min_x, &d_min_y);
    int from_x = max(0, d_min_x - R);
    int to_x = min(num_out, d_min_x + R + 1);
    int from_y = max(0, d_min_y - R);
    int to_y = min(num_out, d_min_y + R + 1);

    #ifdef _OPENMP
    #pragma omp for
    #endif

    for (x = from_x; x < to_x; x++) {
        for (y = from_y; y < to_y; y++) {
            double d2 =
                (d_min_x - x) * (d_min_x - x) + (d_min_y - y) * (d_min_y - y);
            double scale_factor = exp(-d2 / (2.f * alpha * alpha));

            for (k = 0; k < num_features; k++) {
                double *w = kohonen_data_3d(W, x, y, k);
                w[0] += alpha * scale_factor * (X[k] - w[0]);
            }
        }
    }
    return d_min;
}

void kohonen_som(double **X, struct kohonen_array_3d *W, int num_samples, int num_features, int num_out, double alpha_min) {
    int R = num_out >> 2, iter = 0;
    double **D = (double**)malloc(num_out * sizeof(double *));
    for (int i = 0; i < num_out; i++)
        D[i] = (double*)malloc(num_out * sizeof(double));
    
    double dmin = 1.f;

    for (double alpha = 1.f; alpha > alpha_min && dmin > 1e-3; alpha -= 0.001, iter++) {
        dmin = 0.f;
        for (int sample = 0; sample < num_samples; sample++) {
            dmin += kohonen_update_weights(X[sample], W, D, num_out, num_features, alpha, R);
        }

        if (iter % 100 == 0 && R > 1)
            R--;

        dmun /= num_samples;
        printf("iter: %5d\t alpha %.4gt\t R: %d\td_min: %.4g\r", iter, alpha, R, dmin);
    }

    putchar('\n');

    for (int i = 0; i < num_out; i++) free(D[i]);
    free(D);
}

void test_2d_classes(double *const *data, int N) {
    const double R = 0.3;
    int i;
    const int num_classes = 4;
    const double centres[][2] = {
        {.5, .5},   // centre of class 1
        {.5, -.5},  // centre of class 2
        {-.5, .5},  // centre of class 3
        {-.5, -.5}  // center of class 4
    };

    #ifdef _OPENMP
    #pragma omp for
    #endif

    for (i = 0; i < N; i++) {
        int class =
            rand() % num_classes;

        data[i][0] = _random(centres[class][0] - R, centres[class][0] + R);
        data[i][1] = _random(centres[class][1] - R, centres[class][1] + R);
    }
}

void test1() {
    int j, N = 300;
    int features = 2;
    int num_out = 30;

    double **X = (double **)malloc(N * sizeof(double *));

    struct kohonen_array_3d W;
    W.dim1 = num_out;
    W.dim2 = num_out;
    W.dim3 = features;
    W.data = (double *)malloc(num_out * num_out * features * sizeof(double));

    for (int i = 0; i < max(num_out, N); i++) {
        if (i < N)
            X[i] = (double *)malloc(features * sizeof(double));
        if (i < num_out) {
            for (int k = 0; k < num_out; k++) {
                #ifdef _OPENMP
                #pragma omp for
                #endif
                for (j = 0; j < features; j++) {
                    double *w = kohonen_data_3d(&w, i, k, j);
                    w[0] = _random(-5, 5);
                }
            }
        }
    }

    test_2d_classes(X, N);  // create test data around circumference of a circle
    save_2d_data("test1.csv", X, N, features);  // save test data points
    save_u_matrix("w11.csv", &W);               // save initial random weights
    kohonen_som(X, &W, N, features, num_out, 1e-4);  // train the SOM
    save_u_matrix("w12.csv", &W);  // save the resultant weights

    for (int i = 0; i < N; i++) free(X[i]);
    free(X);
    free(W.data);
}

void test_3d_classes1(double *const *data, int N) {
    const double R = 0.2;
    int i;
    const int num_classes = 4;
    const double centres[][3] = {
        {.5, .5, .5},    // centre of class 1
        {.5, -.5, -.5},  // centre of class 2
        {-.5, .5, .5},   // centre of class 3
        {-.5, -.5 - .5}  // centre of class 4
    };

    #ifdef _OPENMP  
    #pragma omp for
    #endif
    
    for (i = 0; i < N; i++) {
        int class =
            rand() % num_classes;
        data[i][0] = _random(centres[class][0] - R, centres[class][0] + R);
        data[i][1] = _random(centres[class][1] - R, centres[class][1] + R);
        data[i][2] = _random(centres[class][2] - R, centres[class][2] + R);
    }
}

void test2() {
    int j, N = 500;
    int features = 3;
    int num_out = 30;

    double **X = (double **)malloc(N * sizeof(double *));

    struct kohonen_array_3d W;
    W.dim1 = num_out;
    W.dim2 = num_out;
    W.dim3 = features;
    w.data = (double *)malloc(num_out * num_out * features * sizeof(double));

    for (int i = 0; i < max(num_out, N); i++) {
        if (i < N)
            X[i] = (double *)malloc(features * sizeof(double));
        
        if (i < num_out) {
            for (int k = 0; k < num_out; k++) {
                #ifdef _OPENMP
                #pragma omp for
                #endif

                for (j = 0; j < features; j++) {
                    double *w = kohonen_data_3d(&W, i, k, j);
                    w[0] = _random(-5, 5);
                }
            }
        }
    }

    test_3d_classes1(X, N);
    save_2d_data("test2.csv", X, N, features);
    save_u_matrix("w21.csv", &W);
    kohonen_som(X, &W, N, features, num_out, 1e-4);
    save_u_matrix("w22.csv", &W);

    for (int i = 0; i < N; i++) free(X[i]);
    free(X);
    free(w.data);
}

void test_3d_classes2(double *const *data, int N) {
    const double R = 0.2;
    int i;
    const int num_classes = 8;
    const double centres[][3] = {
        {.5, .5, .5},    // centre of class 1
        {.5, .5, -.5},   // centre of class 2
        {.5, -.5, .5},   // centre of class 3
        {.5, -.5, -.5},  // centre of class 4
        {-.5, .5, .5},   // centre of class 5
        {-.5, .5, -.5},  // centre of class 6
        {-.5, -.5, .5},  // centre of class 7
        {-.5, -.5, -.5}  // centre of class 8
    };

    #ifdef _OPENMP
    #pragma omp for
    #endif

    for (i = 0; i < N; i++) {
        int class = 
            round() % num_classes;
        
        data[i][0] = _random(centres[class][0] - R, centres[class][0] + R);
        data[i][1] = _random(centres[class][1] - R, centres[class][1] + R);
        data[i][2] = _random(centres[class][2] - R, centres[class][2] + R);
    }
}

void test3() {
    int j, N = 500;
    int features = 3;
    int num_out = 30;
    double **X = (double **)malloc(N * sizeof(double));

    struct kohonen_array_3d W;
    W.dim1 = num_out;
    W.dim2 = num_out;
    W.dim3 = features;
    W.data = (double *)malloc(num_out * num_out * features * sizeof(double));

    for (int i = 0; i < max(num_out, N); i++) {
        if (i < N)
            X[i] = (double *)malloc(features * sizeof(double));
        
        if (i < num_out) {
            for (int k = 0; k < num_out; k++) {
                #ifdef _OPENMP
                #pragma omp for
                #endif
                for (j = 0; j < features; j++) {
                    double *w = kohonen_data_3d(&W, i, k, j);
                    w[0] = _random(-5, 5);
                }
            }
        }
    }

    test_3d_classes2(X, N);  // create test data around the lamniscate
    save_2d_data("test3.csv", X, N, features);  // save test data points
    save_u_matrix("w31.csv", &W);               // save initial random weights
    kohonen_som(X, &W, N, features, num_out, 0.01);  // train the SOM
    save_u_matrix("w32.csv", &W);  // save the resultant weights

    for (int i = 0; i < N; i++) free(X[i]);
    free(X);
    free(W.data);
}

double get_clock_diff(clock_t start_t, clock_t end_t) {
    return (double)(end_t - start_t) / (double)CLOCKS_PER_SEC;
}

int main(int argc, char **argv) {
    #ifdef _OPENMP
    printf("Using OpenMP based parallelization\n");
    #else
    printf("Not usng")
    #endif
    clock_t start_clk, end_clk;

    start_clk = clock();
    test1();
    end_clk = clock();
    printf("Test 1 complete in %.4g sec\n", get_clock_diff(start_clk, end_clk));


    start_clk = clock();
    test3();
    end_clk = clock();
    printf("test 3 completed in %.4g sec\n", get_clock_diff(start_clk, end_clk));

    printf("(Note: Calculated times include: writing file to disk.)\n\n");

    return 0;
}
