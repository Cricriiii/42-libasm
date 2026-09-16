#include "libcpp.hpp"

std::mt19937 getSeed() {
    std::random_device rd;
    return std::mt19937{rd()};
}

std::string generateRandomString(std::mt19937& rng, size_t max_len) {
    std::uniform_int_distribution<size_t> len_dist(0, max_len);
    std::uniform_int_distribution<int> char_dist(1, 255);

    size_t len = len_dist(rng);
    std::string s;
    s.reserve(len);

    for (size_t i = 0; i < len; ++i)
        s.push_back(static_cast<char>(char_dist(rng)));

    return s;
}

