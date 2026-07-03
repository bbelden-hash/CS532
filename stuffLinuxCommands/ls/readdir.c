#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int main(int argc, char **argv) {

    struct dirent *dirent;
    DIR *parentDIR;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <dirname>\n", argv[0]);
        exit(-1);
    }

    parentDIR = opendir(argv[1]);
    
    if (parentDIR == NULL) {
        fprintf(stderr, "Error opening directory '%s'\n", argv[1]);
        exit(-1);
    }

    int count = 1;
    while ((dirent = readdir(parentDIR)) != NULL) {
        printf("[%d] %s\n", count, (*dirent).d_name);
        count++;
    }

    closedir(parentDIR);
    return 0;
}