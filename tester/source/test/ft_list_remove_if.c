#include "tester.h"

int test_ft_list_remove_if(void) {

  t_list *elements = nullptr;
  char *str[] = {"3", "9", "8", "7", "6", "5", "4", "3", "3", "3", "2", "3", "1", "0", nullptr};
  // char *str[] = {"3", nullptr};
  char **ptr = str;
  
  while (*ptr) {
    ft_list_push_front(&elements, (void *) *ptr++);
  }

  t_list *node = elements;
  int i = 0;

  while (node) {
    printf("Elem #%d is >%c<\n", i++, *(char *)node->data);
    node = node->next;
  }

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-function-type"
  ft_list_remove_if(&elements, (void*) "3", (int (*)()) strcmp, free);
#pragma GCC diagnostic pop

  printf("\n");

  i = 0;
  node = elements;
  while (node) {
    printf("Elem #%d is >%c<\n", i++, *(char *)node->data);
    t_list *old = node;
    node = node->next;
    free(old);
  }

  if (node == elements) {
    printf("List is now empty\n");
  }

  return (0);
}


int main(void) {
  return (test_ft_list_remove_if());
}
