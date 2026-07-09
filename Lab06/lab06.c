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

FILE *openfile(char *myfile) {
    FILE *fptr = fopen(myfile, "r");

    if (fptr == NULL) {
        return NULL;
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

    while((getline(&item, &n, file)) != -1) {

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

int main(int argc, char **argv) {

    if (argc != 2) {
        fprintf(stderr, "error: pass .o file and a filename");
        exit(-1);
    }

    FILE *listings = openfile(argv[1]);

    int total;
    struct listing *mylist = fileinfo(listings, &total);
    displayitems(mylist, total);
    


    free(mylist);
}

