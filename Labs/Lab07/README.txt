./lab07 

To Compile: gcc -Wall -O -o lab07 lab07.c 
            ./lab07 input.txt output.log

lab07 -->
    1) reads a .txt supplied as the first command-line argument
    2) each line of .txt file consists of the path to an executable (program wanting to run) and required arguments to successfully run the said program
    3) runs program through an independent process
    4) saves path to executable and time data before and after 'execvp' to the second command-line argument --> output.log

fork() works by splitting the current process (running program) into two (parent, child)
from where the fork() is called in the program both processes run side-by-side starting from the logic written in the program after the fork() ...
fork() returns the process ID (pid) of the child to the parent and returns the process ID (pid) 0 to the child
as fork() duplicates the parent process into the child process, to enable seperate logic into the child process you should use conditional statements
check process ID values to determine if you are "in" a particular process
you can change logic of a child process using the 'exec' command system family 
bcs the two processes are running side-by-side, you risk the possibility of the parent process terminating before the child process --> this leads to a child 'zombie'
to prevent this issue, you can use the wait() command to ensure the parent process waits for continuation until the child process terminates

the two processes prints the desired programs wanting to run in the .txt files logic and varying comments to the terminal as the program iterates

:\