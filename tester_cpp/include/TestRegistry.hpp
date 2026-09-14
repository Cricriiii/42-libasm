#pragma once

#include <functional>
#include <limits>
#include <string>
#include <utility>
#include <vector>

#include <unistd.h>
#include <fcntl.h>

#include "ASMRegisters.hpp"

enum TestSize : size_t {
    XXXS = 10,
    XXS = 50,
    XS = 100,
    S = 500,
    M = 1000,
    L = 5000,
    XL = 10000,
    XXL = 50000,
    XXXL = 100000
};

struct TestResult {
public:
    size_t n_tested;
    size_t n_failures;

    TestResult() : n_tested{0}, n_failures{0} {
    }
    TestResult(size_t n) : n_tested{n}, n_failures{0} {
    }
    TestResult(size_t n, size_t m) : n_tested{n}, n_failures{m} {
    }
};

struct TestCase {
    std::string name;
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
    AutoRegister(const std::string& name, std::function<TestResult()> fn) {
        TestRegistry::getInstance().add(name, std::move(fn));
    }
};

#define TEST(name)                               \
    TestResult name();                           \
    static AutoRegister reg_##name(#name, name); \
    TestResult name()

template <typename Function, typename... Args>
TestResult testRegisterIntegrity(Function function, Args&&... args) {
    CalleeSavedState before = captureCalleeSavedRegisters();

    std::invoke(function, std::forward<Args>(args)...);

    CalleeSavedState after = captureCalleeSavedRegisters();

    return TestResult{1, before == after ? 0 : 1};
}
