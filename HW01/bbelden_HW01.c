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

int main() {

    int mySum = sumOfDigits(-308);
    printf("The sum of the digits represented from the integer passed in as a parameter by the user is: %d\n", mySum);

    return 0;
}