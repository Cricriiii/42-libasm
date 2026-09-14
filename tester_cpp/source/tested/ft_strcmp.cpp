#include "tester_cpp.hpp"

/**
 * These headers are used by this test routine.
 */
#include <cstring>

#include "libasm_decl.hpp"

/**
 * Test routines
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

TEST(ft_strcmp_equal_random_string) {
    std::random_device rd;
    std::mt19937 rng(rd());

    TestResult res{};
    res.n_tested = TestSize::M;

    for (int i = 0; i < res.n_tested; ++i) {
        try {
            std::string s = generate_random_string(rng, TestSize::XXL);

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

TEST(ft_strcmp_different_random_string) {
    std::random_device rd;
    std::mt19937 rng(rd());

    TestResult res{};
    res.n_tested = TestSize::L;

    for (int i = 0; i < res.n_tested; ++i) {
        try {
            std::string s1 = generate_random_string(rng, TestSize::M);
            std::string s2 = generate_random_string(rng, TestSize::M);

            if (ft_strcmp(s1.c_str(), s2.c_str()) !=
                strcmp(s1.c_str(), s2.c_str())) {
                ++res.n_failures;
            }
        } catch (...) {
            std::cerr << "ft_strcmp_equal_random_string: unexpected error!\n";
        }
    }
    return res;
}

TEST(ft_strcmp_register_integrity) {
    char destination[12];
    return testRegisterIntegrity(ft_strcmp, destination, "hello world");
}
