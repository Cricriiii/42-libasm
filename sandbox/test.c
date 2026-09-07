#include <stdbool.h>
#include <stdio.h>

extern bool check_duplicated(const char *str);

int main(int argc, char **argv) {
    if (argc != 2) return (1);

    printf("String is: %s. Duplicated: %d\n", argv[1], check_duplicated(argv[1]));

    return (0);
}

