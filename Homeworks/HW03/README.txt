/* 
Name: Ben Belden
BlazerID: bbelden
Project #: HW03

To compile: 
    - make

NOTE: 'Makefile' config grabs all .c files and compiles and tests all code
    --> all .o files created from 'make' are pushed to a directory called obj within HW03 directory

To run:
    - ./main --> usage:./main <directory>
    - ./main -u /workspaces/CS532/Homeworks/HW02 --> usage:./main -u <username> <directory>
    - ./main /workspaces/CS532/Homeworks/HW03 --> files in 'HW03' directory excluding subdirectories
    - ./main /workspaces/CS532/Labs/Lab06/pricing.txt --> item exists, but it is not a directory
    - ./main /workspaces/CS532/johnnybgoode --> directory does not exist or cannot be accessed
    - ./main -u bbelden /workspaces/CS532/Labs/Lab07 --> all files in 'Lab07' directory with UID bbelden
*/

hw03 ...

pulls all files from a directory specified by the user as a command-line argument, prints files to stdout
along with file name, prints size, words (if the file is a .txt file), and UID (if -u UID is specified as a command line argument)

user has ability to pull and print files from directory owned by a specific owner but specifying "-u <username>" before the directory name as command-line arguments

process of word counting in .txt files and printing the correct information based on user input happens in parallel -->
- in parallel through fork(),
    1) each time fork() is called in journey.c,
    2) a child process with pid = 0 is created ...
    3) original creation is a duplicate of parent process
    4) child process image changed through execv(./execmain, args)
    5) parent process continues execution in 'original process' ...
    6) parent loops around continuing to call child processes for each file until 'while' loop iterates through all files
    7) all child process calls through fork() run in parallel w/ execmain in own process image
    8) parent waits until all children "wrap-up" and child returns ... parent terminates

EDITS: originally my implementation had child process creation for word count and file print (fork(), execv()) sequentially -->
       each fork() call, the parent process waited for the child process to terminate before moving along to the next iteration in the while loop
       current in parallel process of child process creation can become dangerous if a directory contains massive amounts of files (maybe use threads instead)

bout all i got email for any further questions: bbelden@uab.edu




