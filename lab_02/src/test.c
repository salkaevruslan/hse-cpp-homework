#include <test_str.h>
#include <stdio.h>

int main() {
    test_strcpy();
    test_strlen();
    test_strcat();
    test_strcmp();
    printf("%s", "Tests passed successfully\n");
    return 0;
}
