#include "tester.h"

int test_ft_read(void) {

    char str[100] = {};
    int fd = open("/home/fox/Work/libasm/tester/Makefile", O_RDONLY);
    ssize_t read = ft_read(fd, str, 100);
    close(fd);
    printf("read = %ld\nerrno = %d\n", read, errno);

    return (0);
}

int main(void) {
    return (test_ft_read());
}