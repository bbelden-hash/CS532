#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define sizeTask2 100

double task2(double *p, int size) {

    srand48((unsigned int) time(NULL));
    *p = drand48();
    double min = *p;

    printf("%f ", *p);
    p++;

    for (int i = 1; i < size; i++) {
        *p = drand48();
        printf("%f ", *p);
        if (*p < min) {
            min = *p;
        }
        p++;
    }
    printf("\n");

    return min;
}

void buildArray(double *p, int size) {

    srand48((unsigned int) time(NULL));

    for (int i = 0; i < size; i++) {
        *p = drand48();
        p++;
    }

}

void insertionSort(double *p, int size) {

    for (int i = 1; i < size; i++) {
        double key = p[i];
        int j = i - 1;

        while (j >= 0 && p[j] > key) {
            p[j + 1] = p[j];
            j = j - 1; 
        }
        p[j + 1] = key;
    }
}

void printArray(double *p, int size) {

    for (int i = 0; i < size; i++) {
        printf("%f ", *p);
        p++;
    }

    printf("\n");
    
}


int main() {

    /* task 2 */
    static double arr1[sizeTask2];
    double *ptr1;
    ptr1 = &arr1[0];
    double min = task2(ptr1, sizeTask2);
    printf("The smallest double in my array from 'task 2' is: %f\n\n", min);

    /* lab02 assignment */
    int sizeLab2;
    printf("Hi user! I am going to create an array. How big should we make this array: \n");
    scanf("%d", &sizeLab2);
    double arr2[sizeLab2];
    double *ptr2;
    ptr2 = &arr2[0];
    buildArray(ptr2, sizeLab2);
    insertionSort(ptr2, sizeLab2);
    printf("After a very nifty insertion sort, our, sized by yourself, array looks as so ... \n");
    printArray(ptr2, sizeLab2);

}