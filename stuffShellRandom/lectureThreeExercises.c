#include <stdio.h>
#include <string.h>

int exerciseOne(char *arr) {

    printf("%s\n", arr);
}

int main(int argc, char *argv[]) {

    /* Exercise #1 */
    char charArr[] = "Hello, World. You can thank Dennis Ritchie for this nonsense.";
    char *ptr1;
    ptr1 = &charArr[0];
    exerciseOne(ptr1);
}