#include "tester.h"

int main(int argc, char **argv) {
  if (argc != 3) return (1);

  printf("Value >%s< in base >%s< is %d\n", argv[1], argv[2], ft_atoi_base_bonus(argv[1], argv[2]));
  
  return (0);
}