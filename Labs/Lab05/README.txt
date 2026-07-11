UNIX File System, Traversing a File Hierarchy

A user is in dire need of knowing what particular items are "living" inside a directory -->
    the user could call 'ls <dirName>' to print all files inside <dirname> to the terminal shell.

What if the user is in need of knowing a more in-depth analysis of a file within <dirname>? -->
    the user could call 'stat <fileName>' on a specific file that is located inside <dirname> to print information such as: i-node number, block size, group id, user id, etc. from the file to the terminal shell.
NOTE: the user knows <fileName> is inside <dirName> because of the previous call from 'ls <dirName>'

BUT --> what if the user does not want to spend time calling 'ls <dirName>', then calling 'stat <fileName>' on all files inside that particular directory? (if the user is in need of specific information from all files inside the directory)
this can get quite cumbersome and tedious, quite fast ...

We will combine the two command-line arguments of 'ls' and 'stat' into one --> done by creating a .c source file called 'lab05.c'

The two functions concerns us: 'readDirRecurse' & 'printInfo'

'readDirRecurse' traverses the file structure hierarchy recursively -->
Our function recursively traverses a directory tree. 
Starting from a given directory, it prints information about every file and subdirectory it finds
if it encounters a subdirectory, it calls itself to explore that directory as well.

* readDirRecurse' is done by:
    1) making sure the user passed a directory to the terminal after the object file by checking 'if (dir == NULL)'
    2) reading each entry in the directory (entry = readdir(dir))
    3) building a full path of the current location with the inclusion of 'entry' (snprintf(fullPath, sizeof(fullPath), "%s/%s", path, (*entry).d_name);)
    4) filling a struct sb by lstat with information from the current file being read (lstat(fullPath, &sb))
    5) printing specific info from our current file being read ('entry') to the terminal through our function printInfo (printInfo(sb))
    6) checking if the current 'item' within the directory being read is a directory (S_ISDIR(sb.st_mode))
    7) if the 'item' currently being read happens to be a directory, the function recursively calls itself on the directory inside the 'main' directory and traverses this directorys file structure (readDirRecurse(fullPath))
    8) after all recursions and a complete traversal the directory is closed (closedir(dir))

'printInfo' prints all information usually given to the user from command-line arguments like 'stat' and 'lstat'
--> prints the information in a clear and concise manner to the terminal shell
Information printed from each file:
    1) file type
    2) inode number
    3) mode
    4) link count
    5) ownership 
    6) preferred I/O block size 
    7) file size 
    8) blocks allocated
    9) last status change
    10) last file access
    11) last file mofification
