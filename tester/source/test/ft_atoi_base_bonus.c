#include "tester.h"

int main(int argc, char **argv)
{
  if (argc < 3)
    return (1);

  char *base = *++argv;

  while (*++argv)
  {
    printf("Value >%s< in base >%s< is >%d<\n", *argv, base, ft_atoi_base(*argv, base));
  }

  return (0);
}