#include <iostream>
#include "TestRegistry.hpp"

int main(void) {
    int failures = 0;
    for (auto &t : TestRegistry::getInstance().tests) {{
        std::cout << "[RUN] " << t.name << "... ";
        try {
            t.fn();
            std::cout << "OK\n";
        } catch (...) {
            std::cout << "FAIL\n"; ++failures;
        }
    }}
    return failures != 0;
}