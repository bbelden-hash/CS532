#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <time.h>

#include "filesystem.h"

#define FULL_PATH 1000

void printTab(int depth);

int _S(char *path, int depth) {

    printf("Permission values:\n");
    printf("4 = read\n");
    printf("2 = write\n");
    printf("1 = execute\n\n");

    printf("Permission groups:\n");
    printf("Owner: 100 digit\n");
    printf("Group: 010 digit\n");
    printf("Others: 001 digit\n");

    DIR *dir;
    struct dirent *item;
    struct stat entry;
    char fullpath[FULL_PATH];

    dir = opendir(path);

    if (dir == NULL) {
        perror("opendir");
        return -1;
    }

    while ((item = readdir(dir)) != NULL) {

        if (strcmp((*item).d_name, ".") == 0 || strcmp((*item).d_name, "..") == 0) {
            continue;
        }

        printTab(depth);

        snprintf(fullpath, sizeof(fullpath), "%s/%s", path, (*item).d_name);

        if (lstat(fullpath, &entry) == 0 && S_ISDIR(entry.st_mode)) {

            fprintf(stdout, "DIR: %s -> Size: %d, Permissions: %o, Last Access Time: %s\n", 
                item->d_name, 
                0, 
                entry.st_mode & 0777, 
                ctime(&entry.st_atime));
            traversal(fullpath, depth + 1);

        } else {

            fprintf(stdout, "%s -> Size: %lld bytes, Permissions: %o, Last Access Time: %s\n",
                item->d_name,
                (long long) entry.st_size,
                entry.st_mode & 0777,
                ctime(&entry.st_atime));
        }
    }

    closedir(dir);
    return 0;
}