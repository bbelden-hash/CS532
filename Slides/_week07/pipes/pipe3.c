#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

/*
    1) create a pipe in the parent process
    2) create a child process, close the read end of the pipe
    3) replace the standard output stream with the write end of the pipe using dup2 system call
    4) use exec to launch the first program
    5) create another child process
    6) close the write end of the pipe
    7) replace the standard input stream with the read end of the pipe using dup2 system call
    8) use exec to launch the second program
    9) parent then closes both ends of the pipe and uses waitpid system call to wait for both child process to terminate
*/

int main(int argc, char **argv) {
    
    pid_t pid1;
    pid_t pid2;
    int pipefd[2]; // pipefd[0] for read, pipefd[1] for write
    int status1;
    int status2;

    if (argc != 3) {
        printf("usage: %s <command1> <command2>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (pipe(pipefd) == -1) { // open the pipe
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid1 = fork(); // fork first process to execute command1

    if (pid1 < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid1 == 0) { // child process
        close(pipefd[0]); // close read end of the pipe

        // replace stdout with write end of pipe
        if (dup2(pipefd[1], STDOUT_FILENO) == -1) {
            perror("dup2");
            exit(EXIT_FAILURE);
        }
        close(pipefd[1]); // original descriptor no longer needed

        // execute <command1>
        execlp(argv[1], argv[1], (char *) NULL);
        printf("if you see this statement then exec failed :-(\n");
        perror("execlp");
        exit(EXIT_FAILURE);
    }

    pid2 = fork();

    if (pid2 < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid2 == 0) {
        close(pipefd[1]);

        if (dup2(pipefd[0], STDIN_FILENO) == -1) {
            perror("dup2");
            exit(EXIT_FAILURE);
        }
        close(pipefd[0]);

        execlp(argv[2], argv[2], (char *) NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    }

    close(pipefd[0]);
    close(pipefd[1]);

    waitpid(pid1, &status1, 0);
    waitpid(pid2, &status2, 0);

    return 0;
}

/* NOTE: execlp runs program ls, prints ls to terminal stdout,
          but bcs stdout is not the terminal (dup2) -->
          writes to the pipe instead ... */

