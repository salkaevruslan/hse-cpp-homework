#include "mergesort.h"
#include <stddef.h>
#include <string.h>
#include <malloc.h>

int mergesort(void *array, size_t elements, size_t element_size, int (*comparator)(const void *, const void *)) {
    char *buffer = malloc(element_size * elements);
    if (!buffer)
        return -1;
    mergesort_iteration(array, buffer, elements, element_size, comparator);
    free(buffer);
    return 0;
}

void mergesort_iteration(void *array, char *buffer, size_t elements, size_t element_size,
                         int (*comparator)(const void *, const void *)) {
    if (elements <= 1) {
        return;
    }
    char *left = (char *) array;
    char *mid = (char *) array + element_size * (elements / 2);
    char *right = mid;
    char *endArray = (char *) array + element_size * elements;
    mergesort_iteration(array, buffer, elements / 2, element_size, comparator);
    mergesort_iteration(mid, buffer + element_size * (elements / 2), elements - elements / 2, element_size, comparator);
    int position = 0;
    while (left != mid && right != endArray) {
        if (comparator(left, right) >= 0) {
            memcpy(buffer + position * element_size, left, element_size);
            left += element_size;
        } else {
            memcpy(buffer + position * element_size, right, element_size);
            right += element_size;
        }
        position++;
    }
    while (left != mid) {
        memcpy(buffer + position * element_size, left, element_size);
        left += element_size;
        position++;
    }
    while (right != endArray) {
        memcpy(buffer + position * element_size, right, element_size);
        right += element_size;
        position++;
    }
    memcpy((char *) array, buffer, elements * element_size);
}
