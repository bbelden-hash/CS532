#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv) {

    printf("Hello from p1, process id= () %d\n", getpid());
    char *args[] = {"Hello", "CS", "332", NULL};
    execv("./obj/p2", args);
    printf("we are not supposed to see this text");
    return 0;

}