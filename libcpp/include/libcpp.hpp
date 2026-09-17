#pragma once

#include <limits>
#include <random>
#include <string>

/* generators.cpp */
std::mt19937 getSeed();
std::string generateRandomString(std::mt19937& rng, size_t max_len);

/* unopened_fd.cpp */
int unopened_fd(int fd);

/**
 * Generate a random value of the requested integral type.
 */
template <typename T>
T randomIntegerValue() {
    std::mt19937 rng{getSeed()};
    std::uniform_int_distribution<T> range(std::numeric_limits<T>::min(),
                                           std::numeric_limits<T>::max());
    return range(rng);
}