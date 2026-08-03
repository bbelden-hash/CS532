/* 
Name: Ben Belden
BlazerID: bbelden
Project #: lab09

To compile: 
    - gcc -Wall lab09.c -o <executable_name>

To run:
    - ./<executable_name> <command-line arguments>
    - example1: ./lab09 ls -l 
    - example2: ./lab09 /workspaces/CS532/Homeworks/HW03/main /workspaces/CS532/Labs/Lab09
    - example3: ./lab09 ps
    - ...
*/

lab09.c ...

once the process is running stdout will showcase ...
    parent started, child PID = 8158
    Parent waiting for Ctrl+\
    child started, PID = 8158
    child waiting for user input signals...

from here, user input is required to interact with the processes (parent, child) through signals -->
    - if user types Ctrl+Z, terminal outputs 
        "Parent received SIGTSTP (Ctrl+Z), ignored"
        "Child received SIGTSTP(Ctrl+Z)" --> child is currently stopped
    - if user types Ctrl+C, terminal outputs
        "parent received SIGINT (Ctrl+C), ignored"
        "Child received SIGINT (Ctrl+C)", "child terminating" --> child is terminated
    - if user types Ctrl+\, terminal outputs
        "parent received SIGQUIT", "parent exiting immediately" --> parent is terminated and process is DONE 

if the user types Ctrl+\ before Ctrl+C --> "parent received SIGQUIT", "parent exiting immediately"
                                           "Child received SIGQUIT (Ctrl+\)", "child executing command"
this will terminate the parent and change the process image (exiting child limbo in pause()) of the child to execute the program inputted by the user as <command-line arguments>

parent will not terminate unless user inputs Ctrl+\, so program will continue to run in limbo until this signal is received to the parent
child has ability to terminate using Ctrl+C (not executing command through execvp) or Ctrl+\ (executing command through execvp)

if child is terminated early through Ctrl+C, and user decides to input signals specific to the child after termination of the child ...
    - parent recieves child signals (Ctrl+C, Ctrl+Z), ignores them --> leading to the program to continue to run

signals are cool and fun, im excited to get more into them --> communication ... 

