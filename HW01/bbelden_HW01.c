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

void replaceEvenWithZero(int *p, int size) {

    for (int i = 0; i < size; i++) {
        if (*p % 2 == 0) {
            *p = 0;
        }
        p++;  
    }

}

bool perfectSquare(int n) {

    for (int i = 0; i <= n / 2; i++) {
        if (i * i == n) {
            return true;
        }
    }

    return false;
}

int countVowels(char *l, int size) {

    int numOfVowels = 0;

    char vowels[10] = {'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'};

    for (int i = 0; i < size; i++) {
        for (int n = 0; n < 10; n++) {
            if (*l == vowels[n]) {
                numOfVowels += 1;
            }
        }
        l++;
    }

    return numOfVowels;

}


int main() {

    /* intro */ 
    printf("\nblazerID: bbelden || Systems Programming\n");

    /* call to 'sumOfDigits' */
    int mySum = sumOfDigits(123);
    printf("the sum of the digits represented from the integer passed in as a parameter by the user is: %d\n", mySum);

    /* call to 'UABMaxMinDiff' */
    int arr[] = {-2, 4, -1, 6, 5};
    int size_arr = sizeof(arr) / sizeof(arr[0]);
    int myDiff = UABMaxMinDiff(arr, size_arr);
    printf("from the array passed in by the user, the integer value computed by subtracting the maximum value from the minimum value from the array is: %d\n", myDiff);

    /* call to 'replaceEvenWithZero' */
    int arr2[] = {1, 3, 5};
    int size_arr2 = sizeof(arr2) / sizeof(arr2[0]);
    int *ptr1;
    ptr1 = &arr2[0];
    replaceEvenWithZero(ptr1, size_arr2);
    printf("the values in my new array, replacing even integers with 0, are : ");
    for (int i = 0; i < size_arr2; i++) {
        printf("%d\t", *ptr1);
        ptr1++;  
    }
    printf("\n");

    /* call to 'perfectSquare' */
    int numPerfect = 36;
    bool isPerfectSquare = perfectSquare(numPerfect);
    if (isPerfectSquare) {
        printf("the number %d is a perfect square.\n", numPerfect);
    } else {
        printf("the number %d is not a perfect square.\n", numPerfect);
    }

    /* call to 'countVowels' */
    char str[] = "Clayface";
    int size_str = sizeof(str) / sizeof(str[0]);
    char *ptr2;
    ptr2 = &str[0];
    int vowels = countVowels(ptr2, size_str);
    printf("the number of vowels in the 'str[]' variable is/are: %d\n", vowels);

    /* outro */
    printf("looking for a royale w/ cheese\n\n");


    return 0;

}