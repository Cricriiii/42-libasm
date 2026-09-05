#ifndef TESTER_H
# define TESTER_H

#include <stddef.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

extern size_t ft_strlen(const char *s);
extern char *ft_strcpy(char *restrict dst, const char *restrict src);

int test_ft_strlen(void);

#endif
