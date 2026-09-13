#pragma once

#include <iostream>
#include <string>
#include <random>

#include <unistd.h>
#include <sys/wait.h>

#include "libcpp.hpp"
#include "TestRegistry.hpp"

enum class exit_type {
    EXITED, SIGNALED, STOPPED, CONTINUED
};