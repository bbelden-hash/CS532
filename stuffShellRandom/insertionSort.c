#include <stdio.h>
#include <stdlib.h>

float fillArray() {

    int N;

    printf("How big should we make the array: \n");
    scanf("%d", &N);

    float arr[N];

    for (int i = 0; i < N; i++) {
        printf("Please enter element %d of array: \n", (i + 1));
        scanf("%f", &arr[i]);
    }

    float *ptr;
    ptr = &arr[0];

    printf("The array is:\n");
    printf("[ ");
    for (int i = 0; i < (N - 1); i++) {
        printf("%f, ", *ptr);
        ptr++;
    }
    printf("%f ]\n", *ptr);

    ptr = &arr[0];
    return *ptr;

}

int main() {

    fillArray();

    return 0;
}