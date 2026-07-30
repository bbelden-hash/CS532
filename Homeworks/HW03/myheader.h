#ifndef myheader_H
#define myheader_H

#include <dirent.h>

// function that prints particular file info within command-line directory to I/O channel 'stdout'
_info(char *path, struct dirent *file, long words);

#endif