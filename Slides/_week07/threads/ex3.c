#include <stdio.h>
#include <pthread.h>

int globalVar = 50; // define a global variable

void *someFuncToCreateThread(void *someValue) {

    int *threadId = (int *) someValue; // store the value argument passed to this thread

    // define a static and a local variable
    static int staticVar = 75;
    int localVar = 10;

    // change the variables
    globalVar += 100;
    staticVar += 100;
    localVar += 100;
    printf("id = %d, global = %d, local = %d, static = %d, \n", *threadId, globalVar, localVar, staticVar);

    return NULL;
}

int main() {

    int i;
    pthread_t thread_id;
    int threadIds[4];
    for (i = 0; i < 4; i++) {
        threadIds[i] = i;
        pthread_create(&thread_id, NULL, someFuncToCreateThread, (void *) &threadIds[i]);
    }
    pthread_exit(NULL);
}
