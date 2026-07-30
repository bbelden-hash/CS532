#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <linux/limits.h>
#include <stdlib.h>
#include <string.h>

#include "../myheader.h"

int words(char *txt, struct stat *curr, struct dirent *file);
int info1(struct stat *curr, struct dirent *file);

int main(int argc, char **argv) {

    /* dir -> argv[1], item -> all items in 'dir' (iterates), yesfile -> file (struct dirent) looking for */
    DIR *dir;
    struct dirent *item;
    struct dirent *yesfile;

    /* correct -> the file in 'dir' we are looking for, used to give 'yesfile' a value 
       fullpath -> fullpath to 'correct' and 'yesfile->d_name' */
    char *correct = argv[2];
    char fullpath[PATH_MAX];

    dir = opendir(argv[1]);

    if (dir == NULL) {
        fprintf(stderr, "error opening directory w/ 'opendir()' in 'main' function in execmain.c ...\n");
        exit(-1);
    }

    while ((item = readdir(dir)) != NULL) {

        /* iterates through all files in directory 'dir' ...
           when a name of a file in 'dir' equals the value assigned to correct -->
           assign the 'struct dirent *item' to 'struct dirent *yesfile', indicating the file we are looking for has been found */
        if (strcmp(item->d_name, correct) == 0) {
            yesfile = item;
            break;
        }
    }

    /* get the fullpath to the file assigned to 'yesfile->d_name' */
    snprintf(fullpath, sizeof(fullpath), "%s/%s", argv[1], yesfile->d_name);

    struct stat st;

    /* "building" a 'stat' struct from the full path found above through 'yesfile->d_name' */
    if (lstat(fullpath, &st) != 0) {
        fprintf(stderr, "error grabbing stat structure from lstat in execmain.c file ...\n");
        exit(-1);
    }

    /* 'ext' will equal something like .c, .txt, .pdf, etc. */
    char *ext = strrchr(yesfile->d_name, '.');

    /* add word count if file is a .txt file, otherwise ... */
    if (ext != NULL && strcmp(ext, ".txt") == 0) {
        words(fullpath, &st, yesfile);
    } else {
        info1(&st, yesfile);
    }

    return 0;
}