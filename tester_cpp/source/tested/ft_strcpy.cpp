/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 12:38:40 by cgajean           #+#    #+#             */
/*   Updated: 2026/09/17 13:03:43 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libasm_decl.hpp"
#include "tester_cpp.hpp"

/**
 * These headers are used by this test routine.
 */
#include <cstring>

/**
 * Compare null-pointer behavior with the standard strcpy implementation.
 */
TEST(ft_strcpy_null_string) {
    std::vector<std::function<char*(char*, const char*)>> f{ft_strcpy, strcpy};

    char buff[10]{"test"};
    std::vector<std::pair<char*, const char*>> p{
        {nullptr, nullptr}, {nullptr, buff}, {buff, nullptr}};

    TestResult res{};

    for (auto [destination, source] : p) {
        int status[2]{};
        int i{};

        for (auto fn : f) {
            pid_t pid = fork();

            if (pid > 0) {
                ++res.n_tested;
                waitpid(pid, &status[i++], 0);

            } else if (pid == 0) {
                fn(destination, source);
                _exit(EXIT_FAILURE);

            } else {
                std::cerr << "ft_strcpy_null_string: fork failed\n";
            }
        }
        const bool same_signal = WIFSIGNALED(status[0]) &&
                                 WIFSIGNALED(status[1]) &&
                                 WTERMSIG(status[0]) == WTERMSIG(status[1]);
        if (!same_signal) {
            ++res.n_failures;
        }
    }
    return res;
}

/**
 * Compare copied contents for randomly generated strings.
 */
TEST(ft_strcpy_random_string) {
    std::mt19937 rng{getSeed()};

    TestResult res{};
    res.n_tested = TestSize::M;

    for (size_t i = 0; i < res.n_tested; ++i) {
        char *ft_strcpy_ptr, *strcpy_ptr;

        try {
            std::string s = generateRandomString(rng, TestSize::M);

            ft_strcpy_ptr = static_cast<char*>(std::malloc(s.size() + 1));
            strcpy_ptr = static_cast<char*>(std::malloc(s.size() + 1));

            ft_strcpy_ptr = ft_strcpy(ft_strcpy_ptr, s.c_str());
            strcpy_ptr = strcpy(strcpy_ptr, s.c_str());

            if (strcmp(ft_strcpy_ptr, strcpy_ptr)) {
                ++res.n_failures;
            }

            free(ft_strcpy_ptr);
            free(strcpy_ptr);
        } catch (std::bad_alloc& e) {
            std::cerr << "ft_strcpy_random_string: malloc failed!\n";
            free(strcpy_ptr);
        }
    }
    return res;
}

/**
 * Verify that ft_strcpy preserves callee-saved registers.
 */
TEST(ft_strcpy_register_integrity) {
    char destination[12];
    return testRegisterIntegrity(ft_strcpy, destination, "hello world");
}
