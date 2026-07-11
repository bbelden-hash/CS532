#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct listing {

    int id;
    int host_id;
    int minimum_nights;
    int number_of_reviews;
    int calculated_host_listings_count;
    int availability_365;

    char *host_name;
    char *neighborhood_group;
    char *neighborhood;
    char *room_type;

    float latitude;
    float longitude;
    float price;
};

struct listing getfields(char *line) {

    struct listing item;

    item.id = atoi(strtok(line, ","));
    item.host_id = atoi(strtok(NULL, ","));
    item.host_name = strdup(strtok(NULL, ","));
    item.neighborhood_group = strdup(strtok(NULL, ","));
    item.neighborhood = strdup(strtok(NULL, ","));
    item.latitude = atof(strtok(NULL, ","));
    item.longitude = atof(strtok(NULL, ","));
    item.room_type = strdup(strtok(NULL, ","));
    item.price = atof(strtok(NULL, ","));
    item.minimum_nights = atoi(strtok(NULL, ","));
    item.number_of_reviews = atoi(strtok(NULL, ","));
    item.calculated_host_listings_count = atoi(strtok(NULL, ","));
    item.availability_365 = atoi(strtok(NULL, ","));

    return item;
}

FILE *openfile(char *myfile) {
    FILE *fptr = fopen(myfile, "r");

    if (fptr == NULL) {
        return NULL;
    }

    return fptr;
}

FILE *makefile(char *newfile) {
    FILE *fptr = fopen(newfile, "w");

    if (fptr == NULL) {
        perror("error opening/creating an output file");
        exit(-1);
    }

    return fptr;
}

struct listing *fileinfo(FILE *file, int *total) {

    int capacity = 8;
    int count = 0;
    
    struct listing *allitems = malloc(capacity * sizeof(struct listing));

    if (allitems == NULL) {
        fprintf(stderr, "initial malloc error");
        exit(-1);
    }

    size_t n = 0;
    char *item = NULL;

    while ((getline(&item, &n, file)) != -1) {

        if (count == capacity) {
            capacity *= 2;

            struct listing *temp = realloc(allitems, capacity * sizeof(struct listing));

            if (temp == NULL) {
                fprintf(stderr, "realloc error");
                free(allitems);
                free(item);
                exit(-1);
            }

            allitems = temp;
        } 

        allitems[count] = getfields(item);
        count++;
    }

    free(item);
    *total = count;
    
    return allitems;
}

void displayitems(struct listing *arr, int size) {

    for (int i = 0; i < size; i++) {

        fprintf(stdout, "ID: %d, Host ID: %d, Host Name: %s, Neighborhood: %s, Room Type: %s, Price: %.2f\n", 
            arr[i].id, arr[i].host_id, arr[i].host_name, arr[i].neighborhood, arr[i].room_type, arr[i].price);
    }
}

int comparehosts(const void *a, const void *b) {
    
    /*
    The Cast: 
    (struct listing *)a tells the compiler: "Treat this raw address a as the starting point of a struct listing.
    */
    const struct listing *structa = (const struct listing *)a;
    const struct listing *structb = (const struct listing *)b;

    /*
    The Field Lookup: 
    struct_a->host_name calculates exactly where the host_name string pointer sits inside that structural block of memory.
    The Evaluation: strcmp() looks at the actual characters of the two host names and returns a negative, zero, or positive number back to qsort.
    */
    return strcmp(structa->host_name, structb->host_name);
}

int compareprice(const void *a, const void *b) {

    const struct listing *structa = (const struct listing *)a;
    const struct listing *structb = (const struct listing *)b;

    if (structa->price < structb->price) {
        return -1;
    } if (structa->price > structb->price) {
        return 1;
    }

    return 0;
}


int main(int argc, char **argv) {

    if (argc != 4) {
        fprintf(stderr, "error: pass .o file and filenames");
        exit(-1);
    }

    FILE *listings = openfile(argv[1]);
    FILE *hostsort = makefile(argv[2]);
    FILE *pricesort = makefile(argv[3]);

    int total;
    struct listing *mylist = fileinfo(listings, &total);
    displayitems(mylist, total);

    /* 
    calling qsort(mylist, total, sizeof(struct listing), comparehosts);,
    the function sees your array as one long, continuous block of raw bytes in memory.
    Because qsort is generic, it does not know what a struct listing is. 
    It only knows two numbers you gave it:
        - There are total number of blocks.
        - Each block is exactly sizeof(struct listing) bytes wide.

    qsort selects two blocks to compare ... To pass them to your comparison function, 
    it calculates their exact memory addresses using simple math:
        - Address of Block A = mylist + (index_A * size_of_struct)
        - Address of Block B = mylist + (index_B * size_of_struct)
    It hands these two raw addresses to your comparehosts function as void *a and void *b.

    When strcmp returns a value showing that the two elements are out of order, 
    qsort performs an in-place physical swap:
        - It allocates a tiny, internal temporary buffer equal to sizeof(struct listing) bytes.
        - It uses memcpy to copy the entire byte block of Structure A into the temporary buffer.
        - It copies the entire byte block of Structure B into the slot where Structure A used to sit.
        - It copies the temporary buffer into the slot where Structure B used to sit.
    */
    fprintf(stdout, "Sorting names ...\n");
    qsort(mylist, total, sizeof(struct listing), comparehosts);

    fprintf(hostsort, "Sorted names of hosts:\n\n");
    for (int i = 0; i < total; i++) {
        fprintf(hostsort, "%s\n", mylist[i].host_name);
    }
    fclose(hostsort);

    fprintf(stdout, "Sorting prices ...\n");
    qsort(mylist, total, sizeof(struct listing), compareprice);

    fprintf(pricesort, "Sorted items by pricing:\n\n");
    for (int i = 0; i < total; i++) {
        fprintf(pricesort, "Price: %.2f, Host Name: %s, Neighborhood: %s, Room Type: %s\n", 
            mylist[i].price, mylist[i].host_name, mylist[i].neighborhood, mylist[i].room_type);
    }
    fclose(pricesort);

    fclose(listings);
    free(mylist);

    return 0;
}

