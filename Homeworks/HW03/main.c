#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "myheader.h"

void forking(char *path);

int main(int argc, char **argv) {

    struct stat st;

    // if no argument is provided, program print an error message and exit ...
    if (argc == 1) {
        fprintf(stderr, "usages:./hw03 <directory_name>\n");
        exit(-1);
    }
    
    // if the directory is invalid or doesn't exist, print an error message and exit ...
    if (stat(argv[1], &st) == 0) {
        if (S_ISDIR(st.st_mode)) {
            printf("directory: %s\n", argv[1]);
            forking(argv[1]);
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