/* 
Name: Ben Belden
BlazerID: bbelden
Project #: HW02 

To compile: 
    - make

NOTE: 'Makefile' config grabs all .c files and compiles and tests all code
    --> all .o files created from 'make' are pushed to a directory called obj within HW02 directory

To run:
    - ./hw02 --> current directory
    - ./hw02 -S --> current directory w/ size, permissions, and last access time
    - ./hw02 /workspaces/CS532/ --> /workspaces/CS532/ directory
    - ./hw02 /workspaces/CS532/ -s 1024 --> /workspaces/CS532/ directory of files <= 1024 bytes
    - ./hw02 -f c 1 --> current directory
                            files with substring 'c' in filename
                            location of all files from parent directory (current) are 1 unit deep
    - ./hw02 -t f- --> all files of regular type
    - ./hw02 -t d- --> all 'objects' that are directories

NOTE: combinations of -t f- || -t d-, -f <string pattern> <depth>, -S, -s <file size in bytes> can be combined as command line arguments.
Combination prints files with qualifications from all categories provided to terminal
*/

'edits' --> this is a directory within HW02 that contains previous edits before final of .c files I wanted to keep

before the incorporation of the 'struct Options *options' structure, my program checked user input through string compare
    - strcmp(argv[i], "-S") == 0, etc.
this proved to be cumbersome and inefficient ... hence my options structure

before 'bigTraversal.c' I had different files for each command-line specification option (-f, -s, -S, etc.),
upon farther duration into the program build seperate files for all these specifications seemed unneccessary
--> led to bigTraversal.c 
    bigTraversal.c handles all specifications and recursion
    this handling is done through checking struct Option values through conditional statements ...

most of the printing to the terminal is done through the 'printing.c' file

the driver of the program lives in 'search.c' -->
    in search.c, all values associated with the Options structure are given approriate values based on user input (-t d-, -s 1024, etc.)
    the file then calls necessary files to complete compilation properly through 'bigTraversal.c' and 'printing.c'

all files in HW02 directory have access to all functions whether the functions live in the specific file or not ...
this is because of header file 'hw02.h'
    --> 'hw02.h' declares all the functions and the structure so they can be shared across multiple source files.

what this program is doing is printing all items within a user specified directory -->
    - if user needs specific files in a directory with specific qualifications this can be done by prompting ...
        1) -S: along with file prints file size, permissions, and last access time of file
        2) -s 1024: prints all files of maximum 1024 bytes or less
        3) -f mp4 2: prints all files with substring 'mp4' in filename and files of depth 2 from parent directory, both qualifications have to be maintained for file to qualify
        4) -t f-: prints all regular files within directory
        5) -t d-: prints all sub directories within directory
    to terminal

thats bout all i got --> if any farther questions available at bbelden@uab.edu

ADDITION: 'checking.c' --> 
recursively searches through a directory tree and returns if it finds at least one file/directory entry that matches the specified filters.

"Search this directory and all subdirectories. If you find a file that satisfies the requested filters (name, size, depth, etc.), return true. Otherwise return false."




