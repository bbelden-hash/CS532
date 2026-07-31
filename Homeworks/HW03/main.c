#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

#include "myheader.h"

void forking(char *path, char *u, char *usr);

int main(int argc, char **argv) {

    struct stat st;
    char u[2];
    char usr[256];

    // if no argument is provided, program print an error message and exit ...
    if (argc == 1) {
        fprintf(stderr, "usages:./main <directory_name>\n");
        exit(-1);
    }

    // if user inputs "-u" as a command line argument ... plan accordingly
    if (strcmp(argv[1], "-u") == 0) {
        if (argc != 4) {
            fprintf(stderr, "usage:./main -u <username> <directory>\n");
            exit(EXIT_FAILURE);
        }

        strcpy(u, "1");
        strncpy(usr, argv[2], sizeof(usr) - 1);
        usr[sizeof(usr) - 1] = '\0';

        if (stat(argv[3], &st) == 0) {
            if (S_ISDIR(st.st_mode)) {
                printf("directory: %s\n", argv[3]);
                forking(argv[3], u, usr);
            } else {
                fprintf(stderr, "item exists, but it is not a directory.\n");
                exit(-1);
            }
        }
    }
    // if the directory is invalid or doesn't exist, print an error message and exit ...
    else if (stat(argv[1], &st) == 0) {
        strcpy(u, "0");
        if (S_ISDIR(st.st_mode)) {
            printf("directory: %s\n", argv[1]);
            forking(argv[1], u, NULL);
        } else {
            fprintf(stderr, "item exists, but it is not a directory.\n");
            exit(-1);
        }
    } else {
        fprintf(stderr, "directory does not exist or cannot be accessed.\n");
        exit(-1);
    }

    return 0;
}