#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

#include "filesystem.h"

#define FULL_PATH 1000

void printTab(int depth);
int isLink(char *file);

int traversal(char *cwd, int depth) {

    DIR *currDirectory;
    struct dirent *currItem;
    struct stat entry;
    char path[FULL_PATH];

    currDirectory = opendir(cwd);

    if (currDirectory == NULL) {
        perror("opendir");
        return -1;
    }

    while ((currItem = readdir(currDirectory)) != NULL) {

        if (strcmp((*currItem).d_name, ".") == 0 || strcmp((*currItem).d_name, "..") == 0) {
            continue;
        }

        printTab(depth);

        snprintf(path, sizeof(path), "%s/%s", cwd, (*currItem).d_name);

        if (lstat(path, &entry) == 0 && S_ISDIR(entry.st_mode)) {
            fprintf(stdout, "DIR: %s\n", currItem->d_name);
            traversal(path, depth + 1);

        } else if (lstat(path, &entry) == 0 && S_ISLINK(entry.st_mode)) {
            fprintf(stdout, "%s", currItem->d_name);
            isLink(currItem->d_name);

        } else {
            fprintf(stdout, "%s\n", currItem->d_name);
        }
    }

    closedir(currDirectory);
    return 0;
}

