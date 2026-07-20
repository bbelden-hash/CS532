#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv) {

    printf("Hello from p2, process id= () %d\n", getpid());
    printf("The arguments are %s %s %s\n", argv[0], argv[1], argv[2]);
    printf("Now, the child process will terminate\n");
    return 0;
}