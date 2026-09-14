#include "tester_cpp.hpp"

/**
 * These headers are used by this test routine.
 */
#include <cstring>

#include "libasm_decl.hpp"

/**
 * Test routines
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
        const bool crashed0 = WIFSIGNALED(status[0]);
        const bool crashed1 = WIFSIGNALED(status[1]);
        res.n_failures += (crashed0 != crashed1);
    }
    return res;
}

TEST(ft_strcpy_random_string) {
    std::random_device rd;
    std::mt19937 rng(rd());

    TestResult res{};
    res.n_tested = TestSize::M;

    for (int i = 0; i < res.n_tested; ++i) {
        char *ft_strcpy_ptr, *strcpy_ptr;

        try {
            std::string s = generate_random_string(rng, TestSize::M);

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

TEST(ft_strcpy_unfit_destination) {
    std::vector<std::function<char*(char*, const char*)>> f{ft_strcpy, strcpy};
    std::random_device rd;
    std::mt19937 rng(rd());

    TestResult res{};

    for (size_t len_max = TestSize::M; len_max > 100; len_max -= 100) {
        int status[2]{};
        int i{};

        std::string s{};
        do {
            s = generate_random_string(rng, len_max);
        } while (s.size() <= 100);

        for (auto fn : f) {
            pid_t pid = fork();

            if (pid > 0) {
                ++res.n_tested;
                waitpid(pid, &status[i++], 0);
            } else if (pid == 0) {
                try {
                    /* Volontarily allocate 100-bytes short segments*/
                    char* cpy_ptr =
                        static_cast<char*>(std::malloc(s.size() - 100));
                    if (!cpy_ptr) {
                        std::cerr << "malloc failed\n";
                        _exit(2);
                    }

                    cpy_ptr = fn(cpy_ptr, s.c_str());
                    _exit(EXIT_SUCCESS);
                } catch (std::exception& e) {
                    std::cerr << e.what() << "\n";
                }
                _exit(EXIT_FAILURE);
            } else {
                ++res.n_failures;
            }
        }

        const bool crashed0 = WIFSIGNALED(status[0]);
        const bool crashed1 = WIFSIGNALED(status[1]);

        if (crashed0 != crashed1) {
            ++res.n_failures;
        }
    }
    return res;
}

TEST(ft_strcpy_register_integrity) {
    char destination[12];
    return testRegisterIntegrity(ft_strcpy, destination, "hello world");
}
