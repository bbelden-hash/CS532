#include <stdio.h>
#include <stdbool.h>
#include <math.h>

int sumOfDigits(int num) {

    float append = 0;
    int sum = 0;
    float fraction;
    int digit;

    if (num <= 0) {
        return -1;
    }

    while (num > 0) {
        append = (float) num / 10;
        num = num / 10;
        fraction = append - num;
        digit = (int)(fraction * 10.0f + 0.5f);
        sum += digit;
    }

    return sum;

}

int UABMaxMinDiff(int arr[], int size) {

    int min = arr[0];
    int max = arr[0];

    for (int i = 0; i < size; i++) {
        if (arr[i] < min) {
            min = arr[i];
        } if (arr[i] > max) {
            max = arr[i];
        }
    }

    int diff = max - min;
    return diff;

}

int main() {

    int mySum = sumOfDigits(123);
    printf("The sum of the digits represented from the integer passed in as a parameter by the user is: %d\n", mySum);

    int arr[] = {-2, 4, -1, 6, 5};
    int size_arr = sizeof(arr) / sizeof(arr[0]);
    int myDiff = UABMaxMinDiff(arr, size_arr);
    printf("From the array passed in by the user, the integer value computed by subtracting the maximum value from the minimum value from the array is: %d\n", myDiff);

    return 0;

}