#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>

#include "myheader.h"

int info1(struct stat *curr, struct dirent *file) {

    fprintf(
        stdout,
        "File: %s | Size: %lld bytes\n",
        file->d_name,
        (long long) curr->st_size
    );

    return 0;
}

int info2(struct stat *curr, struct dirent *file, long words) {

    fprintf(
        stdout,
        "File: %s | Size: %lld bytes | Words: %ld\n",
        file->d_name,
        (long long) curr->st_size,
        words
    );

    return 0;
}

int info3(struct stat *curr, struct dirent *file, long words, char *usr) {

    fprintf(
        stdout, 
        "File: %s | Size: %lld bytes | Words: %ld | Owner: %s\n",
        file->d_name,
        (long long) curr->st_size,
        words,
        usr
    );

    return 0;
}

int info4(struct stat *curr, struct dirent *file, char *usr) {

    fprintf(
        stdout,
        "File: %s | Size: %lld bytes | Owner: %s\n",
        file->d_name,
        (long long) curr->st_size,
        usr
    );

    return 0;
}

