#include <stdio.h>
#include <stdlib.h>

void fillArray(float arr[], int N) {

    for (int i = 0; i < N; i++) {
        printf("Please enter element %d of array: \n", (i + 1));
        scanf("%f", &arr[i]);
    }

    printf("The array is:\n");
    printf("[ ");
    for (int i = 0; i < (N - 1); i++) {
        printf("%f, ", arr[i]);
    }
    printf("%f ]\n", arr[N - 1]);
}

void insertionSort(float arr[], int size) {


    for (int i = 1; i < size; i++) {
        float temp = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > temp) {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = temp;
    }

    printf("Sorted array is: \n");
    printf("[ ");
    for (int n = 0; n < size - 1; n++) {
        printf("%f, ", arr[n]);
    }
     printf("%f ]\n", arr[size - 1]);
}

int main() {

    int size = 5;
    float arr[size];
    fillArray(arr, size);
    insertionSort(arr, size);
    return 0;
}