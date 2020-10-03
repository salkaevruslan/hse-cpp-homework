#include <test_str.h>
#include <str.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void test_strcpy() {
    const char *test_str2 = "test copy";
    char *test_str1 = (char *) malloc(sizeof(char) * (strlen(test_str2) + 1));
    my_strcpy(test_str1, test_str2);
    assert(strcmp(test_str1, test_str2) == 0);
    printf("%s", "Strcpy test passed\n");
    free(test_str1);
}

void test_strlen() {
    const char *test_str1 = "test length";
    const char *test_str2 = "";
    assert(my_strlen(test_str1) == strlen(test_str1));
    assert(my_strlen(test_str2) == 0);
    printf("%s", "Strlen test passed\n");
}

void test_strcat() {
    const char *test_str0 = "test ";
    const char *test_str2 = "concat";
    char *test_str1 = (char *) malloc(sizeof(char) * (strlen(test_str0) + strlen(test_str2) + 1));
    char *test_str3 = (char *) malloc(sizeof(char) * (strlen(test_str0) + strlen(test_str2) + 1));
    my_strcpy(test_str1, test_str0);
    my_strcpy(test_str3, test_str0);
    strcat(test_str3, test_str2);
    my_strcat(test_str1, test_str2);
    assert(strcmp(test_str1, test_str3) == 0);
    printf("%s", "Strcat test passed\n");
    free(test_str1);
    free(test_str3);
}

void test_strcmp() {
    const char *test_str1 = "test length";
    char *test_str = (char *) malloc(sizeof(char) * (strlen(test_str1) + 1));
    my_strcpy(test_str, test_str1);
    const char *test_str2 = "not test length";
    const char *test_str3 = "test length length";
    const char *test_str4 = "test langth";
    const char *test_str5 = "test langta";
    assert(my_strcmp(test_str, test_str1) == 0);
    assert(my_strcmp(test_str1, test_str2) > 0);
    assert(my_strcmp(test_str2, test_str1) < 0);
    assert(my_strcmp(test_str3, test_str) > 0);
    assert(my_strcmp(test_str4, test_str) < 0);
    assert(my_strcmp(test_str5, test_str) < 0);
    printf("%s", "Strlen test passed\n");
    free(test_str);
}
