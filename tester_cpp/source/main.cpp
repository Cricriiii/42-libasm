#include <iostream>

#include "TestRegistry.hpp"

int main(void) {
    TestResult error_report{};
    const char* outcome[] = {"[FAIL] ", "[SUCCESS] "};

    for (auto& t : TestRegistry::getInstance().tests) {
        std::cout << "[RUN] " << t.name << "... \n";

        try {
            TestResult result = t.fn();
            error_report.n_tested += result.n_tested;
            error_report.n_failures += result.n_failures;

            std::cout << outcome[result.n_failures == 0] << t.name << "   ("
                      << (result.n_tested - result.n_failures) << "/"
                      << result.n_tested << ")\n";

        } catch (const std::exception& e) {
            std::cerr << "[ERROR] " << e.what() << "\n";
            ++error_report.n_failures;

        } catch (...) {
            std::cerr << "[ERROR] Unknown exception\n";
            ++error_report.n_failures;
        }
    }
    return error_report.n_failures != 0;
}