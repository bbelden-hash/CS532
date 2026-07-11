#ifndef FILESYSTEM_H
#define FILESYSTEM_H

int search(int argc, char *argv[]);
int traversal(char *cwd, int depth);
int _S(char *path, int depth);

void printTab(int depth);
int isLink(char *file);

#endif