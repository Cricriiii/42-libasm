/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 12:38:47 by cgajean           #+#    #+#             */
/*   Updated: 2026/09/17 12:38:48 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libasm_decl.hpp"
#include "tester_cpp.hpp"

/**
 * Compare ft_write and write on a closed file descriptor.
 */
TEST(ft_write_unopened_fd) {
    int fd = unopened_fd(4);

    /* Test ft_write */
    ssize_t ret_1 = ft_write(fd, "hello world", 11);
    int errno_1 = errno;

    /* Reset errno */
    set_errno(0);

    /* Test write */
    ssize_t ret_2 = write(fd, "hello world", 11);
    int errno_2 = errno;

    return TestResult{1, (errno_1 != errno_2) || (ret_1 != ret_2)};
}

/**
 * Compare ft_write and write with a null buffer and increasing byte counts.
 */
TEST(ft_write_null_string) {
    int fd_out = open("/dev/null", O_WRONLY);
    if (fd_out < 0) {
        return TestResult{0, 0};
    }

    TestResult res{TestSize::XXXS};

    for (size_t i = 1; i <= res.n_tested; i *= TestSize::XXXL) {
        set_errno(0);
        ssize_t ret_1 = ft_write(fd_out, nullptr, i);
        int errno_1 = errno;

        set_errno(0);
        ssize_t ret_2 = write(fd_out, nullptr, i);
        int errno_2 = errno;

        res.n_failures += (errno_1 != errno_2) || (ret_1 != ret_2);
    }

    close(fd_out);
    return res;
}

/**
 * Compare return values, errno, and written contents for random strings.
 */
TEST(ft_write_exact_write) {
    std::string outfile = "/tmp/libasm-read-out.txt";
    std::system(std::string{std::string{"touch "} + outfile}.c_str());

    int fd_out = open(outfile.c_str(), O_RDWR);
    if (fd_out < 0) {
        return TestResult{0, 0};
    }

    std::mt19937 rng{getSeed()};

    TestResult res{TestSize::XS};

    for (size_t i = 0; i < res.n_tested; ++i) {
        std::string s = generateRandomString(rng, TestSize::L);

        /* Test return values and errno */
        {
            set_errno(0);
            ssize_t ret_1 = ft_write(fd_out, s.c_str(), s.size());
            int errno_1 = errno;

            set_errno(0);
            ssize_t ret_2 = write(fd_out, s.c_str(), s.size());
            int errno_2 = errno;

            res.n_failures += (errno_1 != errno_2) || (ret_1 != ret_2);
        }

        /* Test what has actually been written by ft_write */
        {
            std::string rd(s.size(), '\0');
            lseek(fd_out, -1 * s.length(), SEEK_CUR);
            ssize_t ret = read(fd_out, rd.data(), s.length());
            if (static_cast<size_t>(ret) != s.length() || s != rd) {
                ++res.n_failures;
            }
        }
    }

    unlink(outfile.c_str());
    return res;
}

/**
 * Verify that ft_write preserves callee-saved registers.
 */
TEST(ft_write_register_integrity) {
    int fd_out = open("/dev/null", O_WRONLY);
    if (fd_out < 0)
        return TestResult{};
    TestResult res = testRegisterIntegrity(ft_write, fd_out, "hello world", 12);
    close(fd_out);
    return res;
}
