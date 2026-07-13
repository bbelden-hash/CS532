#ifndef hw02_H
#define hw02_H

#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

struct Options {

    int detailed; // -S flag
    int sizeFilter; // -s flag
    int substringFilter; // -f flag
    int regularFilter; // -t f- flag
    int dirFilter; // -t d- flag

    off_t maxBytes; // -s value
    int maxDepth; // -f depth

    char subStr[20]; // -f string
};

int search(int argc, char *argv[]);

int traversal(char *path, int depth, struct Options *options);
int matching(char *path, int depth, struct Options *options);

void printTab(int depth);
int isLink(char *file);

void _Sinfo(char *path, struct dirent *item, int depth);
void lsInfo(char *path, struct dirent *currItem, int depth);
void dirInfo(char *name, int depth);

#endif