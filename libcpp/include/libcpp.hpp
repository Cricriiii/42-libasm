#pragma once

#include <string>
#include <random>

/* generators.cpp */
std::string generate_random_string(std::mt19937 &rng, size_t max_len);