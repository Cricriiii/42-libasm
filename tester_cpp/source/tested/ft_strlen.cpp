#include "tester_cpp.hpp"

/**
 * These headers are used by this test routine.
 */
#include "libasm_decl.hpp"
#include <cstring>

/**
 * Test routines
 */

TEST(ft_strlen_null_string) {
    std::vector<std::function<size_t(const char *)> > f {ft_strlen, strlen};
    int failures = 0;

    for (auto fn: f) {
        pid_t pid = fork();
        int status = 0;

        if (pid > 0) {
            if (waitpid(pid, &status, 0) == -1 || !WIFSIGNALED(status)) {
                ++failures;
            }

        } else if (pid == 0) {
            fn(nullptr);
            std::cerr << "ft_strlen_null_string: function should not accept nullptr!\n";
            _exit(EXIT_FAILURE);
        } else {
            std::cerr << "ft_strlen_null_string: fork failed\n";
            ++failures;
        }
    }

    std::cout << f.size() - failures << "/" << f.size() << " OK\n";
}

TEST(ft_strlen_random_string) {
    std::random_device rd;
    std::mt19937 rng(rd());

    const int nb_tests = 100000;
    int failures = 0;

    for (int i = 0; i < nb_tests; ++i)
    {
        std::string s = generate_random_string(rng, 500);
        size_t expected = strlen(s.c_str());
        size_t got      = ft_strlen(s.c_str());

        if (got != expected)
        {
            std::cerr << "FAIL (len=" << s.size() << ", expected="
                      << expected << ", got=" << got << ")\n";
            ++failures;
        }
    }

    std::cout << (nb_tests - failures) << "/" << nb_tests << " OK\n";
}