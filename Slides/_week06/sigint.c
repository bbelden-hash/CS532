#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

/* generate the signal in a program using the C API for kill or raise system call 

   replace the SIGINT signal handler with our own ...
   in the signal handler asks the user if the process should be terminated ... 
   based on the response continue with either terminating the process or let it continue to run ... */

static void sig_int(int signo) {
    ssize_t n;
    char buf[2];

    /* ignore signal first without this ->
       suppose user presses Ctrl + C again while answering the prompt ...
       Ctrl + C
            handler starts
                Ctrl + C
                    handler starts again ...
                        Ctrl + C
                            handler starts again ...
       instead
       Ctrl + C
            handler starts
                Ctrl + C
                    ignored
       */

    signal(signo, SIG_IGN);
    printf("Do you really want to do this: [Y/N]? ");
    fflush(stdout);

    n = read(STDIN_FILENO, buf, 2);

    if (buf[0] == 'Y') {
        raise(SIGTERM); // or kill(0, SIGTERM); // or exit(-1);
    } else {
        printf("Ignoring signal, be careful next time!\n");
        fflush(stdout);
    }
    signal(signo, sig_int); // reinstall the signal handler

}

int main(void) {

    /* "Whenever this process receives SIGINT, call sig_int() instead of using the default action." */
    if (signal(SIGINT, sig_int) == SIG_ERR) {
        printf("Unable to catch SIGINT\n");
        exit(-1);
    }

    for ( ; ; ) {
        pause();
    }

    return 0;
}