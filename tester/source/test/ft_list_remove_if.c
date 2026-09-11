#include "tester.h"

int test_ft_list_remove_if(void) {

  t_list *elements = nullptr;
  char str[] = "0123456789", *ptr = str;
  
  while (*ptr) {
    ft_list_push_front(&elements, (void *) ptr++);
  }

  t_list *node = elements;
  int i = 0;

  while (node) {
    printf("Elem #%d is >%s<\n", i++, (char *)node->data);
    node = node->next;
  }

  ft_list_remove_if(&elements, (void*) "3", strcmp, free);

  while (node) {
    printf("Elem #%d is >%s<\n", i++, (char *)node->data);
    t_list *old = node;
    node = node->next;
    free(old);
  }

  return (0);
}


int main(void) {
  return (test_ft_list_remove_if());
}
