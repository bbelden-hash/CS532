#include <stdio.h>

int main(int argc, char **argv) {
    int x;
    printf("enter an int: \n");
    scanf("%d", &x);
    printf("your number is %d, square of your number is %d\n", x, x*x);

    return 0;
}