#include <stdbool.h>
#include <stdio.h>

extern size_t assess_base(const char *base);

int main(int argc, char **argv)
{
    if (argc == 1)
        return (1);

    while (*++argv) {
        size_t len = assess_base(*argv);
        printf("Base is: %s. Is valid: %s. Base len: %ld\n", *argv, len != 0 ? "true" : "false", len);
    }

    return (0);
}
