#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>

#include "myheader.h"

int info2(struct stat *curr, struct dirent *file, long words);

int words(char *txt, struct stat *curr, struct dirent *file) {

    FILE *fptr = fopen(txt, "r");

    if (fptr == NULL) {
        fprintf(stderr, "unable to open .txt file in 'words' function to count number of words in file\n");
        exit(-1);
    }

    /* buf -> pointer for getline(), stores a line from file each iteration
       size -> size of allocated buf, getline() updates this value as it allocates or resizes memory
       count -> number of words in .txt file */
    char *buf = NULL;
    size_t size = 0;
    long count = 0;

    // reading file line by line
    while ((getline(&buf, &size, fptr)) != -1) {

        /* inword -> word state for current line ...
           0 = currently oustide word
           1 = currently inside word */
        int inword = 0;

        // 'for' loop goes through the line one char at a time
        for (int i = 0; buf[i] != '\0'; i++) {
                // isspace() checks if the char is ' ', '\n', '\t'
                if (isspace(buf[i])) {
                    inword = 0;
                } else if (inword == 0) {
                    count++;
                    inword = 1;
                }
            }
        }

    free(buf);
    fclose(fptr);
    info2(curr, file, count);

    return 0;
}

/* example of how this program is going to count words from a file line by line ...
   
   buf -> "hello world"
   buf[0] == 'h'
   if (isspace('h') == ' ', '\n', '\t', etc.) -> false
   else if (inword == 0) --> true
   count++ --> count = 1 && inword = 1

   ...
   buf[1, 2, 3, 4] == 'e', 'l', 'l', 'o'
   inword = 1

   ...
   buf[5] == ' '
   if (isspace(' ') == ' ', etc.) -> true
   inword = 0 from inword = 1
   else if (inword = 0) --> true
   count ++ --> count = 2 && inword = 1

   ...
   buf[6, 7, 8, 9, 10] == 'w', 'o', 'r', 'l', 'd'
   inword = 1

   ...
   EOF reached
   return count == 2 (words) */