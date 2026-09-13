#include "tester_cpp.hpp"

/**
 * These headers are used by this test routine.
 */
#include "libasm_decl.hpp"
#include <cstring>

/**
 * Test routine.
 */

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