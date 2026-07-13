#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <time.h>
#include <linux/limits.h>

#include "hw02.h"

void printTab(int depth);
void _Sinfo(char *path, struct dirent *item, int depth);

int _S(char *path, int depth) {

    DIR *dir;
    struct dirent *item;

    char fullpath[PATH_MAX];

    dir = opendir(path);

    if (dir == NULL) {
        perror("opendir");
        return -1;
    }

    while ((item = readdir(dir)) != NULL) {

        if (strcmp(item->d_name, ".") == 0 || strcmp(item->d_name, "..") == 0) {
            continue;
        }

        snprintf(
            fullpath, 
            sizeof(fullpath), 
            "%s/%s", path, 
            item->d_name
        );

        _Sinfo(fullpath, item, depth);  
    }

    closedir(dir);
    return 0;
    
}