#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>

void sig_handler_parent(int signum) {

    printf("Parent : Recieved a response signal from child \n");
}

void sig_handler_child(int signum) {

    printf("Child : Recieved a signal from parent \n");
    sleep(1);
    kill(getppid(), SIGUSR1); // after parent sends signal to child, child sends signal to parent
}

int main() {

    pid_t pid;

    if ((pid = fork()) < 0) {
        printf("Fork Failed\n");
        exit(1);
    } else if (pid == 0) { // Child Process
        signal(SIGUSR1, sig_handler_child); // waiting for SIGUSR1 invoke --> if called with child PID, sig_handler_child runs ...
        printf("Child : waiting for signal\n");
        pause();
    } else { // Parent Process
        signal(SIGUSR1, sig_handler_parent); // Register signal handler
        sleep(1);
        printf("Parent : sending signal to Child\n");
        kill(pid, SIGUSR1); // sends signal to child running sig_handler_child
        printf("Parent : waiting for response\n");
        pause();
    }

    return 0;
}

/* Parent Child Communication with Signals 
   Here, fork() function creates child processes and return zero to child process and child process ID to parent process. 
   So, pid has been checked to decide parent and child process.
   
   In parent process, it is slept for 1 second so that child process can register signal handler function and wait for the signal from parent.
   After 1 second, parent process send SIGUSR1 signal to child process and wait for the response signal from child ...
   
   In child process, first it is waiting for signal from parent and when signal is received, handler function is invoked.
   From the handler function, the child process send another SIGUSR1 signal to parent.
   Here getppid() function is used for getting parent process ID.*/