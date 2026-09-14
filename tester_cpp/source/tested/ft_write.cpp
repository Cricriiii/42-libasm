#include "tester_cpp.hpp"

/**
 * These headers are used by this test routine.
 */
#include <cstring>

#include "libasm_decl.hpp"

/**
 * Test routines
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

TEST(ft_write_null_string) {
    int fd_out = open("/dev/null", O_WRONLY);
    if (fd_out < 0) {
        return TestResult{0, 0};
    }

    TestResult res{TestSize::S};

    for (size_t i = 0; i < res.n_tested; i += TestSize::L) {
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

TEST(ft_write_proper_use) {
    int fd_out = open("/dev/null", O_WRONLY);
    if (fd_out < 0) {
        return TestResult{0, 0};
    }

    std::random_device rd;
    std::mt19937 rng(rd());

    TestResult res{TestSize::M};

    for (size_t i = 0; i < res.n_tested; ++i) {
        std::string s = generateRandomString(rng, TestSize::M);

        set_errno(0);
        ssize_t ret_1 = ft_write(fd_out, s.c_str(), s.size());
        int errno_1 = errno;

        set_errno(0);
        ssize_t ret_2 = ft_write(fd_out, s.c_str(), s.size());
        int errno_2 = errno;

        res.n_failures += (errno_1 != errno_2) || (ret_1 != ret_2);
    }
    return res;
}

TEST(ft_write_excess_write) {
    int fd_out = open("/dev/null", O_WRONLY);
    if (fd_out < 0) {
        return TestResult{0, 0};
    }

    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<size_t> distribution(1, TestSize::M);
    const char* str{"hello world"};

    TestResult res{TestSize::M};

    for (size_t i = 0; i < res.n_tested; ++i) {

        size_t len{distribution(rng)};

        set_errno(0);
        ssize_t ret_1 = ft_write(fd_out, str, len);
        int errno_1 = errno;

        set_errno(0);
        ssize_t ret_2 = ft_write(fd_out, str, len);
        int errno_2 = errno;

        res.n_failures += (errno_1 != errno_2) || (ret_1 != ret_2);
    }
    return res;
}
