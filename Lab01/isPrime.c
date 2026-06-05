#include <stdio.h>
#include <stdbool.h>

/* 
C program to check whether a number inserted by the user ...
is prime or not 
*/

int givenNumber() {
    int number;

    printf("Enter a number, any number: ");
    scanf("%d", &number);

    return number;
}

bool checkPrime(int num) {

    if (num < 2) {
        return false;
    }

    for (int i = 2; i < num; i++) {
        if (num % i == 0) {
            return false;
        }
    }

    return true;
}

int main() {

    int check = givenNumber();
    bool isPrime = checkPrime(check);

    if (isPrime) {
        printf("%d is a prime number.\n", check);
    } else {
        printf("%d is not a prime number.\n", check);
    }

    return 0;
}




