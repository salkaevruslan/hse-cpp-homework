#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <assert.h>
#include "mergesort.h"

int int_comparer(const void *left, const void *right) {
    return *((const int *) right) - *((const int *) left);
}

int char_comparer(const void *left, const void *right) {
    return *((const char *) right) - *((const char *) left);
}

int str_comparer(const void *left, const void *right) {
    return strcmp(*(const char **) right, *(const char **) left);
}

void exit_error() {
    printf("Error: memory allocation\n");
    exit(-1);
}

void sort_int(int argc, char *argv[]) {
    int *array = (int *) malloc(argc * sizeof(int));
    if (!array) {
        free(array);
        exit_error();
    }
    for (int i = 0; i < argc; ++i)
        array[i] = atoi(argv[i]);
    if (mergesort(array, argc, sizeof(int), int_comparer) == -1) {
        free(array);
        exit_error();
    } else {
        for (int i = 0; i < argc; ++i)
            printf("%d ", array[i]);
        printf("\n");
        free(array);
    }
}

void sort_char(int argc, char *argv[]) {
    char *array = (char *) malloc(argc * sizeof(char));
    if (!array) {
        free(array);
        exit_error();
    }
    for (int i = 0; i < argc; ++i)
        array[i] = *(argv[i]);
    if (mergesort(array, argc, sizeof(char), char_comparer) == -1) {
        free(array);
        exit_error();
    } else {
        for (int i = 0; i < argc; ++i)
            printf("%c ", array[i]);
        printf("\n");
        free(array);
    }
}

void sort_str(int argc, char *argv[]) {
    if (mergesort(argv, argc, sizeof(char *), str_comparer) == -1) {
        exit_error();
    } else {
        for (int i = 0; i < argc; ++i)
            printf("%s ", argv[i]);
        printf("\n");
    }
}

int main(int argc, char *argv[]) {
    if (strcmp((char *) argv[1], "int") == 0) {
        sort_int(argc - 2, &argv[2]);
    }
    if (strcmp((char *) argv[1], "char") == 0) {
        sort_char(argc - 2, &argv[2]);
    }
    if (strcmp((char *) argv[1], "str") == 0) {
        sort_str(argc - 2, &argv[2]);
    }
    return 0;
}
