#include <str.h>

char *my_strcpy(char *restrict destination, const char *restrict source) {
    char *ptr = destination;
    while ((*destination++ = *source++));
    return ptr;
}

char *my_strcat(char *restrict destination, const char *restrict source) {
    char *ptr = destination;
    while (*destination)
        ++destination;
    while (*source) {
        *destination = *source;
        ++destination, ++source;
    }
    *destination = 0;
    return ptr;
}

int my_strcmp(const char *str1, const char *str2) {
    while (*str1 == *str2 && *str1 != 0) {
        ++str1, ++str2;
    }
    return *str1 - *str2;
}

size_t my_strlen(const char *str) {
    size_t result = 0;
    while (*str++)
        ++result;
    return result;
}
