/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TestRegistry.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 12:38:59 by cgajean           #+#    #+#             */
/*   Updated: 2026/09/17 12:39:00 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <fcntl.h>
#include <unistd.h>

#include <functional>
#include <limits>
#include <string>
#include <utility>
#include <vector>

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

    /**
     * Create an empty test result.
     */
    TestResult() : n_tested{0}, n_failures{0} {
    }

    /**
     * Create a result with a test count and no failures.
     */
    TestResult(size_t tested) : n_tested{tested}, n_failures{0} {
    }

    /**
     * Create a result with explicit test and failure counts.
     */
    TestResult(size_t tested, size_t failed)
        : n_tested{tested}, n_failures{failed} {
    }
};

struct TestCase {
    std::string name;
    std::function<TestResult()> fn;
};

class TestRegistry {
public:
    /**
     * Return the process-wide registry instance.
     */
    static TestRegistry& getInstance() {
        static TestRegistry reg;
        return reg;
    }

    /**
     * Register a test name and its callable implementation.
     */
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
    /**
     * Register a test during static initialization.
     */
    AutoRegister(const std::string& name, std::function<TestResult()> fn) {
        TestRegistry::getInstance().add(name, std::move(fn));
    }
};
/**
 * Check that a function preserves all callee-saved registers.
 */

#define TEST(name)                               \
    TestResult name();                           \
    static AutoRegister reg_##name(#name, name); \
    TestResult name()

template <typename Function, typename... Args>
TestResult testRegisterIntegrity(Function function, Args&&... args) {
    CalleeSavedState before = captureCalleeSavedRegisters();

    std::invoke(function, std::forward<Args>(args)...);

    CalleeSavedState after = captureCalleeSavedRegisters();

    return TestResult{1, static_cast<size_t>(before == after ? 0 : 1)};
}
