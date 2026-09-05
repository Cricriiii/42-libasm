#include "tester.h"

int test_ft_strcpy(void) {
    char *src = malloc(12);
    char *dst = malloc(12);
    // char dst[11] = {};

    src = strcpy(src, "hello world");
    ft_strcpy(dst, src);

    printf(">%s<\n", src);
    printf(">%s<\n", dst);
    
    free(src);
    free(dst);

    // ft_strcpy(src, nullptr);

    return (0);
}

int main(void) {
    return (test_ft_strcpy());
}
