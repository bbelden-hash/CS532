#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int count = 0;

void sig_handler(int signum) {

    count++;

    if (count > 3) {
        signal(SIGINT, SIG_DFL); // Re Register signal handler for default action
    }

    // Return type of the handler function should be void
    printf("\nInside handler function\n");
}


int main() {

    signal(SIGINT, sig_handler); // Register signal handler
    for (int i = 1; ; i++) {
        printf("%d : Inside main function\n", i);
        sleep(1); // Delay for 1 second
    }

    return 0;
}