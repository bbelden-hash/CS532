#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

/* parent process creates a child process,
   child uses exec to launch second program
   parent will use exec to launch first program */

int main(int argc, char **argv) {

    pid_t pid;
    int pipefd[2]; // pipefd[0] for read, pipefd[1] for write

    if (argc != 3) {
        printf("usage: %s <command1> <command2>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (pipe(pipefd) == 0) { // open a pipe
        pid = fork(); // fork child process to execute command2
        if (pid == 0) { // child process
            close(pipefd[1]); // close write end of the pipe

            if (dup2(pipefd[0], STDIN_FILENO) == -1) { // replace stdin with read end of pipe
                perror("dup2");
                exit(EXIT_FAILURE);
            }

            /* execute <command2> */
            execlp(argv[2], argv[2], (char *) NULL);
            perror("execlp");
            exit(EXIT_FAILURE);
        } else if (pid > 0) { // parent process
            close(pipefd[0]); // close read end of the pipe 

            if (dup2(pipefd[1], STDOUT_FILENO) == -1) { // replace stdout with write end of pipe
                perror("dup2");
                exit(EXIT_FAILURE);
            }

            /* execute <command1> */
            execlp(argv[1], argv[1], (char *) NULL);
            perror("execlp");
            exit(EXIT_FAILURE);
        } else if (pid < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        }
    } else {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    return 0;
}

/* 
    1) reads two commands as command-line arguments,
    2) creates a pipe and then creates a child process
    3) the parent process replaces the stdout with write end of the pipe and execs the first command
    4) the child replaces the stdin with read end of the pipe and execs the second command
    5) stdout of the parent process is sent to the stdin of the child process

    $ gcc -wall pipe2.c -o obj/pipe2
    $ ./obj/pipe2 <command1> <command2>
        output of <command1> will be the input for <command2>
*/

/*
    Create a pipe.
    fork() creates a parent and child.
    Child closes the write end.
    Child uses dup2() so its stdin comes from the pipe.
    Child becomes p2 using execlp().
    Parent closes the read end.
    Parent uses dup2() so its stdout goes to the pipe.
    Parent becomes p1 using execlp().
    p1 writes its output into the pipe.
    p2 reads that output from the pipe as its input.
    p2 iterates its logic and prints the result to the terminal.
*/