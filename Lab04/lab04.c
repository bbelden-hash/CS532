#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFSIZE 4096

int example1(int arg, char *file[]) {

    char buffer[BUFFSIZE];
    long n = 0;

    if (arg != 3) {
        fprintf(stderr, "Required three args as command line arguments");
        exit(-1);
    }

    if (strcmp(file[1], file[2]) == 0) {
        fprintf(stderr, "Input and Output files are the same, will lose all data if same");
        exit(-1);
    }

    int input = open(file[1], O_RDONLY);
    int output = open(file[2], O_CREAT | O_WRONLY | O_TRUNC, 0700);

    if (input == -1 || output == -1) {
        fprintf(stderr, "Error reading (or creating) from either file");
        exit(-1);
    }

    while ((n = read(input, buffer, BUFFSIZE)) > 0) {
        if (write(output, buffer, n) != n) {
            fprintf(stderr, "Error reading from input");
            exit(-1);
        }
    }

    if (n < 0) {
        fprintf(stderr, "Error counting read file, did not reach specified amount of data to read");
        exit(-1);
    }

    close(input);
    close(output);

    return(0);
}

int main(int argc, char *argv[]) {

    example1(argc, argv);

    return 0;
}