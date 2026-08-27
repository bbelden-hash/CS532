#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define min(a, b) (((a) < (b)) ? (a) : (b))
#define NBUFF 10
#define MAXNTHREADS 100

int nitems;
int nproducers;

struct {
    int buff[NBUFF];
    int nput;
    int nputval;
    sem_t mutex;
    sem_t nempty;
    sem_t nstored;
} shared;

void *producer(void *);
void *consumer(void *);

int main(int argc, char **argv) {

    int i;
    int prodcount[MAXNTHREADS];
    pthread_t tid_producer[MAXNTHREADS];
    pthread_t tid_consumer;

    if (argc != 3) {
        printf("usage: %s <#item> <#producers>\n", argv[0]);
        exit(-1);
    }

    nitems = atoi(argv[1]);
    nproducers = min(atoi(argv[2]), MAXNTHREADS);

    sem_init(&shared.mutex, 0, 1);
    sem_init(&shared.nempty, 0, NBUFF);
    sem_init(&shared.nstored, 0, 0);

    for (i = 0; i < nproducers; i++) {
        prodcount[i] = 0;
        pthread_create(&tid_producer[i], NULL, producer, &prodcount[i]);
    }
    pthread_create(&tid_consumer, NULL, consumer, NULL);

    for (i = 0; i < nproducers; i++) {
        pthread_join(tid_producer[i], NULL);
        printf("producer count[%d] = %d\n", i, prodcount[i]);
    }
    pthread_join(tid_consumer, NULL);

    sem_destroy(&shared.mutex);
    sem_destroy(&shared.nempty);
    sem_destroy(&shared.nstored);

    return 0;
}

void *producer (void *arg) {

    for ( ; ; ) {
        sem_wait(&shared.nempty);
        sem_wait(&shared.mutex);

        if (shared.nput >= nitems) {
            sem_post(&shared.mutex);
            sem_post(&shared.nempty);
            return(NULL);
        }

        shared.buff[shared.nput % NBUFF] = shared.nputval;
#ifdef DEBUG
        printf("wrote %d to buffer at location %d\n", shared.nputval, shared.nput % NBUFF);
#endif

        shared.nput++;
        shared.nputval++;

        sem_post(&shared.mutex);
        sem_post(&shared.nstored);
        *((int *) arg) += 1; //prodcount[i]++
    }
}

void *consumer(void *arg) {

    int i;

    for (i = 0; i < nitems; i++) {
        sem_wait(&shared.nstored);
        sem_wait(&shared.mutex);

        if (shared.buff[i % NBUFF] != i) {
            printf("error: buff[%d] = %d\n", i, shared.buff[i % NBUFF]);
        }
#ifdef DEBUG
        printf("read %d from buffer at location %d\n", shared.buff[i % NBUFF], i % NBUFF);
#endif

        sem_post(&shared.mutex);
        sem_post(&shared.nempty);
    }

    return (NULL);
}
