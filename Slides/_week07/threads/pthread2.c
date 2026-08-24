#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int nthreads;

void *compute(void *arg) {
    long tid = (long) arg;
    pthread_t pthread_id = pthread_self();

    printf("hello, I am thread %ld of %d, pthread_self() = %lu (0x%lx)\n",
        tid,
        nthreads,
        (unsigned long) pthread_id,
        (unsigned long) pthread_id
    );

    return (NULL);
}

int main(int argc, char **argv) {
    long i;
    pthread_t *tid;
    pthread_t pthread_id = pthread_self();

    if (argc != 2) {
        printf("usage: %s <# of threads>\n", argv[0]);
        exit(-1);
    }

    nthreads = atoi(argv[1]);

    tid = (pthread_t *)malloc(sizeof(pthread_t)*nthreads);

    for (i = 0; i < nthreads; i++) {
        pthread_create(&tid[i], NULL, compute, (void *) i);
    }

    for (i = 0; i < nthreads; i++) {
        printf("tid[%ld] = %lu (0x%lx)\n", i, tid[i], tid[i]);
    }

    printf("hello, I am main thread. pthread_self() = %lu (0x%lx)\n",
        (unsigned long) pthread_id,
        (unsigned long) pthread_id
    );

    for (i = 0; i < nthreads; i++) {
        pthread_join(tid[i], NULL);
    }

    printf("exiting main program\n");

    return 0;
}

/* overall flow of the above program looks as so ...

                    MAIN THREAD
                         │
                         │ pthread_self()
                         ↓
                  Get main's ID
                         │
                         ↓
                  nthreads = 3
                         │
                         ↓
                  malloc 3 IDs
                         │
             ┌───────────┼───────────┐
             │           │           │
             ↓           ↓           ↓
          create 0    create 1    create 2
             │           │           │
             ↓           ↓           ↓
          Worker 0    Worker 1    Worker 2
             │           │           │
      pthread_self() pthread_self() pthread_self()
             │           │           │
             ↓           ↓           ↓
          compute()    compute()    compute()
             │           │           │
             ↓           ↓           ↓
           finish      finish      finish
             │           │           │
             └───────────┼───────────┘
                         │
                         ↓
                  pthread_join()
                         │
                         ↓
               Main continues
                         │
                         ↓
              "exiting main program"
                         │
                         ↓
                       EXIT

*/