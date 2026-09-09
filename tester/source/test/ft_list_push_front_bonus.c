// #include "tester.h"

// int test_ft_list_push_front(void) {

//   t_list *elements = nullptr;
//   char str[] = "0123456789";
  
//   for (int i = 0; i < 1000000; ++i) {
//     printf("%d -> %c\n", i, str[i % 10]);
//     ft_list_push_front(&elements, &str[i % 10]);
//   }

//   t_list *ptr = elements;
//   int i = 0;

//   while (ptr) {
//     printf("Elem #%d is >%s<\n", i++, (char *)ptr->data);
//     t_list *old = ptr;
//     ptr = ptr->next;
//     free(old);
//   }

//   return (0);
// }


// int main(void) {
//   return (test_ft_list_push_front());
// }


#include "tester.h"

int test_ft_list_push_front(const char **strs) {

  t_list *elements = nullptr;

  while (*strs) {
    ft_list_push_front(&elements, (void *)*strs++);
  }

  t_list *ptr = elements;
  int i = 0;

  while (ptr) {
    printf("Elem #%d is >%s<\n", i++, (char *)ptr->data);
    t_list *old = ptr;
    ptr = ptr->next;
    free(old);
  }

  return (0);
}


int main(int argc, char **argv) {
  if (argc == 1) return (1);

  return (test_ft_list_push_front((const char **) ++argv));
}