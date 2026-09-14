#pragma once

#include <vector>
#include <string>
#include <functional>
#include <utility>
#include <limits>

#include "ASMRegisters.hpp"

struct TestResult {
public:
    int n_tested;
    int n_failures;

    TestResult(): n_tested {0}, n_failures {0} {}
    TestResult(int n): n_tested {n}, n_failures {0} {}
    TestResult(int n, int m): n_tested {n}, n_failures {m} {}
};

struct TestCase {
    std::string                 name;
    std::function<TestResult()> fn;
};

class TestRegistry {
public: 
    static TestRegistry& getInstance() {
        static TestRegistry reg;
        return reg;
    }

    void add(std::string name, std::function<TestResult()> fn) {
        tests.push_back({std::move(name), std::move(fn)});
    }

    std::vector<TestCase> tests;

private:
    TestRegistry() = default;
    TestRegistry(const TestRegistry& other) = delete;
    TestRegistry& operator=(const TestRegistry& other) = delete;
};

struct AutoRegister {
    AutoRegister(const std::string &name, std::function<TestResult()> fn) {
        TestRegistry::getInstance().add(name, std::move(fn));
    }
};

#define TEST(name)                                              \
    TestResult name();                                          \
    static AutoRegister reg_##name(#name, name);                \
    TestResult name()



template <typename Function, typename... Args>
TestResult test_register_integrity(Function function, Args&&... args)
{
    CalleeSavedState before = captureCalleeSavedRegisters();

    std::invoke(
        function,
        std::forward<Args>(args)...
    );

    CalleeSavedState after = captureCalleeSavedRegisters();

    return TestResult{1, before == after ? 0 : 1};
}
