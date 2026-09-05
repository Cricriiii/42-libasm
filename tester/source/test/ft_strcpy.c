#include "tester.h"

int test_ft_strcpy(void) {
    char *src = malloc(12);
    // char dst[11] = {};
    char *dst = malloc(12);

    src = strcpy(src, "hello world");
    ft_strcpy(dst, src);

    printf(">%s<\n", src);
    printf(">%s<\n", dst);
    
    free(src);

    // ft_strcpy(src, nullptr);
    // free(dst);

    return (0);
}

int main(void) {
    return (test_ft_strcpy());
}
