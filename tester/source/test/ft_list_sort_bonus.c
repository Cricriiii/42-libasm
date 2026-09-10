#include "tester.h"

int test_ft_list_sort(void) {
    char *strs[] = {"3", "2", "1"};
    t_list *elems = nullptr;    

    for (int i = sizeof(strs)/sizeof(*strs) - 1; i >= 0; --i) {
        ft_list_push_front(&elems, strs[i]);
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

int main(void) {
    return (test_ft_list_sort());
}