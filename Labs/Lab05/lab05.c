#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <time.h>

void printInfo(struct stat sb) {

    char fileType[20] = "";

    if (S_ISREG(sb.st_mode)) {
        strcpy(fileType, "regular");
    } else if (S_ISDIR(sb.st_mode)) {
        strcpy(fileType, "directory");
    } else if (S_ISCHR(sb.st_mode)) {
        strcpy(fileType, "character");
    } else if (S_ISBLK(sb.st_mode)) {
        strcpy(fileType, "block");
    } else if (S_ISFIFO(sb.st_mode)) {
        strcpy(fileType, "FIFO");
    } else if (S_ISLNK(sb.st_mode)) {
        strcpy(fileType, "symlink");
    } else if (S_ISSOCK(sb.st_mode)) {
        strcpy(fileType, "socket");
    } else {
        strcpy(fileType, "unknown");
    }

    long ino = (long) sb.st_ino;
    unsigned long mode = (unsigned long) sb.st_mode;
    long nlink = (long) sb.st_nlink;
    long uid = (long) sb.st_uid;
    long gid = (long) sb.st_gid;
    long blksize = (long) sb.st_blksize;
    long long size = (long long) sb.st_size;
    long long blocks = (long long) sb.st_blocks;

    printf("File type: %s\n", fileType);
    printf("I-node number: %ld\n", ino);
    printf("Mode: %lo (octal)\n", mode);
    printf("Link count: %ld\n", nlink);
    printf("Ownership: UID=%ld, GID=%ld\n", uid, gid);
    printf("Preferred I/O block size: %ld bytes\n", blksize);
    printf("File size: %lld bytes\n", size);
    printf("Blocks allocated: %lld bytes\n", blocks);

    printf("Last status change: %s", ctime(&sb.st_ctime));
    printf("Last file access: %s", ctime(&sb.st_atime));
    printf("Last file modification: %s", ctime(&sb.st_mtime));
    printf("\n");

}

void readDirent(int numOfArgs, char **directory) {

    struct dirent *dirent;
    DIR *parentDIR;

    if (numOfArgs < 2) {
        fprintf(stderr, "Usage: %s <dirname>\n", directory[0]);
        exit(-1);
    }

    parentDIR = opendir(directory[1]);
    
    if (parentDIR == NULL) {
        fprintf(stderr, "Error opening directory '%s'\n", directory[1]);
        exit(-1);
    }

    int count = 1;
    while ((dirent = readdir(parentDIR)) != NULL) {
        printf("[%d] %s\n", count, (*dirent).d_name);
        count++;
    }

    closedir(parentDIR);
}

void readDirRecurse(char *path) {

    struct dirent *entry;
    DIR *dir;
    struct stat sb;

    char fullPath[1000];

    dir = opendir(path);

    if (dir == NULL) {
        perror("opendir");
        return;
    }

    printf("\nDirectory: %s\n", path);

    while ((entry = readdir(dir)) != NULL) {

        if (strcmp((*entry).d_name, ".") == 0 || strcmp((*entry).d_name, "..") == 0) {
            continue;
        }

        snprintf(fullPath, sizeof(fullPath), "%s/%s", path, (*entry).d_name);

        if (lstat(fullPath, &sb) < 0) {
            perror("stat");
            continue;
        }

        printf("%s\n", fullPath);
        printInfo(sb);

        if (S_ISDIR(sb.st_mode)) {
            readDirRecurse(fullPath);
        }
    }

    closedir(dir);  
}

int main(int argc, char **argv) {

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <dirname>\n", argv[0]);
        return 1;
    }

    readDirRecurse(argv[1]);

    return 0;
}