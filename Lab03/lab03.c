#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void insertionSort(char *arr[], int size) {

    for (int i = 1; i < size; i++) {
        char *key = arr[i];
        int j = i - 1;

        while (j >= 0 && strcmp(arr[j], key) > 0) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

int splitChar(char *arr, char *str[]) {

    char *token;
    token = strtok(arr, " ");
    int n = 0;
    
    while (token != NULL) {
        str[n] = token;
        token = strtok(NULL, " ");
        n++;
    }

    return n;
}

void printWords(char *arr[], int size) {

    for (int i = 0; i < size; i++) {
        printf("%s\n", arr[i]);
    }
}

int main() {

    /* lab03 assignment */

    int lab03Size;
    printf("How big should the sentence buffer be?\n");
    scanf("%d", &lab03Size);
    getchar();

    char *str = malloc(lab03Size * sizeof(char));

    printf("Enter a sentence:\n");
    fgets(str, lab03Size, stdin);

    char *phrase[100];
    int count = splitChar(str, phrase);

    printf("\nBefore sort:\n");
    printWords(phrase, count);

    insertionSort(phrase, count);

    printf("\nAfter sort:\n");
    printWords(phrase, count);

    free(str);
}