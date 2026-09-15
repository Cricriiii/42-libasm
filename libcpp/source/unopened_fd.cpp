#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int unopened_fd(int fd) {
    /* Close errno anyway, which sets errno to EBADF */
    close(fd);
    /* Reset errno */
    *__errno_location() = 0;
    return fd;
}