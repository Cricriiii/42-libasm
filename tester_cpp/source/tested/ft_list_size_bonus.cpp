#include "libasm_decl.hpp"
#include "tester_cpp.hpp"

TEST(ft_list_size_null_list) {
    t_list *list = nullptr;

    return TestResult{1, static_cast<size_t>(ft_list_size(list) != 0 ? 1 : 0)};
}

TEST(ft_list_size_random_size) {
    std::mt19937 rng{getSeed()};

    std::uniform_int_distribution<size_t> list_size_distrib(0, TestSize::XL);

    TestResult res{TestSize::M};

    constexpr int same_value_for_all = 1;

    for (size_t i = 0; i < res.n_tested; ++i) {
        t_list *list = nullptr;
        size_t generated_list_size{list_size_distrib(rng)};

        for (size_t i = 0; i < generated_list_size; ++i) {
            ft_list_push_front(
                &list, const_cast<void *>(
                           static_cast<const void *>(&same_value_for_all)));
        }

        size_t calculated_list_size = ft_list_size(list);

        if (generated_list_size != calculated_list_size) {
            ++res.n_failures;
        }

        for (t_list *ptr = list; ptr != nullptr;) {
            t_list *next = ptr->next;
            std::free(ptr);
            ptr = next;
        }
    }
    return res;
}

TEST(ft_list_size_register_integrity) {
    t_list *list = nullptr;
    int value = 3;
    ft_list_push_front(&list, &value);
    TestResult res = testRegisterIntegrity(ft_list_size, list);
    free(list);
    return res;
}
