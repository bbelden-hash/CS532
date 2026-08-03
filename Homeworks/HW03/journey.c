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

void forking(char *path, char *u, char *usr) {

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

        struct stat filestats;

        snprintf(filepath, sizeof(filepath), "%s/%s", path, item->d_name);

        if (lstat(filepath, &filestats) != 0) {
            fprintf(stderr, "error grabbing stat structure from lstat in journey.c file ...\n");
            exit(-1);
        }

        if (S_ISDIR(filestats.st_mode)) {
            continue;
        }

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
            );*/
            closedir(dir);
            char *args[] = {"/workspaces/CS532/Homeworks/HW03/forexec/execmain", path, item->d_name, u, usr, NULL};

            execv(args[0], args);
            perror("execv failed");
            _exit(EXIT_FAILURE);
        }
    }

    int status;
    while (wait(&status) > 0) {
        if (WIFEXITED(status)) {
            // child exited normally
        } else if (WIFSIGNALED(status)) {
            fprintf(stderr, "child terminated by signal %d\n", WTERMSIG(status));
        }
    }

    closedir(dir);
}

    

