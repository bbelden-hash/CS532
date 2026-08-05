#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/wait.h>
#include <sys/stat.h>

/* shows the steps involved in creating a pipe, 
   forking a child process, 
   closing the file descriptors in the parent and child process,
   and communication between the parent and child process.

   parent process writes the string passed as the command-line argument to the pipe
   and the child process reads the string from the pipe,
   converts the string to uppercase, 
   and prints it to the stdout 
   
   read and write functions that operate on files are used to read and write data from the pipe */

int main(int argc, char **argv) {

    pid_t pid;
    int status;
    int pipefd[2]; // pipefd[0] for read, pipefd[1] for write
    char c;

    if (argc != 2) {
        printf("usage: %s <string>\n", argv[0]);
        exit(-1);
    }

    if (pipe(pipefd) == 0) { // opening the pipe
        if ((pid = fork()) == 0) { // child process
            close(pipefd[1]); // close write end

            while (read(pipefd[0], &c, 1) > 0) {
                c = toupper(c);
                write(STDOUT_FILENO, &c, 1);
            }
            write(STDOUT_FILENO, "\n", 1);
            close(pipefd[0]);

            exit(EXIT_SUCCESS);
        }
        else if (pid > 0) { // parent process
            close(pipefd[0]); // close read end

            write(pipefd[1], argv[1], strlen(argv[1]));
            close(pipefd[1]);

            wait(&status); // wait for child to terminate
            if (WIFEXITED(status)) {
                printf("child process exited with status = %d\n", WEXITSTATUS(status));
            }
            else {
                printf("child process did not terminate normally!\n");
            }
        } else { // we have an error in fork
            perror("fork");
            exit(EXIT_FAILURE);
        }
    } else {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}

/* 
    1) opens a pipe and then forks a child process to create a copy of itself
    2) communicates with the child via the pipe
    3) both parent and child processes have access to the pipe 
    4) child inherits all the open pipe file descriptors belonging to the parent
    5) after fork, parent closes the read file descriptor of the pipe and writes the string passed as the command-line argument to the pipe
    6) child closes the write file descriptor of the pipe and read the string from the pipe one character at a time, converts it to uppercase, and writes it to stdout

    $ gcc -Wall pipe1.c -o obj/pipe1
    $ ./obj/pipe1 <string>
    ...
    $ 
*/
    
