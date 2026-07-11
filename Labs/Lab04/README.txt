Instructions to Compile and Execute "lab04.c"

--> why?
"lab04.c" is a file. A C source file.

Within "lab04.c" there is a function that returns an integer called lab04 (int lab04(int arg, char *file[])).

For the function "lab04" to run without an error two parameters are required:
    1) int arg: this represents the total number of "items" that will be used (3)
    2) char *file[]: this is an array of pointers of length "arg", indices 1 & 2 in "file" are pointers in memory to two different .txt files (file1.txt, file2.txt)

"lab04" is called in "the main" --> 
    because the way "main" is written (requiring two parameters, argc & argv), to initiate without an error, the user must call with not only the specified ".o" name but more ...
    the more: after running the standard "gcc lab04.c -o 'lab04'" in the terminal, the terminal will prompt for a run of the machine translated "lab04.o" but the compiler needs additional information -->
        1) the name of a .txt file to be manipulated
        2) the name of a .txt file to perform the manipulation

So rather than a "./lab04", the user provides within the terminal shell a "./lab04 file1.txt file2.txt"
The additional information satisfies the reformed main function requirement of parameters.

now --> 
the "argc" represents our THREE "strings" typed by the user in the terminal (./lab04, file1.txt, and file2.txt), argc == 3
the "argv" is an array of memory block pointers of these three "commands", argv[] = {*./lab04, *file1.txt, *file2.txt}

As the "lab04" function called in the "main" requires two parameters (stated above), the character traits of argc and argcv satisfy all the needed qualifications for both parameters of "lab04"
--> lab04(argc, argv);

All the user should be concerned with is properly running the file, the steps look as so ...
1) gcc lab04.txt -o "lab04"
2) ./lab04 file1.txt file2.txt

Once "in" what is going to happen -->
The contents from "file2.txt" will be concatenated to the end of "file1.txt" by reading from "file2.txt" and writing to "file1.txt"
The terminal will print a message giving the user a understanding of just how much information is written to "file1.txt" with a -->
"Bytes copied: ..."



