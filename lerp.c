#include <math.h>
#include <stdio.h>

float lerp(float k0, float k1, float t) {
    return k0 + t * (k1 - k0);
}

float lerp_precise(int k0, int k1, float t) {
    return (1 - t) * k0 + t * k1;
}

int main() {
    float start = 0;
    float finish = 5;
    float steps = 0;

    printf("input number, thiss is the bigger of the lerp:\n");
    scanf("%f", &finish);
    
    printf(
        "input number, thiss is how many step you want to divide by lerp:\n"
    );
    scanf("%f", &steps);

    for (int i = 0; i < steps + 1; i++) {
        printf("%f\n", lerp(start, finish, i / finish));
    }

    return 0;
}
