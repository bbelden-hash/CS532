#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFSIZE 4096

int examples1AND2(int arg, char *file[]) {

    char buffer[BUFFSIZE];
    long a = 0;
    long b = 0;
    char MSG[] = "THIS IS A NEW MSG FROM LSEEK!";

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

    while ((a = read(input, buffer, BUFFSIZE)) > 0) {
        if (write(output, buffer, a) != a) {
            fprintf(stderr, "Error reading from input");
            exit(-1);
        }
    }

    if (a < 0) {
        fprintf(stderr, "Error counting read file, did not reach specified amount of data to read");
        exit(-1);
    }

    close(output);

    if (lseek(input, -10, SEEK_END) >= 0) {
        if ((b = read(input, buffer, 10)) > 0) {
            if (write(STDOUT_FILENO, buffer, b) != b) {
                fprintf(stderr, "write error");
                exit(-1);
            }
        } else {
            fprintf(stderr, "read error");
            exit(-1);
        }
    } else {
        fprintf(stderr, "lseek error");
        exit(-1);
    }

    close(input);

    int input2 = open(file[1], O_WRONLY);

    if (lseek(input2, 0, SEEK_SET) >= 0) {
        if (write(input2, MSG, strlen(MSG)) != strlen(MSG)) {
            fprintf(stderr, "write error");
            exit(-1);
        }
    } else {
        fprintf(stderr, "lseek error (Part 2)");
        exit(-1);
    }

    close(input2);

    return(0);

}

int lab04(int arg, char *file[]) {

    ssize_t bytesRead = 0;
    size_t numOfBytes = 0;
    char itllBuff[BUFFSIZE];

    if (arg != 3) {
        fprintf(stderr, "Required three args as command line arguments");
        exit(-1);
    }

     if (strcmp(file[1], file[2]) == 0) {
        fprintf(stderr, "Input and Output files are the same, will lose all data if same");
        exit(-1);
    }

    int file1 = open(file[1], O_WRONLY | O_APPEND);
    int file2 = open(file[2], O_RDONLY);

     if (file1 == -1 || file2 == -1) {
        fprintf(stderr, "Error reading (or creating) from either file");
        exit(-1);
    }

    while ((bytesRead = read(file2, itllBuff, BUFFSIZE)) > 0) {
        if (write(file1, itllBuff, bytesRead) != bytesRead) {
            fprintf(stderr, "error: appending data to file");
            exit(-1);
        }
        numOfBytes += bytesRead;
    }

    printf("\nBytes copied: %zu\n", numOfBytes);

    close(file1);
    close(file2);

    return 0;

}


int main(int argc, char *argv[]) {

    examples1AND2(argc, argv);
    lab04(argc, argv);

    return 0;
}