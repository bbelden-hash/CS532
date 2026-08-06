#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

/* 
    extend to three processes
    create three processes and use two pipes
        - one for communication between the first and second process
        - one for commnication between second and third process 
*/

int main(int argc, char **argv) {

    pid_t pid1;
    pid_t pid2;
    pid_t pid3;
    int pipefd1[2];
    int pipefd2[2];
    int status1, status2, status3;

    if (argc != 4) {
        printf("usage: %s <command1> <command2> <command3>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (pipe(pipefd1) != 0) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    if (pipe(pipefd2) != 0) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid1 = fork();
    if (pid1 < 0) {
        perror("fork");
        exit(EXIT_FAILURE);

    }
    if (pid1 == 0) {
        close(pipefd1[0]);

        close(pipefd2[0]);
        close(pipefd2[1]);

        if (dup2(pipefd1[1], STDOUT_FILENO) == -1) {
            perror("dup2");
            exit(EXIT_FAILURE);
        }
        close(pipefd1[1]);

        execlp(argv[1], argv[1], (char *) NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    }

    pid2 = fork();
    if (pid2 < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (pid2 == 0) {
        close(pipefd1[1]);

        if (dup2(pipefd1[0], STDIN_FILENO) == -1) {
            perror("dup2");
            exit(EXIT_FAILURE);
        }
        close(pipefd1[0]);
        close(pipefd2[0]);

        if (dup2(pipefd2[1], STDOUT_FILENO) == -1) {
            perror("dup2");
            exit(EXIT_FAILURE);
        }
        close(pipefd2[1]);

        execlp(argv[2], argv[2], (char *) NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    }

    pid3 = fork();
    if (pid3 < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (pid3 == 0) {
        close(pipefd2[1]);

        close(pipefd1[0]);
        close(pipefd1[1]);

        if (dup2(pipefd2[0], STDIN_FILENO) == -1) {
            perror("dup2");
            exit(EXIT_FAILURE);
        }
        close(pipefd2[0]);

        execlp(argv[3], argv[3], (char *) NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    }

    close(pipefd1[1]);
    close(pipefd1[0]);
    close(pipefd2[0]);
    close(pipefd2[1]);

    waitpid(pid1, &status1, 0);
    waitpid(pid2, &status2, 0);
    waitpid(pid3, &status3, 0);

    return 0;
}