#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "filesystem.h"

int traversal(char *cwd, int depth);
int _S(char *path, int depth);

int search(int argc, char *argv[]) {

    if (argc == 1) {
        char *cwd = getcwd(NULL, 0);

        if (cwd != NULL) {
            fprintf(stdout, "Current directory: %s\n", cwd);

        } else {
            perror("getcwd");
            exit(-1);
        }

        traversal(cwd, 0);
        free(cwd);
    }

    if (argc == 2) {

        if (strcmp(argv[1], "-S") == 0) {

            char *cwd = getcwd(NULL, 0);
            _S(cwd, 0);
        
        } else {
            traversal(argv[1], 0);
        }
    }

    if (argc > 2) {

        for (int i = 0; i < argc; i++) {

            if (strcmp(argv[i], "-S") == 0) {
                int _S = 0;
            
            } if (strcmp(argv[i], "-s") == 0) {
                int _s = argv[i + 1];

            } if (strcmp(argv[1], "-f") == 0) {
                char subStr[20] = argv[i + 1];
                int maxDepth = argv[i + 2];
            }
        }
    }





    return 0;
}