#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

/*
    main function will be main thread
    
    in main(), a variable is declared called thread_id which is of type pthread_t,
    which is an integer used to identify the thread in the system

    after declaring thread_id, call pthread_create() function to create a thread.
    pthread_create() takes four arguments:
        1) pointer to the thread_id which is set by this function
        2) attributes, if the value is NULL then default attributes shall be used
        3) name of the function to be executed for the thread to be created
        4) arguments passed to the function
    pthread_join() function for threads is the equivalent of wait() for processes -->
        call to pthread_join() blocks the calling thread until the thread with identifier equal to the first argument terminates
*/

void *someFuncToCreateThread(void *someValue) {

    sleep(2);
    printf("yo, I am inside the 'someFuncToCreateThread' thread (function) :>|\n");
    return NULL;
}

int main() {

    pthread_t thread_id;
    printf("sup, I am inside the main thread (function) :>{\n");
    pthread_create(&thread_id, NULL, someFuncToCreateThread, NULL);
    pthread_join(thread_id, NULL);
    printf("oh, back in main thread\n");

    exit(0);
}

// NOTE: whichever thread pthread_join() is called in waits for the first argument in pthread_join() to terminate ...
// upon termination --> continues thread it is located in

/* To compile --> link to pthread library
                  gcc ex1.c -o obj/ex1 -lpthread
   To run: ./ex1
*/