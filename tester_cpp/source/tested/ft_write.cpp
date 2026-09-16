#include "tester_cpp.hpp"
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

TEST(ft_write_exact_write) {
    int fd_out = open("/dev/null", O_WRONLY);
    if (fd_out < 0) {
        return TestResult{0, 0};
    }

    std::mt19937 rng{getSeed()};

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

TEST(ft_write_register_integrity) {
    int fd_out = open("/dev/null", O_WRONLY);
    if (fd_out < 0) return TestResult{};
    TestResult res = testRegisterIntegrity(ft_write, fd_out, "hello world", 12);
    close(fd_out);
    return res;
}
