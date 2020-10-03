#ifndef MERGESORT_H_
#define MERGESORT_H_

#include <stddef.h>

int mergesort(void *array, size_t elements, size_t element_size,
              int (*comparator)(const void *, const void *));

void mergesort_iteration(void *array, char *buffer, size_t elements, size_t element_size,
                         int (*comparator)(const void *, const void *));

#endif
