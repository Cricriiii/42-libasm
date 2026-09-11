#include <random>
#include <string>
#include <cstring>
#include <cassert>
#include <iostream>

extern "C" size_t ft_strlen(const char *s);

std::string generate_random_string(std::mt19937 &rng, size_t max_len)
{
    std::uniform_int_distribution<size_t> len_dist(0, max_len);
    std::uniform_int_distribution<int>    char_dist(1, 255);

    size_t len = len_dist(rng);
    std::string s;
    s.reserve(len);

    for (size_t i = 0; i < len; ++i)
        s.push_back(static_cast<char>(char_dist(rng)));

    return s;
}

int main(void)
{
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
    return (failures != 0);
}