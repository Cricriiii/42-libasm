#include "tester_cpp.hpp"
#include "libasm_decl.hpp"

/**
 * These headers are used by this test routine.
 */
#include <cstring>



/**
 * Test routines
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

    const bool crashed0 = WIFSIGNALED(status[0]);
    const bool crashed1 = WIFSIGNALED(status[1]);
    return TestResult{1, crashed0 != crashed1};
}

TEST(ft_strdup_random_string) {
    std::random_device rd;
    std::mt19937 rng(rd());

    TestResult res{};
    res.n_tested = TestSize::XXL;

    for (size_t i = 0; i < res.n_tested; ++i) {
        char *ft_strdup_ptr, *strdup_ptr;

        try {
            std::string s = generateRandomString(rng, TestSize::M);

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

TEST(ft_strdup_register_integrity) {
    return testRegisterIntegrity(ft_strdup, "hello world");
}