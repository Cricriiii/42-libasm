#include "libasm_decl.hpp"
#include "tester_cpp.hpp"

TEST(ft_list_push_front_random_sequence) {
    std::mt19937 rng{getSeed()};

    std::uniform_int_distribution<size_t> list_size_distrib(0, TestSize::M);

    TestResult res{TestSize::M};

    for (size_t i = 0; i < res.n_tested; ++i) {
        t_list *list = nullptr;
        size_t len{list_size_distrib(rng)};

        std::vector<int> values{};
        for (size_t j = 0; j < len; ++j) {
            values.push_back(randomIntegerValue<int>());
        }

        for (auto cri = values.crbegin(); cri != values.crend(); ++cri) {
            ft_list_push_front(
                &list, const_cast<void *>(
                           static_cast<const void *>(std::addressof(*cri))));
        }

        auto ci = values.begin();
        for (t_list *ptr = list; ptr != nullptr; ptr = ptr->next) {
            if (*static_cast<int *>(ptr->data) != *ci) {
                ++res.n_failures;
                break;
            }
            ++ci;
        }

        if (ci != values.end()) {
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

TEST(ft_list_push_front_register_integrity) {
    t_list *list = nullptr;
    int value = 3;
    TestResult res = testRegisterIntegrity(ft_list_push_front, &list, &value);
    free(list);
    return res;
}
