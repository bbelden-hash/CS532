#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <linux/limits.h>

#include "hw02.h"

int traversal(char *path, int depth, struct Options *options);

void dirInfo(char *path, int depth);

int search(int argc, char *argv[]) {

    struct Options options;

    options.detailed = 0;
    options.sizeFilter = 0;
    options.substringFilter = 0;
    options.regularFilter = 0;
    options.dirFilter = 0;

    options.maxDepth = 0;
    options.maxBytes = 0;

    options.subStr[0] = '\0';

    if (argc == 1) {

        char *cwd = getcwd(NULL, 0);

        if (cwd != NULL) {
            fprintf(
                stdout, 
                "Current directory: %s\n", 
                cwd
            );

        } else {
            perror("getcwd");
            exit(-1);
        }

        traversal(cwd, 0, &options);
        free(cwd);
    }

    else if (argc == 2) {

        if (strcmp(argv[1], "-S") == 0) {

            options.detailed = 1;

            char *cwd = getcwd(NULL, 0);

            if (cwd != NULL) {
                fprintf(
                    stdout, 
                    "Current directory: %s\n", 
                    cwd
                );
            
            } else {
                perror("getcwd");
                exit(-1);
            }

            traversal(cwd, 0, &options);
            free(cwd);
        
        } else {

            traversal(argv[1], 0, &options);
        }
    }

    else if (argc > 2) {

        char path[PATH_MAX] = "";

        int depth = 0;

        for (int i = 1; i < argc; i++) {

            if (strcmp(argv[i], "-S") == 0) {
                options.detailed = 1;
            
            } else if (strcmp(argv[i], "-s") == 0) {
                options.sizeFilter = 1;
                options.maxBytes = atoi(argv[i + 1]);
                i++;

            } else if (strcmp(argv[i], "-f") == 0) {
                options.substringFilter = 1;
                strcpy(options.subStr, argv[i + 1]);
                options.maxDepth = atoi(argv[i + 2]);
                i+=2;

            } else if (strcmp(argv[i], "-t") == 0) {
                
                if (strcmp(argv[i + 1], "f-") == 0) {
                    options.regularFilter = 1;

                } else if (strcmp(argv[i + 1], "d-") == 0) {
                    options.dirFilter = 1;
                }

                i++;

            } else {
                strcpy(path, argv[i]);
            }
        }

        if (path[0] != '\0') {

            fprintf(
                stdout,
                "Current directory: %s\n",
                path
            );
        }

        else if (path[0] == '\0') {

            char *cwd = getcwd(NULL, 0);

            if (cwd != NULL) {
                strcpy(path, cwd);
                free(cwd);

                fprintf(
                    stdout,
                    "Current directory: %s\n",
                    path
                );
            
            } else {
                perror("getcwd");
                exit(-1);
            }
        }
        
        traversal(path, depth, &options);
    }

    return 0;
}