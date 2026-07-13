#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <linux/limits.h>

#include "hw02.h"

int traversal(char *path, int depth, struct Options *option);

void printTab(int depth) {

    for (int i = 0; i < depth; i++) {
        printf(
            "\t"
        );
    }

}

int isLink(char *file) {

    char link[PATH_MAX];
    
    ssize_t bytes = readlink(file, link, sizeof(link) - 1);

    if (bytes == -1) {
        perror(file);
        return -1;
    }

    link[bytes] = '\0';
    fprintf(
        stdout,
        " -> (%s)\n", 
        link
    );

    return 0;

}

void _Sinfo(char *path, struct dirent *item, int depth) {

    struct stat entry;

    if (lstat(path, &entry) != 0) {
        perror(path);
        return;
    }

    printTab(depth);

    fprintf(stdout, 
        "%s -> Size: %lld bytes, Permissions: %o, Last Access Time: %s\n",
        item->d_name,
        (long long) entry.st_size,
        entry.st_mode & 0777,
        ctime(&entry.st_atime));
}

void lsInfo(char *path, struct dirent *currItem, int depth) {

    struct stat entry;

    if (lstat(path, &entry) != 0) {
        perror(path);
        return;
    }

    printTab(depth);

    if (S_ISLNK(entry.st_mode)) {
        fprintf(
            stdout, 
            "%s", 
            currItem->d_name);

        isLink(path);

    } else {

        fprintf(
            stdout, 
            "%s\n", 
            currItem->d_name);
    }
}

void dirInfo(char *name, int depth) {

    printTab(depth);

    fprintf(
        stdout,
        "DIR: %s\n",
        name
    );
}