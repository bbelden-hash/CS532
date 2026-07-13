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

void lsInfo(char *path, struct dirent *currItem, int depth);
void _Sinfo(char *path, struct dirent *item, int depth);
void printTab(int depth);
void dirInfo(char *name, int depth);

int traversal(char *path, int depth, struct Options *options) {

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
            "%s/%s", 
            path, 
            item->d_name
        );

        struct stat entry;

        if (lstat(fullpath, &entry) != 0) {
            perror(fullpath);
            continue;
        }

        if (S_ISREG(entry.st_mode) || S_ISLNK(entry.st_mode)) {

            int allowed = 1;

            if (options->substringFilter && 
                strstr(item->d_name, options->subStr) == NULL) {
                allowed = 0;  
            } 
            
            if (options->sizeFilter && 
                entry.st_size > options->maxBytes) {
                allowed = 0;   
            } 
            
            if (allowed) {

                if (options->detailed) {
                    _Sinfo(
                        fullpath,
                        item,
                        depth
                    );
                    
                } else {
                    lsInfo(
                        fullpath,
                        item,
                        depth
                    );
                }
            }

        } else if (S_ISDIR(entry.st_mode)) {

            if (!options->substringFilter || depth < options->maxDepth) {

                dirInfo(item->d_name, depth);

                traversal(fullpath, depth + 1, options);
            }
        }
    }

    closedir(dir);
    return 0;

}