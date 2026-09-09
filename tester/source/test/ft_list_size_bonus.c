#include "tester.h"

int test_ft_list_size(int size) {

  char *str = "*";
  t_list *elements = nullptr;

  for (int i = 0; i < size; ++i) {
    ft_list_push_front(&elements, str);
  }

  printf("Size of list=%u\n", ft_list_size(elements));

  for (t_list *ptr = elements; ptr; ) {
    t_list *old = ptr;
    ptr = ptr->next;
    free(old);
  }

  return (0);
}

int main(int argc, char **argv) {
  if (argc != 2) return (1);

  return (test_ft_list_size(atoi(*++argv)));
}