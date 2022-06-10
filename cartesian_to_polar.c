#define _USE_MATH_DEFINES
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void to_polar(double x, double y, double *r, double *theta) {
    double thetaFinal = 0.f;
    *r = sqrt(x * x + y * y);

    if (x !=  0) {
        if (y != 0) {
            *theta = atan(y / x);
            if ((x > 0 && y > 0) || (x == -y)) {
                thetaFinal = *theta;
            } else if (x < 0 && y > 0) {
                thetaFinal = *theta + M_PI;
            } else if (x < 0 && y < 0) {
                thetaFinal = *theta - M_PI;
            } else if (x > 0 && y < 0) {
                thetaFinal = 2 * M_PI - *theta;
            } else {
                fprintf(stderr, "should not reach here \n");
            }
        }
    } else {
        if (y > 0)
            thetaFinal = M_PI / 2;
        else
            thetaFinal = -(M_PI / 2);
    } if (y == 0) {
        if (x > 0)
            thetaFinal = 0;
        else
            thetaFinal = -M_PI;
    }
    *theta = thetaFinal;
}

double get_rand(double lim1, double lim2) {
    double r = (double)rand() / RAND_MAX;
    return (lim2 - lim1) * r + lim1;
}

void testing() {
    srand(10);
    int NUM_TEST = 5;
    for (int i  = 0; i < NUM_TEST; i++) {
        double r, theta;
        printf("test %d...", i);
        double x = get_rand(-5, 5);
        double y = get_rand(-5, 5);
        
        printf("(%.2g, %.2g)...", x, y);
        to_polar(x, y, &r, &theta);

        assert(fabs(r - hypot(x, y)) < 0.01);
        assert(fabs(theta - atan2(y, x)) < 0.01);
        printf("passed\n");
    }
}

int main() {
    testing();
    return 0;
}
