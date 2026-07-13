#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <linux/limits.h>

#include "hw02.h"

int matching(char *path, int depth, struct Options *options) {

    DIR *dir;
    struct dirent *item;

    char fullpath[PATH_MAX];

    dir = opendir(path);

    if (dir == NULL) {
        return 0;
    }

    while ((item = readdir(dir)) != NULL) {

        if (strcmp(item->d_name, ".") == 0 ||
            strcmp(item->d_name, "..") == 0) {
            continue;
        }

        snprintf(
            fullpath,
            sizeof(fullpath),
            "%s/%s",
            path,
            item->d_name
        );

        struct stat entry;

        if (lstat(fullpath, &entry) != 0) {
            continue;
        }

        if (S_ISDIR(entry.st_mode)) {

            if (matching(fullpath, depth + 1, options)) {
                
                closedir(dir);
                return 1;
            }

        } else if (S_ISREG(entry.st_mode) ||
                   S_ISLNK(entry.st_mode)) {

            if (options->dirFilter) {
                continue;
            }

            int allowed = 1;

            if (options->substringFilter &&
                strstr(item->d_name, options->subStr) == NULL) {
                allowed = 0;
            }

            if (options->substringFilter &&
                depth > options->maxDepth) {
                allowed = 0;
            }

            if (options->sizeFilter &&
                entry.st_size > options->maxBytes) {
                allowed = 0;
            }

            if (allowed) {
                closedir(dir);
                return 1;
            }
        }
    }

    closedir(dir);
    return 0;
}

