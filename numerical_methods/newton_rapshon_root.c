#include <complex.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ACCURACY 1e-10

double complex func(double complex x) {
    return x * x - 3.;
}

double complex d_func(double complex x) { return 2. * x; }

int main(int argc, char **argv) {
    double delta = 1;
    double complex cdelta = 1;

    srand(time(NULL));

    double complex root = (rand() % 100 - 50) + (rand() % 100 - 50) * I;
    unsigned long counter = 0;
    while (delta > ACCURACY && counter < ULONG_MAX) {
        cdelta = func(root) / d_func(root);
        root += -cdelta;
        counter++;
        delta = fabs(cabs(cdelta));

        #if defined(DEBUG) || !defined(NDEBUG)
        if (counter % 50 == 0) {
            double r = creal(root);
            double c = cimag(root);

            printf("Iter %5lu: Root: %4.4g%c%4.4gi\t\tdelta: %.4g\n", counter,
                   r, c >= 0 ? '+' : '-', c >= 0 ? c : -c, delta);
        }
        #endif
    }

    double r = creal(root);
    double c = fabs(cimag(root)) < ACCURACY ? 0 : cimag(root);

    printf("Iter %5lu: Root: %4.4g%c%4.4gi\t\tdelta: %.4g\n", counter, r,
           c >= 0 ? '+' : '-', c >= 0 ? c : -c, delta);
    
    return 0;
}
