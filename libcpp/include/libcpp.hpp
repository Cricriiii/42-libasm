#pragma once

#include <random>
#include <string>

/* generators.cpp */
std::string generateRandomString(std::mt19937& rng, size_t max_len);

/* unopened_fd.cpp */
int unopened_fd(int fd);
