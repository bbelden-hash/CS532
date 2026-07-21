#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv) {

    printf("Hello from p1, process id= () %d\n", getpid());

    int pid = fork();
    int status;

    if (pid == 0) {

        char *args[] = {"Hello", "CS", "532", NULL};
        execv("./obj/p2", args);
        printf("we are not supposed to see this text");
    
    } else if (pid > 0) {
        wait(&status);
    }

    return 0;
}