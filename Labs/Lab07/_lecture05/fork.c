#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

/* NOTES:
* The call wait(&status) is equivalent to: waitpid(-1, &status, 0);
* WIFEXITED(status) returns true if the child terminated normally
* WEXITSTATUS(status) returns the exit status of the child -->
    consists of the least significant 16-8 bits of the status argument that the child specified in a call to exit() or _exit()
    or as the argument for a return statement in main().
    This macro should only be employed if WIFEXITED returned true
*/

int main(int argc, char **argv) {

    pid_t pid;
    int status;

    pid = fork();
    if (pid == 0) {
        printf(
            "This is the child process, my PID is %ld and my parent PID is %ld\n",
            (long) getpid(),
            (long) getppid()
        );
    } else if (pid > 0) {
        printf(
            "This is the parent process, my PID is %ld and the child PID is %ld\n",
            (long) getpid(),
            (long) pid
        );

        printf("Wait for the child process to terminate\n");
        wait(&status);
        if (WIFEXITED(status)) {
            printf("Child process exited with status = %d\n", WEXITSTATUS(status));
        } else {
            printf("ERROR: child process did not terminate normally!\n");
        }

    } else {
        perror("fork");
        exit(EXIT_FAILURE);

    }

    printf("[%ld]: Exiting program .....\n", (long) getpid());

    return 0;
}