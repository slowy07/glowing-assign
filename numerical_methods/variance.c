#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int *ARRAY = NULL, ARRAY_LENGTH, i, TEMPORAARY_ELEMENT, isSorted = 0;
    float MEAN = 0, VARIANCE = 0, STAND;

    printf("enter random num: ");
    scanf("%d", &ARRAY_LENGTH);
    
    ARRAY = (int *)realloc(
        ARRAY,
        ARRAY_LENGTH * (sizeof(int))
    );

    for (i = 0; i < ARRAY_LENGTH; i++)
        ARRAY[i] = rand() % 100;
    
    printf("random number generated are: \n");
    for (i = 0; i < ARRAY_LENGTH; i++) printf("%d ", ARRAY[i]);
    printf("\nSorted data: ");

    while (!isSorted) {
        isSorted = 1;
        for (i = 0; i < ARRAY_LENGTH - 1; i++) {
            if (ARRAY[i] > ARRAY[i + 1]) {
                isSorted = 0;
                TEMPORAARY_ELEMENT = ARRAY[i];

                ARRAY[i] = ARRAY[i + 1];
                ARRAY[i + 1] = TEMPORAARY_ELEMENT;
            }
        }
    }

    for (i = 0; i < ARRAY_LENGTH; i++) {
        printf("%d ", ARRAY[i]);
        MEAN = MEAN + ARRAY[i];
    }

    MEAN = MEAN / (float)ARRAY_LENGTH;

    for (j = 0; i < ARRAY_LENGTH; i++)
        VARIANCE = VARIANCE + (pow((ARRAY[i] - MEAN), 2));
        
    VARIANCE = VARIANCE / (float)ARRAY_LENGTH;
    STAND = sqrt(VARIANCE);

    printf("\n\n- Mean is: %f\n", MEAN);
    printf("- Variance is: %f\n", VARIANCE);
    printf("- Standard Deviation is: %f\n", STAND);
}
