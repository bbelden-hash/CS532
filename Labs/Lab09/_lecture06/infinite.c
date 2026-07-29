#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handleSignINT(int sig) {

    printf("the signal caught = %d\n", sig);
}

int main() {

    /* when user initiates SIGINT (Ctrl + C), handleSignINT is called rather than SIGINT default action
       after handler (handleSignINT) returns, execution continues with loop */
    signal(SIGINT, handleSignINT);

    /* infinite loop --> prints Hello CS532 every second */
    while (1 == 1) {
        printf("Hello CS532 \n");
        sleep(1);
    }

    /* to quit infinite loop -- SIGQUIT (Ctrl + \) */

    return 0;
}