#pragma once

#include <vector>
#include <string>
#include <functional>
#include <utility>

struct TestCase {
    std::string             name;
    std::function<void()>   fn;
};

class TestRegistry {
public: 
    static TestRegistry& getInstance() {
        static TestRegistry reg;
        return reg;
    }

    void add(std::string name, std::function<void()> fn) {
        tests.push_back({std::move(name), std::move(fn)});
    }

    std::vector<TestCase> tests;

private:
    TestRegistry() = default;
    TestRegistry(const TestRegistry& other);
    TestRegistry& operator=(const TestRegistry& other);
};

struct AutoRegister {
    AutoRegister(const std::string &name, std::function<void()> fn) {
        TestRegistry::getInstance().add(name, std::move(fn));
    }
};

#define TEST(name)                                              \
    void name();                                                \
    static AutoRegister reg_##name(#name, name);                \
    void name()
