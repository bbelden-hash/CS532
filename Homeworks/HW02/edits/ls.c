#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <linux/limits.h>

#include "hw02.h"

void printTab(int depth);
int isLink(char *file);
void lsInfo(char *path, struct dirent *currItem, int depth);

int traversal(char *cwd, int depth) {

    DIR *currDirectory;
    struct dirent *currItem;
    
    char path[PATH_MAX];

    currDirectory = opendir(cwd);

    if (currDirectory == NULL) {
        perror("opendir");
        return -1;
    }

    while ((currItem = readdir(currDirectory)) != NULL) {

        if (strcmp(currItem->d_name, ".") == 0 || strcmp(currItem->d_name, "..") == 0) {
            continue;
        }

        snprintf(
            path, 
            sizeof(path), 
            "%s/%s", 
            cwd, 
            currItem->d_name
        );

        lsInfo(path, currItem, depth);
    }

    closedir(currDirectory);
    return 0;
    
}

