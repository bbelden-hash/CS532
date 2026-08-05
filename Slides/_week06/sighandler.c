#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

/* handle other signal generated from keyboard such as:
   Ctrl + C (SIGINT) 
   Ctrl + Z (SIGTSTP)
   Ctrl + \ (SIGQUIT) 
   use a single signal handler to handle all these signals using a switch statement */

static void sig_usr(int signo) {

    switch(signo) {

        case SIGINT:
            printf("received SIGINT signal %d\n", signo);
            break;
        case SIGQUIT:
            printf("received SIGQUIT signal %d\n", signo);
            break;
        case SIGUSR1:
            printf("received SIGUSR1 signal %d\n", signo);
            break;
        case SIGUSR2:
            printf("received SIGUSR2 signal %d\n", signo);
            break;
        case SIGTSTP:
            printf("received SIGTSTP signal %d\n", signo);
            break;
        default:
            printf("received signal %d\n", signo);
    }

}

int main(void) {

    if (signal(SIGINT, sig_usr) == SIG_ERR) {
        printf("can't catch SIGINT\n");
        exit(-1);
    }
    if (signal(SIGQUIT, sig_usr) == SIG_ERR) {
        printf("can't catch SIGQUIT\n");
        exit(-1);
    }
    if (signal(SIGUSR1, sig_usr) == SIG_ERR) {
        printf("can't catch SIGUSR1\n");
        exit(-1);
    }
    if (signal(SIGUSR2, sig_usr) == SIG_ERR) {
        printf("can't catch SIGUSR2\n");
        exit(-1);
    }
    if (signal(SIGTSTP, sig_usr) == SIG_ERR) {
        printf("can't catch SIGTSTP\n");
        exit(-1);
    }

    for ( ; ; ) {
        pause();
    }

    return 0;

}

/* replaced the default signal handlers to kill this job from the keyboard ... 
   program will enter infinite loop with pause
   
   we cannot terminate this program from the keyboard -->
   login to the specific machine this process is running and kill this process using either kill or top 
   
   kill from another terminal ...
   1) find PID --> ps -ef | grep <filename> 
   2) send SIGTERM --> kill <pid> */