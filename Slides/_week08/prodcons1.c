#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

/* 
NOTE:
The producer can generate items and store them in the buffer at its own pace -->
    each time, an index (in) into the buffer is incremented
The consumer proceeds in a similar fashion but must make sure that it does not attempt to read from an empty buffer -->
    the consumer makes sure that the producer has advanced beyond it (in > out) before proceeding 
*/

/* Solution to the single Producer/Consumer problem using semaphores. 
    
   to enable printing add -DDEBUG to compile
   gcc -O -Wall -DDEBUG -o <filename> <filename>.c -lpthread 
*/

#define NBUFF 10

int nitems; // global variable, number of items the producer will produce and the consumer will consume

struct { // shared between the producer and consumer threads
    int buff[NBUFF]; // buffer
    sem_t mutex; // mutex lock
    sem_t nempty; // number of empty slots
    sem_t nstored; // number of filled slots
} shared;

void *producer(void *);
void *consumer(void *);

/* 
in main --> read the number of items to be produced/consumed as a command-line argument
initialize the three semaphores using sem_init
create two separate threads, one for the producer and one for the consumer, and wait for the two threads to complete 
*/

int main(int argc, char **argv) {

    pthread_t tid_producer;
    pthread_t tid_consumer;

    if (argc != 2) {
        printf("usage: %s <#items>\n", argv[0]);
        exit(-1);
    }

    nitems = atoi(argv[1]);

    sem_init(&shared.mutex, 0, 1);
    sem_init(&shared.nempty, 0, NBUFF);
    sem_init(&shared.nstored, 0, 0);

    pthread_create(&tid_producer, NULL, producer, NULL);
    pthread_create(&tid_consumer, NULL, consumer, NULL);

    pthread_join(tid_producer, NULL);
    pthread_join(tid_consumer, NULL);

    sem_destroy(&shared.mutex);
    sem_destroy(&shared.nempty);
    sem_destroy(&shared.nstored);

    return 0;
}

void *producer(void *arg) {

    for (int i = 0; i < nitems; i++) {
        sem_wait(&shared.nempty); // wait for at least 1 empty slot
        sem_wait(&shared.mutex);

        /* since mutex is initially set to 1 ... (sem_wait decrements 1 to 0)
            the producer thread enters the critical section and assigns the value i to the buffer location -->
            i % NBUFF 
        */
        shared.buff[i % NBUFF] = i; // store i into circular buffer
#ifdef DEBUG
    printf("wrote %d to buffer at location %d\n", i, i % NBUFF);
#endif
        
        sem_post(&shared.mutex); // release the mutex (increments the mutex back to 1)
        sem_post(&shared.nstored); // increments # of elements stored in the buffer (nstored)
    }

    return (NULL);
}

void *consumer(void *arg) {

    /* consumer thread will enter the loop and wait on the semaphore nstored ...
        initially nstored is set to 0, this call will block and the consumer will wait until the producer posts on the semaphore nstored 
    */

    for (int i = 0; i < nitems; i++) {
        sem_wait(&shared.nstored);
        sem_wait(&shared.mutex);

        /* when the producer posts on the semaphore nstored, 
           the consumer will return from sem_wait on nstored and invoke the sem_wait on the semaphore mutex
           if the producer is not in the critical section, the consumer will obtain the mutex sempahore, 
           consume the buffer (check if the value in the buffer match the corresponding (loop index mod NBUFF) and print an error message in case they dont match).
           and release the mutex by calling sem_post on the mutex semaphore
        */

        if (shared.buff[i % NBUFF] != i) {
            printf("error: buff[%d] = %d\n", i, shared.buff[i % NBUFF]);
#ifdef DEBUG
    printf("read %d from buffer at location %d\n", shared.buff[i % NBUFF], i % NBUFF);
#endif
        }

        /* consumer thread will post the sem_post on the semaphore nempty to indicate to the producer that now there is an empty slot
           consumer thread terminates when the loop completes
        */

        sem_post(&shared.mutex);
        sem_post(&shared.nempty);
    }

    return (NULL);
}

/* 
                         MAIN
                          |
              initialize semaphores
                          |
             ┌────────────┴────────────┐
             ↓                         ↓
        PRODUCER                    CONSUMER
             |                         |
       wait(nempty)              wait(nstored)
             |                         |
       wait(mutex)               wait(mutex)
             |                         |
             ↓                         ↓
       WRITE BUFFER                READ BUFFER
             |                         |
             ↓                         ↓
       post(mutex)                post(mutex)
             |                         |
       post(nstored)              post(nempty)
             |                         |
             └───────────┬─────────────┘
                         ↓
                   repeat until
                    nitems done
                         |
                         ↓
                   threads finish
                         |
                         ↓
                       MAIN
                     finishes

Producer:
    take mutex
       ↓
    write ONE element
       ↓
    release mutex

Consumer:
    take mutex
       ↓
    read ONE element
       ↓
    release mutex
*/
