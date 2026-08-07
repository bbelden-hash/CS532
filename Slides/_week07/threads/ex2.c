#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *function1(void *someValue) {

    while (1 == 1) {
        sleep(1);
        printf("hey, function1 thread\n");
    }
}

void function2() {

    while(1 == 1) {
        sleep(2);
        printf("hm, function2 thread\n");
    }
}

int main() {

    pthread_t thread_id;
    printf("here, I am inside the main function :<|\n");
    pthread_create(&thread_id, NULL, function1, NULL);
    function2();

    exit(0);
}

/* compile: gcc -Wall ex2.c -o obj/ex2 -lpthread
   run: ./ex2 */