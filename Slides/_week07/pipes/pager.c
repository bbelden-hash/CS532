#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/wait.h>
#include <sys/stat.h>

/*
    opens the file provided as the command-line argument
    creates a pipe, and forks a child process
    then, the parent closes the read file descriptor of the pipe,
    reads the contents of the file specified as the command-line argument,
    writes the contents to the pipe,
    and waits for the child process to complete
    the child process closes the write file descriptor of the pipe and
    execs the "more" command 
*/

int main(int argc, char** argv) {

    pid_t pid;
    int status;
    int pipefd[2];
    FILE *fp;
    char line[BUFSIZ];
    int n;

    if (argc != 2) {
        printf("usage: %s <filename>\n", argv[0]);
        exit(-1);
    }

    if ((fp =fopen(argv[1], "r")) == NULL) {
        printf("error opening file %s for reading\n", argv[1]);
        exit(-1);
    }

    if (pipe(pipefd) == 0) {

        if ((pid = fork()) == 0) {
            close(pipefd[1]);
            dup2(pipefd[0], STDIN_FILENO);
            execlp("/usr/bin/more", "more", (char *) NULL);
            perror("execlp");
            exit(EXIT_FAILURE);
        }
        else if (pid > 0) {
            close(pipefd[0]);

            while (fgets(line, BUFSIZ, fp) != NULL) {
                n = strlen(line);
                if (write(pipefd[1], line, n) != n) {
                    printf("error writing to pipe\n");
                    exit(-1);
                }
            }
            close(pipefd[1]);

            wait(&status);
            if (WIFEXITED(status)) {
                printf("child process exited with status = %d\n", WEXITSTATUS(status));
            } else {
                printf("child process did not terminate normally!\n");
            }
        } else {
            perror("fork");
            exit(EXIT_FAILURE);
        }
    } else {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}

/* To Compile: gcc -Wall pager.c -o obj/pager
   To Run: ./obj/pager <filename> */