#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int nthreads;

void *compute(void *arg) {
    long tid = (long) arg;

    printf("hello, I am thread %ld of %d\n", tid, nthreads);

    return (NULL);
}

int main(int argc, char **argv) {
    long i;
    pthread_t *tid;

    if (argc != 2) {
        printf("usage: %s <# of threads>\n", argv[0]);
        exit(-1);
    }

    nthreads = atoi(argv[1]);

    tid = (pthread_t *)malloc(sizeof(pthread_t)*nthreads);

    for (int i = 0; i < nthreads; i++) {
        pthread_create(&tid[i], NULL, compute, (void *) i);
    }

    for (i = 0; i < nthreads; i++) {
        pthread_join(tid[i], NULL);
    }

    printf("exiting main program\n");

    return 0;
}