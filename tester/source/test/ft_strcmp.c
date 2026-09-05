#include "tester.h"

int test_ft_strcmp(void) {
    char *s1 = "hello world";
    char *s2 = "hello world";
    char *s3 = "hello world!";

    printf("ft_strcmp: >%s< against >%s< is >%d<\n", s1, s2, ft_strcmp(s1, s2));
    printf("strcmp: >%s< against >%s< is >%d<\n", s1, s2, strcmp(s1, s2));
    printf("ft_strcmp: >%s< against >%s< is >%d<\n", s1, s3, ft_strcmp(s1, s3));
    printf("strcmp: >%s< against >%s< is >%d<\n", s1, s3, strcmp(s1, s3));
    
    return (0);
}

int main(void) {
    return (test_ft_strcmp());
}