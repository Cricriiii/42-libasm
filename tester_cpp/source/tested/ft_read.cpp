#include "tester_cpp.hpp"

/**
 * These headers are used by this test routine.
 */
#include <cstring>

#include "libasm_decl.hpp"


/**
 * Test routines
 */
TEST(ft_read_unopened_fd) {
    int fd = unopened_fd(4);
    char buf[12]{};

    /* Test ft_read */
    ssize_t ret_1 = ft_read(fd, buf, 12);
    int errno_1 = errno;

    /* Reset errno */
    set_errno(0);

    /* Test read */
    ssize_t ret_2 = read(fd, buf, 12);
    int errno_2 = errno;

    return TestResult{1, (errno_1 != errno_2) || (ret_1 != ret_2)};
}

TEST(ft_read_null_string) {
    int fd_in = open("/dev/random", O_RDONLY);
    if (fd_in < 0) {
        return TestResult{};
    }

    TestResult res{TestSize::S};

    for (size_t i = 0; i < res.n_tested; i += TestSize::L) {
        set_errno(0);
        ssize_t ret_1 = ft_read(fd_in, nullptr, i);
        int errno_1 = errno;
        
        set_errno(0);
        ssize_t ret_2 = read(fd_in, nullptr, i);
        int errno_2 = errno;

        res.n_failures += (errno_1 != errno_2) || (ret_1 != ret_2);
    }

    close(fd_in);
    return res;
}

TEST(ft_read_smaller_read) {
    /* Generate the random engine */
    std::random_device rd;
    std::mt19937 rng(rd());
    
    /* Generate the random sample file */
    std::uniform_int_distribution<size_t> distribution(1, TestSize::XXXL);
    std::string outfile = "/tmp/libasm-read-out.txt";
    size_t file_len = distribution(rng) * 1000;

    std::string cmd = "dd if=/dev/urandom of=" + outfile + " bs=" + std::to_string(file_len) + " count=1 2> /dev/null";
    std::system(cmd.c_str());

    int fd_in_1 = open(outfile.c_str(), O_RDONLY);
    if (fd_in_1 < 0) {
        return TestResult{};
    }

    int fd_in_2 = open(outfile.c_str(), O_RDONLY);
    if (fd_in_2 < 0) {
        close(fd_in_1);
        return TestResult{};
    }    

    TestResult res{TestSize::M};
    
    std::uniform_int_distribution<size_t> distribution_file_len(1, file_len);

    for (size_t i = 0; i < res.n_tested; ++i) {

        size_t len{distribution_file_len(rng)};

        std::vector<char> buf_1(len);
        set_errno(0);
        ssize_t ret_1 = ft_read(fd_in_1, buf_1.data(), len);
        int errno_1 = errno;

        std::vector<char> buf_2(len);
        set_errno(0);
        ssize_t ret_2 = read(fd_in_2, buf_2.data(), len);
        int errno_2 = errno;        

        res.n_failures += (errno_1 != errno_2) || (ret_1 != ret_2) || buf_1 != buf_2;
    }

    close(fd_in_1);
    close(fd_in_2);
    unlink(outfile.c_str());
    return res;
}

TEST(ft_read_exact_read) {
    /* Generate the random engine */
    std::random_device rd;
    std::mt19937 rng(rd());
    
    /* Generate the random sample file */
    std::uniform_int_distribution<size_t> distribution(1, TestSize::XXXL);
    std::string outfile = "/tmp/libasm-read-out.txt";
    size_t file_len = distribution(rng) * 1000;

    std::string cmd = "dd if=/dev/urandom of=" + outfile + " bs=" + std::to_string(file_len) + " count=1 2> /dev/null";
    std::system(cmd.c_str());

    int fd_in_1 = open(outfile.c_str(), O_RDONLY);
    if (fd_in_1 < 0) {
        return TestResult{};
    }

    int fd_in_2 = open(outfile.c_str(), O_RDONLY);
    if (fd_in_2 < 0) {
        close(fd_in_1);
        return TestResult{};
    }    

    TestResult res{1};

    std::vector<char> buf_1(file_len);
    set_errno(0);
    ssize_t ret_1 = ft_read(fd_in_1, buf_1.data(), file_len);
    int errno_1 = errno;

    std::vector<char> buf_2(file_len);
    set_errno(0);
    ssize_t ret_2 = read(fd_in_2, buf_2.data(), file_len);
    int errno_2 = errno;        

    res.n_failures += (errno_1 != errno_2) || (ret_1 != ret_2) || buf_1 != buf_2;

    close(fd_in_1);
    close(fd_in_2);
    unlink(outfile.c_str());
    return res;
}

TEST(ft_read_register_integrity) {
    size_t file_len = TestSize::M;
    std::string outfile = "/tmp/libasm-read-out.txt";
    std::string cmd = "dd if=/dev/urandom of=" + outfile + " bs=" + std::to_string(file_len) + " count=1 2> /dev/null";
    std::system(cmd.c_str());

    int fd_in = open(outfile.c_str(), O_RDONLY);
    std::vector<char> buf(file_len);
    if (fd_in < 0) return TestResult{};
    TestResult res = testRegisterIntegrity(ft_read, fd_in, buf.data(), file_len);
    close(fd_in);
    return res;
}