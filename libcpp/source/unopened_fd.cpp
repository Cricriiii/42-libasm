#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

/**
 * Return a file descriptor after closing it and clearing errno.
 */
int unopened_fd(int fd) {
    /* Close errno anyway, which sets errno to EBADF */
    close(fd);
    /* Reset errno */
    *__errno_location() = 0;
    return fd;
}