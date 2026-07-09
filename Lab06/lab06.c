#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

FILE openfile(char *myfile) {

    FILE *fptr = fopen(myfile, "r");
    return *fptr;
}

struct listing *fileinfo(FILE *file) {

    int capacity = 8;
    int icount = 0;
    int rcount = 0;
    struct listing *allitems = malloc(capacity * sizeof(struct listing));
    struct listing *tmp = malloc(icount * sizeof(struct listing));
    size_t n = 0;
    char *item = NULL;

    while((getline(&item, &n, file)) != -1) {

        icount++;
        tmp = relloc(icount * sizeof(struct listing));
        tmp[icount - 1] = getfields(item);

        if (tmp == NULL) {
                fprintf(stderr, "realloc error");
                allitems = tmp;
                free(tmp);
                tmp = NULL;
                exit(-1);
            }

        if (sizeof(tmp) == (capacity * sizeof(struct listing))) {
            capacity *= 2;

            allitems = realloc(allitems, capacity * sizeof(struct listing));
        } 

        allitems[rcount] = getfields(item);
        rcount++;
    }

    free(item);
    item = NULL;
    free(tmp);
    tmp = NULL;
    
    return allitems;
}

void displayitems(struct listing arr[], int size) {

    for (int i = 0; i < size; i++) {

        fprintf(stdout, "%s\n", arr[i]);
    }
}

int main(int argc, char **argv) {







}

