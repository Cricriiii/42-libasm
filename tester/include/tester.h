#ifndef TESTER_H
# define TESTER_H

#include <stddef.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

extern size_t ft_strlen(const char *s);
extern char *ft_strcpy(char *restrict dst, const char *restrict src);
extern int ft_strcmp(const char *s1, const char *s2);
extern ssize_t ft_write(int fd, const void *buf, size_t count);
extern ssize_t ft_read(int fd, void *buf, size_t count);

int test_ft_strlen(void);

#endif
