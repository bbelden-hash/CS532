#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>

#include "myheader.h"

void _info(char *path, struct dirent *file, long words) {

    /* strrchr finds the last '.' in the filename 
       file->d_name -> file1.txt, ext -> .txt */
    const char *ext = strrchr(file->d_name, '.');
    struct stat curr;

    if (lstat(path, &curr) != 0) {
        fprintf(stderr, "unable to acquire information from %s in directory\n", file->d_name);
        return;
    }

    /* if the current file has extension '.txt' print no. of words in file along with file name and size of file, else ... */
    if (ext != NULL && strcmp(ext, ".txt") == 0) {
        fprintf(
            stdout,
            "File: %s | Size: %lld bytes | Words: %ld\n",
            file->d_name,
            (long long) curr.st_size,
            words
        );
    } else {
        fprintf(
            stdout,
            "File: %s | Size: %lld bytes\n",
            file->d_name,
            (long long) curr.st_size
        );
    }

}