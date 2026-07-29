#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

/* write a program to handle a simple signal that catches either of the two user-defined signals
   prints the signal number ... */

static void sig_usr(int signo) {

    /* create a user-defined function (signal handler) that will be invoked when a signal is recieved: */

    if (signo == SIGUSR1) {
        printf("recieved SIGUSR1\n");
    } else if (signo == SIGUSR2) {
        printf("recieved SIGUSR2\n");
    } else {
        printf("recieved signal %d\n", signo);
    }

}

int main(void) {

    /* now let's call above user-defined signal */

    if (signal(SIGUSR1, sig_usr) == SIG_ERR) {
        printf("can't catch SIGUSR1\n");
        exit(-1);
    }

    if (signal(SIGUSR2, sig_usr) == SIG_ERR) {
        printf("can't catch SIGUSR2\n");
        exit(-1);
    }

    /* this is an infinite loop. pause() suspends the process until any signal is delivered.
       instead of wasting CPU time, the process sleeps until a signal arrives. */
    for ( ; ; ) {
        pause();
    }

    return 0;
}

/* execute a program in the background by typing program name followed by symbol & at the end 
   returns command-prompt w/ background process number and corresponding PID of the process that was created 
   
   display various jobs that are currently running in the background using "jobs" 
   
   to terminate --> "kill -signal_name pid" 
   -signal_name A symbolic signal name specifying the signal to be sent instead of the default TERM 
   
   kill -USR1 5324 ... send the SIGUSR1 signal to process 5324
   kill -STOP PID ... suspends 
   kill -CONT PID ... continues, running 
   kill -TERM %1,PID ... terminates for good */