#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

/* Global Variables 
    flags, used to remember that a signal happened 
    sig_atomic_t --> signals can interrupt your program at any time 
                     because signals interrupt normal execution, special variables are used
                     guarantees that reading/writing the variable happens safely 
    volatile --> allows for no assumptions variables below stay the same 
                 always check the real memory value 
*/

volatile sig_atomic_t child_execute = 0;
volatile sig_atomic_t child_terminate = 0;
volatile sig_atomic_t parent_quit = 0;

static void sighandlerChild(int signo);
static void sighandlerParent(int signo);


static void sighandlerChild(int signo) {
    switch (signo)
    {
        // Ctrl+C, updates the child terminate variable to one --> will later exit
        case SIGINT:
            printf("\nChild received SIGINT (Ctrl+C)\n");
            child_terminate = 1;
            break;

        // Ctrl+Z, child keeps running ...
        case SIGTSTP:
            printf("\nChild received SIGTSTP (Ctrl+Z)\n");
            break;

        // Ctrl+\, updates the child execute variable to one --> executes execvp
        case SIGQUIT:
            printf("\nChild received SIGQUIT (Ctrl+\\)\n");
            child_execute = 1;
            break;

        default:
            break;
    }
}


static void sighandlerParent(int signo) {

    // Ctrl+\ updates the parent quit variable --> parent will exit
    if (signo == SIGQUIT) {
        parent_quit = 1;
    }
    else if (signo == SIGTSTP) {
        printf("\nParent received SIGTSTP (Ctrl+Z), ignored\n");
    }
    else if (signo == SIGINT) {
        printf("\nparent received SIGINT (Ctrl+C), ignored\n");
    }
}



void forkexecvp(int argc, char **argv) {
    pid_t pid;

    if (argc < 2) {
        fprintf(stderr, "usage: %s <command> [args]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // creation of child process, both continue from the next line ...
    pid = fork();

    if (pid == 0) { // child

        printf("child started, PID = %ld\n", (long)getpid());

        // install signal handlers, when these signals arrive, call this function ...
        signal(SIGINT, sighandlerChild);
        signal(SIGTSTP, sighandlerChild);
        signal(SIGQUIT, sighandlerChild);

        printf("child waiting for user input signals...\n");

        // keep waiting while: child execute = 0 and child terminate = 0 ...
        while (!child_execute && !child_terminate) {
            pause();
        }
        // the child sleeps, wakes only when signal arrives ...

        // if value of child terminate updates to one, child exits --> Ctrl+C
        if (child_terminate) {
            printf("child terminating\n");
            exit(EXIT_SUCCESS);
        }

        // Ctrl+\, child program is replaced with execvp and child executes ,,,
        if (child_execute) {

            printf("child executing command\n");
            execvp(argv[1], &argv[1]);

            perror("execvp");
            exit(EXIT_FAILURE);
        }
    }
    else if (pid > 0) {

        printf("parent started, child PID = %ld\n", (long)pid);

        // parent handles SIGQUIT, SIGTSTP, SIGINT
        signal(SIGQUIT, sighandlerParent);
        signal(SIGTSTP, sighandlerParent);
        signal(SIGINT, sighandlerParent);

        printf("Parent waiting for Ctrl+\\\n");

        // parent sleeps until it receives SIGQUIT
        while (!parent_quit) {
            pause();
        }

        // when Ctrl+\ happens ..., parent quit updates to 1, and the parent terminates
        printf("\nparent received SIGQUIT\n");
        printf("parent exiting immediately\n");
        exit(EXIT_SUCCESS);
    }
    else {
        perror("fork");
        exit(EXIT_FAILURE);
    }

}

int main(int argc, char **argv) {

    forkexecvp(argc, argv);

    return 0;
}
