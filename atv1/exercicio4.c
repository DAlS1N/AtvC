#include <stdio.h>

int main() {
    char c;
    int i;
    float f;
    double d;

    printf("char: %lu bytes\n", sizeof(c));
    printf("int: %lu bytes\n", sizeof(i));
    printf("float: %lu bytes\n", sizeof(f));
    printf("double: %lu bytes\n", sizeof(d));

    return 0;
}