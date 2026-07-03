#include <stdio.h>
#include <stdlib.h>

float fillArray(int N) {

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

void insertionSort(float *p, int size) {

    for (int i = 0; i < size; i++) {
        int j = i + 1;
        
    }




}

int main() {

    int size = 9;
    float arr1 = fillArray(size);


    return 0;
}