lab06 -->

listings.csv:
    (comma seperated values) file that stores tabular data in plain text 

the first row of all columns from "listings.csv" are variables in a struct called "listing"

    --> from the .csv file, all data is read ...
    
each row in the .csv file corresponds to one struct listing structure -->
    the file is read line by line, appending each row in the file to an array of type "struct listing"
    as data is read from lines, the variables from the "struct listing" structure are given values ...
    data is acquired through the 'getline()' C function 

so ...
    items[0] = {row1 = struct listing}
    items[1] = {row2 = struct listing}
    items[2] = {row3 = struct listing}
    etc.

data is read row by row from the file (appending the data to the array) from the .csv until the end of file is reached

--> all information from the file is printed to the console (could be cumbersome ...)

a file called "hosting.txt" and "pricing.txt" are created ... 
--> using C's qsort() 
(data read from the .csv, stored in a dynamically allocated memory array from above) 
    - is sorted, first, by the host_name (host_name is one of the columns from our "listings.csv" file, one variable in the "listing" structure)
    - is sorted, second, by the price (price is one of the columns from our "listings.csv" file, one variable in the "listing" structure)

upon both sorts by both host_name and price locations of particular structures in the array are moved to there respected sorted positions ...

after qsort(host_name) --> a file is created called "hosting.txt" of all the host names in sorted order

after qsort(price) --> a file is created called "pricing.txt" of structure "listing" variables Price, Host Name, Neighborhood, and Room type sorted by price in ascending order.

compilation:
to compile properly one must provide the object file, "listings.csv", and two .txt files to the console 
--> .txt files correspond to the files that are going to be created post host_name sort and post price sort

    1) gcc lab06.c -o "lab06"
    2) ./lab06 listings.csv hosting.txt pricing.txt

NOTE: the .txt corresponding to appended host_names data must come before the .txt corresponding to sorted price values in the console 

