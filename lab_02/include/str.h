#pragma once

#include<stdlib.h>//for size_t

char *my_strcpy(char *restrict destination, const char *restrict source);

char *my_strcat(char *restrict destination, const char *restrict source);

size_t my_strlen(const char *str);

int my_strcmp(const char *str1, const char *str2);
