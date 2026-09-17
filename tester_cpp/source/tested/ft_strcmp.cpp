/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 12:38:38 by cgajean           #+#    #+#             */
/*   Updated: 2026/09/17 12:38:39 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libasm_decl.hpp"
#include "tester_cpp.hpp"

/**
 * These headers are used by this test routine.
 */
#include <cstring>

/**
 * Compare null-pointer behavior with the standard strcmp implementation.
 */
TEST(ft_strcmp_null_string) {
    std::vector<std::function<int(const char*, const char*)>> f{ft_strcmp,
                                                                strcmp};

    char buff[10]{"test"};
    std::vector<std::pair<char*, const char*>> p{
        {nullptr, nullptr}, {nullptr, buff}, {buff, nullptr}};

    TestResult res{};

    for (auto fn : f) {
        for (auto [destination, source] : p) {
            pid_t pid = fork();

            if (pid > 0) {
                ++res.n_tested;
                int status = 0;
                if (waitpid(pid, &status, 0) == -1 || !WIFSIGNALED(status)) {
                    ++res.n_failures;
                }
            } else if (pid == 0) {
                fn(destination, source);
                _exit(EXIT_FAILURE);
            } else {
                ++res.n_failures;
            }
        }
    }
    return res;
}

/**
 * Compare results for pairs containing the same random string.
 */
TEST(ft_strcmp_equal_random_string) {
    std::mt19937 rng{getSeed()};

    TestResult res{};
    res.n_tested = TestSize::M;

    for (size_t i = 0; i < res.n_tested; ++i) {
        try {
            std::string s = generateRandomString(rng, TestSize::XXL);

            if (ft_strcmp(s.c_str(), s.c_str()) !=
                strcmp(s.c_str(), s.c_str())) {
                ++res.n_failures;
            }
        } catch (...) {
            std::cerr << "ft_strcmp_equal_random_string: unexpected error!\n";
        }
    }
    return res;
}

/**
 * Compare ft_strcmp with strcmp for both orders of every tested character pair.
 */
TEST(ft_strcmp_bruteforce) {
    TestResult res{};
    char s1[2]{}, s2[2]{};

    for (unsigned char c1 = 0; c1 < 254; ++c1) {
        for (unsigned char c2 = c1 + 1; c2 < 255; ++c2) {
            ++res.n_tested;
            *s1 = static_cast<char>(c1);
            *s2 = static_cast<char>(c2);

            if (ft_strcmp(s1, s2) != strcmp(s1, s2) ||
                ft_strcmp(s2, s1) != strcmp(s2, s1)) {
                ++res.n_failures;
            }
        }
    }
    return res;
}

/**
 * Verify that ft_strcmp preserves callee-saved registers.
 */
TEST(ft_strcmp_register_integrity) {
    char destination[12];
    return testRegisterIntegrity(ft_strcmp, destination, "hello world");
}
