
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    /* Searching for directories relative to current terminal folder */

    DIR *dp;
    struct dirent *dirp;

    if (argc != 2) {
        fprintf(stderr, "usage: %s directory_name\n", argv[0]);
        exit(1);
    }

    printf("Program: %s\n", argv[0]);
    printf("Searching: %s\n\n", argv[1]);

    if ((dp = opendir(argv[1])) == NULL) {
        perror("opendir");
        exit(1);
    }

    while ((dirp = readdir(dp)) != NULL) {
        printf("%s\n", dirp->d_name);
    }

    closedir(dp);
    return(0);
}