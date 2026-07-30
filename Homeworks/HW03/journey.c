#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <linux/limits.h>
#include <fcntl.h>

#include "myheader.h"

void forking(char *path) {

    /* DIR -> type, an open directory stream | dir -> pointer to a DIR 
       struct dirent -> structure defined in <dirent.h> | item -> pointer to that structure | one entry (file or subdirectory) inside 'DIR' */
    DIR *dir;
    struct dirent *item;

    char filepath[PATH_MAX];

    dir = opendir(path);

    if (dir == NULL) {
        fprintf(stderr, "error opening directory w/ 'opendir()' in 'forking' function ...\n");
        exit(-1);
    }

    while ((item = readdir(dir)) != NULL) {

        // the current file inside directory is '.' or '..', continue
        if (strcmp(item->d_name, ".") == 0 || strcmp(item->d_name, "..") == 0) {
            continue;
        }

        int status = 0;

        snprintf(filepath, sizeof(filepath), "%s/%s", path, item->d_name);

        pid_t pid = fork();

        if (pid < 0) {
            fprintf(stderr, "fork in 'forking' function failed\n");
            closedir(dir);
            exit(-1);
        }
        if (pid == 0) {
            /* fprintf(stdout, "this is child process (my PID: %ld | my parent PID: %ld), process print to stdout info on files\n\n",
                (long) getpid(),
                (long) getppid()
            ); */
            char *args[] = {"/workspaces/CS532/Homeworks/HW03/forexec/execmain", path, item->d_name, NULL};

            execv(args[0], args);
            perror("execvp failed");
            exit(1);
        }
        else {
            /*fprintf(stdout, "parent, waiting for the child process to terminate ...\n"); */
            wait(&status);

            if (WIFEXITED(status)) {
                /* fprintf(stdout, "child process acquiring information exited with status = %d\n", WEXITSTATUS(status)); */
                continue;
            }
            else {
                printf("ERROR: child process did not terminate normally!\n");
            }
        }

    }

    closedir(dir);
}