#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

/* 
    This example illustrates how to use dup2 to replace stdin and stdout file descriptors ...
    replaces with the files stdin.txt and stdout.txt 
*/

int main(int argc, char **argv) {
    
    pid_t pid;
    int status;
    int fdin;
    int fdout;

    // display program usage if arguments are missing 
    if (argc < 2) {
        printf("usage: %s <command> [args]\n", argv[0]);
        exit(-1);
    }

    /* open file to read standard input stream,
       make sure the file stdin.txt exists, even if it is empty */
    if ((fdin = open("stdin.txt", O_RDONLY)) == -1) {
        printf("error opening file stdin.txt for input\n");
        exit(-1);
    }

    /* open file to write standard output stream in append mode
       create a new file if the file does not exist 
       Permissions:
        Owner: (7) --> read, write, execute
        Group: (5) --> read, execute
        Others: (5) --> read, execute */
    if ((fdout = open("stdout.txt", O_CREAT | O_APPEND | O_WRONLY, 0755)) == -1) {
        printf("error opening file stdout.txt for output\n");
        exit(-1);
    }

    pid = fork();
    if (pid == 0) { // this is child process
        // replace standard input stream with the file stdin.txt --> anything written to stdin goes to stdin.txt
        dup2(fdin, 0);

        // replace standard output stream with the file stdout.txt --> anything written to stdout goes to stdout.txt
        dup2(fdout, 1);

        execvp(argv[1], &argv[1]);
        /* since stdout is written to stdout.txt and not the terminal,
           we should write to stderr in case exec fails, we use perror
           that writes the error message to stderr */
        perror("exec");
        exit(-1);
    }
    else if (pid > 0) { // this is parent process
        /* output from the parent process still goes to stdout :-) */
        printf("wait for the child process to terminate\n");
        wait(&status);

        if (WIFEXITED(status)) { // child process terminated normally
            printf("child process exited with status = %d\n", WEXITSTATUS(status));
            /* parent process still has the file handle to stdout.txt,
               now that the child process is done, let us write to
               the file stdout.txt using the write system call */
            write(fdout, "Hey! This is the parent process\n", 32);
            close(fdout);
            /* since we opened the file in append mode, the above text
               will be added after the output from the child process */

        } else { // child process did not terminate normally 
            printf("child process did not terminate normally!\n");
            /* look at the man page for wait (man 2 wait) to determine 
               how the child process was terminated */
        }
    }
    else { // error
        perror("fork");
        exit(EXIT_FAILURE);
    }

    return 0;
}

/* NOTE: if child "argv[1, ...]" reads from stdin, it will read from stdin.txt,
         because of dup2(), so if stdin.txt is empty --> EOF is reached immediately, no data */

/* compile and run ... 
    Compile and run this program using myprog as the child process.
    Note that you have provide input to myprog in the file stdin.txt
    and the output of myprog will be written to stdout.txt.
    
    As we did not do anything with the stderr stream,
    the output to stderr stream goes to the terminal. 
    
    terminal session:
    $ gcc -Wall -o obj/myprog myprog.c
    $ gcc -Wall -o obj/dup dup.c
    $ cat > stdin.txt
    name
    ^D
    $ ./obj/dup ./obj/myprog
    ...
    ...
    $ cat stdout.txt
    ...
    ...
*/