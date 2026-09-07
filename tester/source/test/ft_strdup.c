#include "tester.h"

int test_ft_strdup() {
    char *src = "hello world";
    char *dst = ft_strdup(src);

    printf("source >%s<\ndestination >%s<\n", src, dst);

    free(dst);

    return (0);
}

int main(void) {
    return (test_ft_strdup());
}