/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_remove_if_bonus.cpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 12:38:30 by cgajean           #+#    #+#             */
/*   Updated: 2026/09/17 12:38:31 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libasm_decl.hpp"
#include "tester_cpp.hpp"

/**
 * Verify that ft_list_remove_if removes matching nodes at the front.
 */
TEST(ft_list_remove_if_front) {
    t_list* list = nullptr;
    int value = 7;

    size_t n = 11;
    while (n-- != 0) {
        ft_list_push_front(&list, static_cast<void*>(&value));
    }

    auto cmp = [](void* a, void* b) {
        int lhs = *static_cast<int*>(a);
        int rhs = *static_cast<int*>(b);
        return static_cast<int>(lhs != rhs);
    };

    ft_list_remove_if(&list, &value, cmp, free);

    return TestResult{1, static_cast<size_t>(list != nullptr)};
}

/**
 * Verify removal of matching values from random lists.
 */
TEST(ft_list_remove_if_random_sequence) {
    std::mt19937 rng{getSeed()};

    std::uniform_int_distribution<size_t> list_size_distrib(0, TestSize::L);
    std::uniform_int_distribution<size_t> value_distrib(0, TestSize::XXXS);

    TestResult res{TestSize::M};

    for (size_t i = 0; i < res.n_tested; ++i) {
        t_list* list = nullptr;
        size_t len{list_size_distrib(rng)};

        std::vector<int> values{};
        for (size_t j = 0; j < len; ++j) {
            values.push_back(value_distrib(rng));
        }

        for (auto cri = values.crbegin(); cri != values.crend(); ++cri) {
            ft_list_push_front(
                &list, const_cast<void*>(
                           static_cast<const void*>(std::addressof(*cri))));
        }

        auto cmp = [](void* a, void* b) {
            int lhs = *static_cast<int*>(a);
            int rhs = *static_cast<int*>(b);
            return static_cast<int>(lhs != rhs);
        };

        int removed = value_distrib(rng);
        ft_list_remove_if(&list, &removed, cmp, free);

        for (t_list* cur = list; cur != nullptr;) {
            if (!cmp(cur->data, &removed)) {
                ++res.n_failures;
            }

            t_list* next = cur->next;
            free(cur);
            cur = next;
        }
    }

    return res;
}

/**
 * Verify that ft_list_remove_if preserves callee-saved registers.
 */
TEST(ft_list_remove_if_register_integrity) {
    t_list* list = nullptr;
    int value = 3;
    ft_list_push_front(&list, &value);
    TestResult res = testRegisterIntegrity(
        ft_list_remove_if, &list, static_cast<void*>(&value),
        [](void* a, void* b) {
            int lhs = *static_cast<int*>(a);
            int rhs = *static_cast<int*>(b);
            return static_cast<int>(lhs != rhs);
        },
        free);
    if (list) {
        free(list);
    }
    return res;
}
