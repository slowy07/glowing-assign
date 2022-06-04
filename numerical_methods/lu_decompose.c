#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#ifdef _OPENMP
#include <omp.h>
#endif

/** Perform LU decomposition on matrix
 * \param[in] A matrix to decompose
 * \param[out] L output L matrix
 * \param[out] U output U matrix
 * \param[in] mat_size input square matrix size
 */
int lu_decomposition(double **A, double **L, double **U, int mat_size)
{
    int row, col, j;

    for (row = 0; row < mat_size; row++)
    {
#ifdef _OPENMP
#pragma omp for
#endif
        for (col = row; col < mat_size; col++)
        {
            double lu_sum = 0.;
            for (j = 0; j < row; j++) lu_sum += L[row][j] * U[j][col];
            U[row][col] = A[row][col] - lu_sum;
        }

#ifdef _OPENMP
#pragma omp for
#endif
        for (col = row; col < mat_size; col++)
        {
            if (row == col)
            {
                L[row][col] = 1.;
                continue;
            }

            // Summation of L[i,j] * U[j,k]
            double lu_sum = 0.;
            for (j = 0; j < row; j++) lu_sum += L[col][j] * U[j][row];

            // Evaluate U[i,k]
            L[col][row] = (A[col][row] - lu_sum) / U[row][row];
        }
    }

    return 0;
}
void display(double **A, int N)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf("% 3.3g \t", A[i][j]);
        }
        putchar('\n');
    }
}

int main(int argc, char **argv) {
    int mat_size = 3;
    const int range = 10;
    const int range2 = range >> 1;

    if (argc == 2)
        mat_size = atoi(argv[1]);

    srand(time(NULL));
    double **A = (double **)malloc(mat_size * sizeof(double *));
    double **L = (double **)malloc(mat_size * sizeof(double *));  
    double **U = (double **)malloc(mat_size * sizeof(double *)); 
    for (int i = 0; i < mat_size; i++) {
        // calloc so that all valeus are '0' by default
        A[i] = (double *)calloc(mat_size, sizeof(double));
        L[i] = (double *)calloc(mat_size, sizeof(double));
        U[i] = (double *)calloc(mat_size, sizeof(double));
        for (int j = 0; j < mat_size; j++)
            A[i][j] = (double)(rand() % range - range2);
    }

    lu_decomposition(A, L, U, mat_size);

    printf("A = \n");
    display(A, mat_size);
    printf("\nL = \n");
    display(L, mat_size);
    printf("\nU = \n");
    display(U, mat_size);
    for (int i = 0; i < mat_size; i++) {
        free(A[i]);
        free(L[i]);
        free(U[i]);
    }
    free(A);
    free(L);
    free(U);

    return 0;
}