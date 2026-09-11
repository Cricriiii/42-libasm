#include "tester.h"

int test_ft_write(void) {

    const char *str = "this is a sample.\n";
    ssize_t written = ft_write(12, str, ft_strlen(str));

    printf("written = %ld\nerrno = %d\n", written, errno);

    return (0);
}

int main(void) {
    return (test_ft_write());
}