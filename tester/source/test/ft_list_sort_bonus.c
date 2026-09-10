#include "tester.h"

int test_ft_list_sort(int n, char **strs) {
    t_list *elems = nullptr;

    for (;n; --n) {
        ft_list_push_front(&elems, strs[n - 1]);
    }

    for (t_list *ptr = elems; ptr; ptr = ptr->next) {
        printf("Value: %s\n", (char *) ptr->data);
    }

    printf("\n");

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-function-type"
    ft_list_sort(&elems, (int (*)())ft_strcmp);
#pragma GCC diagnostic pop

    for (t_list *ptr = elems; ptr; ptr = ptr->next) {
        printf("Value: %s\n", (char *) ptr->data);
    }    

    for (t_list *ptr = elems; ptr; ) {
        t_list *old = ptr;
        ptr = ptr->next;
        free(old);
    }

    return (0);
}

int main(int argc, char **argv) {
    if (argc == 1) return (1);
    return (test_ft_list_sort(argc - 1, ++argv));
}