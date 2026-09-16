#include "tester_cpp.hpp"
#include "libasm_decl.hpp"

/**
 * These headers are used by this test routine.
 */
#include <cstring>


/**
 * Test routines
 */

TEST(ft_strlen_null_string) {
    std::vector<std::function<size_t(const char*)>> f{ft_strlen, strlen};

    TestResult res{};
    int status[2]{};
    int i{};

    for (auto fn : f) {
        pid_t pid = fork();

        if (pid > 0) {
            ++res.n_tested;
            if (waitpid(pid, &status[i++], 0) == -1) {
                ++res.n_failures;
            }

        } else if (pid == 0) {
            fn(nullptr);
            std::cerr << "ft_strlen_null_string: function should not accept "
                         "nullptr!\n";
            _exit(EXIT_FAILURE);
        } else {
            std::cerr << "ft_strlen_null_string: fork failed\n";
            ++res.n_failures;
        }
    }

    const bool crashed0 = WIFSIGNALED(status[0]);
    const bool crashed1 = WIFSIGNALED(status[1]);
    res.n_failures += (crashed0 != crashed1);

    return res;
}

TEST(ft_strlen_random_string) {
    std::random_device rd;
    std::mt19937 rng(rd());

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

TEST(ft_strlen_register_integrity) {
    return testRegisterIntegrity(ft_strlen, "hello world");
}
