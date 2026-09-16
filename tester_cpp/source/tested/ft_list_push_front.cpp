#include "tester_cpp.hpp"
#include "libasm_decl.hpp"

TEST(ft_list_push_front_random_sequence) {
    std::mt19937 rng{getSeed()};

    std::uniform_int_distribution<int> value_distrib(0, std::numeric_limits<int>::max());
    std::uniform_int_distribution<size_t> list_size_distrib(0, TestSize::M);

    TestResult res{TestSize::M};
    
    for (size_t i = 0; i < res.n_tested; ++i) {
        t_list *list = nullptr;
        size_t len{list_size_distrib(rng)};

        std::vector<int> values{};
        for (size_t j = 0; j < len; ++j) {
            values.push_back(randomIntegerValue<int>());
        }

        for (std::vector<int>::const_reverse_iterator cri = values.crbegin(); cri != values.crend(); ++cri) {
            ft_list_push_front(&list, const_cast<void *>(static_cast<const void *>(std::addressof(*cri))));
        }

        std::vector<int>::const_iterator ci = values.begin();
        for (t_list *ptr = list; ptr != nullptr; ptr = ptr->next) {
            if (*static_cast<int*>(ptr->data) != *ci) {
                ++res.n_failures;
                break;
            }
            ++ci;
        }      

        if (ci != values.end()) {
            ++res.n_failures;
        }

        for (t_list *ptr = list; ptr != nullptr; ) {
            t_list *next = ptr->next;
            std::free(ptr);
            ptr = next;
        }              
    }
    return res;
}
