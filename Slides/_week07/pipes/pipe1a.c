#include <stdio.h>
#include <stdlib.h>

/* 
   creates a pipe and then creates two child processes.
   first child replaces the stdout with write end of the pipe and execs the first command
   second child replaces the stdin with read end of the pipe and execs the second command
   the stdout of the first child is sent to the stdin of the second child
   the parent process closes both ends of the pipe and waits for the child process to terminate
*/

int main(int argc, char **argv) {

    FILE *fptr1;
    FILE *fptr2;
    char line[BUFSIZ];

    if (argc != 3) {
        printf("usage: %s <command1> <command2>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // create a pipe, fork/exec command argv[1], in "read" mode
    // read mode - parent process reads stdout of child process
    if ((fptr1 = popen(argv[1], "r")) == NULL) {
        perror("popen");
        exit(EXIT_FAILURE);
    }

    // create a pipe, fork/exec command argv[2], in "write" mode
    // write mode - parent process writes to stdin of child process
    if ((fptr2 = popen(argv[2], "w")) == NULL) {
        perror("popen");
        exit(EXIT_FAILURE);
    }

    // read stdout from child process 1 and write to stdin of child process 2
    while (fgets(line, BUFSIZ, fptr1) != NULL) {
        if (fputs(line, fptr2) == EOF) {
            printf("error writing to pipe\n");
            exit(EXIT_FAILURE);
        }
    }

    // wait for child process to terminate
    if ((pclose(fptr1) == -1) && pclose(fptr2) == -1) {
        perror("pclose");
        exit(EXIT_FAILURE);
    }

    return 0;
}

/* NOTE: "w" writes into the pipe for the child process to take and do with it as they please
         "r" the child executes and puts the info in the pipe and the parent grabs that info to read */