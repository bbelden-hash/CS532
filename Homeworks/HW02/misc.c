#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>

#include "filesystem.h"

#define FULL_PATH 1000

void printTab(int depth) {

    for (int i = 0; i < depth; i++) {
        printf("\t>");
    }
}

int isLink(char *file) {

    int fd = open(file, O_RDONLY);
    char link[FULL_PATH];

    if (fd == 1) {
        perror("open");
        return -1;
    }

    ssize_t bytes = read(fd, link, sizeof(link) - 1);

    if (bytes > 0) {
        link[bytes] = '\0';
        fprintf(stdout, " -> (%s)\n", link);
    }

    close(fd);
    return 0;
}