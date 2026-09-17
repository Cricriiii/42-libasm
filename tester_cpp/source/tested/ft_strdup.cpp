/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 12:38:42 by cgajean           #+#    #+#             */
/*   Updated: 2026/09/17 13:07:18 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libasm_decl.hpp"
#include "tester_cpp.hpp"

/**
 * These headers are used by this test routine.
 */
#include <cstring>

/**
 * Compare null-pointer behavior with the standard strdup implementation.
 */
TEST(ft_strdup_null_string) {
    std::vector<std::function<char*(const char*)>> f{ft_strdup, strdup};

    int status[2]{};
    int i{};

    for (auto fn : f) {
        pid_t pid = fork();

        if (pid > 0) {
            waitpid(pid, &status[i++], 0);

        } else if (pid == 0) {
            fn(nullptr);
            _exit(EXIT_FAILURE);

        } else {
            std::cerr << "ft_strdup_null_string: fork failed\n";
        }
    }

    const bool same_signal = WIFSIGNALED(status[0]) && WIFSIGNALED(status[1]) &&
                             WTERMSIG(status[0]) == WTERMSIG(status[1]);
    return TestResult{1, !same_signal};
}

/**
 * Compare duplicated contents for randomly generated strings.
 */
TEST(ft_strdup_random_string) {
    std::mt19937 rng{getSeed()};

    TestResult res{};
    res.n_tested = TestSize::XL;

    for (size_t i = 0; i < res.n_tested; ++i) {
        char *ft_strdup_ptr = nullptr, *strdup_ptr = nullptr;

        try {
            std::string s = generateRandomString(rng, TestSize::XXXL);

            ft_strdup_ptr = ft_strdup(s.c_str());
            strdup_ptr = strdup(s.c_str());

            if (strcmp(ft_strdup_ptr, strdup_ptr)) {
                ++res.n_failures;
            }

            free(ft_strdup_ptr);
            free(strdup_ptr);
        } catch (std::bad_alloc& e) {
            std::cerr << "ft_strdup_random_string: malloc failed!\n";
            free(strdup_ptr);
        }
    }
    return res;
}

/**
 * Verify that ft_strdup preserves callee-saved registers.
 */
TEST(ft_strdup_register_integrity) {
    return testRegisterIntegrity(ft_strdup, "hello world");
}