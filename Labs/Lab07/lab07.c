#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>


int _lab07(int argc, char **argv) {

    FILE *input;
    FILE *output;

    size_t n = 0;

    char *lineptr = NULL;

    input = fopen(argv[1], "r");

    if (input == NULL) {
        fprintf(stderr, "could not open file\n");
        exit(-1);
    }

    output = fopen(argv[2], "a");

    while ((getline(&lineptr, &n, input)) != -1) {

        lineptr[strcspn(lineptr, "\n")] = '\0';
        fprintf(output, "%s\t", lineptr);

        char *args[10];
        char before_string[50];
        char after_string[50];

        int i = 0;

        char *token = strtok(lineptr, " ");
        while (token != NULL && i < 9) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;

        int status = 0;

        time_t after;
        time_t before = time(NULL);

        strcpy(before_string, ctime(&before));
        before_string[strcspn(before_string, "\n")] = '\0';
        fprintf(output, "%s\t", before_string);

        /*
        * 'fork()' splits, creating two processes (child & parent)
        * child: pid = 0 (bcs it has no children to 'take' a pid from)
        * parent: child pid
        * after fork, both processes continue executing from same point
        * to decide what each process should do --> use conditional statements
        */
        pid_t pid = fork();

        if (pid < 0) {
            perror("fork failed");
            exit(1);
        }

        if (pid == 0) {

            printf(
                "This is the child process, my PID is: %ld and my parent PID is: %ld\n",
                (long) getpid(),
                (long) getppid()
            );

            execvp(args[0], args);

            perror("execvp failed");
            exit(1);

        } else {
            printf("Wait for the child process to terminate ...\n");
            wait(&status);

            if (WIFEXITED(status)) { /* child process terminated normally  */

                after = time(NULL);
                strcpy(after_string, ctime(&after));
                before_string[strcspn(before_string, "\n")] = '\0';
                fprintf(output, "%s\n", after_string);

                printf(
                    "Child process exited with status = %d\n",
                    WEXITSTATUS(status)
                );
            
            } else { /* child process did not terminate normally */
        
                printf("ERROR: child process did not terminate normally!\n");
            }
        }
    }

    fclose(input);
    fclose(output);
    free(lineptr);

    return 0;
}

int main(int argc, char **argv) {

    _lab07(argc, argv);

    return 0;
}