/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 12:38:44 by cgajean           #+#    #+#             */
/*   Updated: 2026/09/17 13:18:12 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libasm_decl.hpp"
#include "tester_cpp.hpp"

/**
 * These headers are used by this test routine.
 */
#include <cstring>

/**
 * Compare null-pointer behavior with the standard strlen implementation.
 */
TEST(ft_strlen_null_string) {
    std::vector<std::function<size_t(const char*)>> f{ft_strlen, strlen};

    TestResult res{};
    int status[2]{};
    int pid[2];
    int i{};

    for (auto fn : f) {
        pid[i] = fork();

        if (pid[i] > 0) {
            if (waitpid(pid[i], &status[i], 0) == -1) {
                if (i == 0) {
                    ++res.n_failures;
                }
            }

        } else if (pid[i] == 0) {
            fn(nullptr);
            std::cerr << "ft_strlen_null_string: function should not accept "
                         "nullptr!\n";
            _exit(EXIT_FAILURE);
        } else {
            std::cerr << "ft_strlen_null_string: fork failed\n";
        }

        ++i;
    }

    const bool same_signal = WIFSIGNALED(status[0]) && WIFSIGNALED(status[1]) &&
                             WTERMSIG(status[0]) == WTERMSIG(status[1]);
    return TestResult{1, !same_signal};
}

/**
 * Compare lengths returned for randomly generated strings.
 */
TEST(ft_strlen_random_string) {
    std::mt19937 rng{getSeed()};

    TestResult res{};
    res.n_tested = TestSize::M;

    for (size_t i = 0; i < res.n_tested; ++i) {
        std::string s = generateRandomString(rng, TestSize::S);
        size_t expected = strlen(s.c_str());
        size_t got = ft_strlen(s.c_str());

        if (got != expected) {
            std::cerr << "FAIL (len=" << s.size() << ", expected=" << expected
                      << ", got=" << got << ")\n";
            ++res.n_failures;
        }
    }
    return res;
}

/**
 * Verify that ft_strlen preserves callee-saved registers.
 */
TEST(ft_strlen_register_integrity) {
    return testRegisterIntegrity(ft_strlen, "hello world");
}
