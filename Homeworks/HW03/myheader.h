#ifndef myheader_H
#define myheader_H

#include <dirent.h>

// functions that print particular file info in command-line directory to I/O channel 'stdout'
int info1(struct stat *curr, struct dirent *file);
int info2(struct stat *curr, struct dirent *file, long words);

// function that grabs the number of words from .txt files in the directory
int words(char *txt, struct stat *curr, struct dirent *file);

// function that traverses the directory and lists all files (excluding subdirectories), each file --> creates a child process using fork()
void forking(char *path);


#endif