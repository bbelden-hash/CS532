#ifndef myheader_H
#define myheader_H

#include <dirent.h>

// functions that print particular file info in command-line directory to I/O channel 'stdout'
int info1(struct stat *curr, struct dirent *file);
int info2(struct stat *curr, struct dirent *file, long words);
int info3(struct stat *curr, struct dirent *file, long words, char *usr);
int info4(struct stat *curr, struct dirent *file, char *usr);

// function that grabs the number of words from .txt files in the directory
int words(char *txt, struct stat *curr, struct dirent *file, char *u);

// function that traverses the directory and lists all files (excluding subdirectories), each file --> creates a child process using fork()
void forking(char *path, char *u, char *usr);


#endif