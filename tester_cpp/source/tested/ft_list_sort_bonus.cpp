#include <chrono>

#include "libasm_decl.hpp"
#include "tester_cpp.hpp"

TEST(ft_list_sort_empty_list) {
    t_list *list = nullptr;

    ft_list_sort(&list, nullptr);

    return TestResult{1, 0};
}

TEST(ft_list_sort_ordered_sequence) {
    std::mt19937 rng{getSeed()};

    std::uniform_int_distribution<size_t> list_size_distrib(0, TestSize::L);

    TestResult res{TestSize::M};
    std::vector<int64_t> measures{};

    for (size_t i = 0; i < res.n_tested; ++i) {
        t_list *list = nullptr;
        size_t len{list_size_distrib(rng)};

        std::vector<int> values{};
        for (size_t j = len; j + 1 != 0; --j) {
            values.push_back(j);
        }

        for (auto ci = values.cbegin(); ci != values.cend(); ++ci) {
            ft_list_push_front(
                &list, const_cast<void *>(
                           static_cast<const void *>(std::addressof(*ci))));
        }

        auto cmp = [](void *a, void *b) {
            int lhs = *static_cast<int *>(a);
            int rhs = *static_cast<int *>(b);
            return static_cast<int>(lhs > rhs);
        };

        auto start = std::chrono::steady_clock::now();
        ft_list_sort(&list, cmp);
        auto end = std::chrono::steady_clock::now();
        auto elapsed =
            std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        measures.push_back(elapsed.count());

        for (t_list *prev = nullptr, *cur = list; cur != nullptr;) {
            if (prev && cmp(prev->data, cur->data)) {
                if (!res.n_failures)
                    ++res.n_failures;
            }
            t_list *tmp = prev;
            prev = cur;
            cur = cur->next;
            if (tmp)
                free(tmp);
        }
    }

    __int128_t total = 0;
    for (auto m : measures) {
        total += m;
    }
    int64_t average = total / measures.size();
    (void)average;

    return res;
}

TEST(ft_list_sort_random_sequence) {
    std::mt19937 rng{getSeed()};

    std::uniform_int_distribution<size_t> list_size_distrib(0, TestSize::L);

    TestResult res{TestSize::M};

    std::vector<int64_t> measures{};

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

        auto cmp = [](void *a, void *b) {
            int lhs = *static_cast<int *>(a);
            int rhs = *static_cast<int *>(b);
            return static_cast<int>(lhs > rhs);
        };

        auto start = std::chrono::steady_clock::now();
        ft_list_sort(&list, cmp);
        auto end = std::chrono::steady_clock::now();
        auto elapsed =
            std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        measures.push_back(elapsed.count());

        for (t_list *prev = nullptr, *cur = list; cur != nullptr;) {
            if (prev && cmp(prev->data, cur->data)) {
                if (!res.n_failures)
                    ++res.n_failures;
            }
            t_list *tmp = prev;
            prev = cur;
            cur = cur->next;
            if (tmp) {
                free(tmp);
            }
        }
    }

    __int128_t total = 0;
    for (auto m : measures) {
        total += m;
    }
    int64_t average = total / measures.size();
    (void)average;

    return res;
}

TEST(ft_list_sort_register_integrity) {
    t_list *list = nullptr;
    int value1 = 1;
    int value2 = 2;
    int value3 = 3;
    ft_list_push_front(&list, &value1);
    ft_list_push_front(&list, &value2);
    ft_list_push_front(&list, &value3);
    TestResult res =
        testRegisterIntegrity(ft_list_sort, &list, [](void *a, void *b) {
            int lhs = *static_cast<int *>(a);
            int rhs = *static_cast<int *>(b);
            return static_cast<int>(lhs > rhs);
        });
    return res;
}