/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_size_bonus.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 12:38:32 by cgajean           #+#    #+#             */
/*   Updated: 2026/09/17 12:38:33 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libasm_decl.hpp"
#include "tester_cpp.hpp"

/**
 * Verify that an empty list has size zero.
 */
TEST(ft_list_size_null_list) {
    t_list* list = nullptr;

    return TestResult{1, static_cast<size_t>(ft_list_size(list) != 0 ? 1 : 0)};
}

/**
 * Compare sizes of randomly generated lists with their expected sizes.
 */
TEST(ft_list_size_random_size) {
    std::mt19937 rng{getSeed()};

    std::uniform_int_distribution<size_t> list_size_distrib(0, TestSize::XL);

    TestResult res{TestSize::M};

    constexpr int same_value_for_all = 1;

    for (size_t i = 0; i < res.n_tested; ++i) {
        t_list* list = nullptr;
        size_t generated_list_size{list_size_distrib(rng)};

        for (size_t i = 0; i < generated_list_size; ++i) {
            ft_list_push_front(
                &list, const_cast<void*>(
                           static_cast<const void*>(&same_value_for_all)));
        }

        size_t calculated_list_size = ft_list_size(list);

        if (generated_list_size != calculated_list_size) {
            ++res.n_failures;
        }

        for (t_list* ptr = list; ptr != nullptr;) {
            t_list* next = ptr->next;
            std::free(ptr);
            ptr = next;
        }
    }
    return res;
}

/**
 * Verify that ft_list_size preserves callee-saved registers.
 */
TEST(ft_list_size_register_integrity) {
    t_list* list = nullptr;
    int value = 3;
    ft_list_push_front(&list, &value);
    TestResult res = testRegisterIntegrity(ft_list_size, list);
    free(list);
    return res;
}
