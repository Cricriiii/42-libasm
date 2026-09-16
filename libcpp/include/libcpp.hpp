#pragma once

#include <limits>
#include <random>
#include <string>

/* generators.cpp */
std::mt19937 getSeed();
std::string generateRandomString(std::mt19937& rng, size_t max_len);

/* unopened_fd.cpp */
int unopened_fd(int fd);

template <typename T>
T randomIntegerValue() {
    using namespace std;
    mt19937 rng{getSeed()};
    uniform_int_distribution<T> range(numeric_limits<T>::min(),
                                      numeric_limits<T>::max());
    return range(rng);
}