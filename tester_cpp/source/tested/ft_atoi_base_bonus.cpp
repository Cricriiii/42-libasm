#include "libasm_decl.hpp"
#include "tester_cpp.hpp"

/**
 * These headers are used by this test routine.
 */
#include <cstring>

const std::vector<char> whitespaces{'\t', '\n', '\v', '\f', '\r', ' '};
const std::vector<char> signs{'+', '-'};

static const std::vector<char> asciiTable(void) {
    std::vector<char> ascii{};
    for (unsigned char i = 0; i != 255; ++i) {
        if (std::find(signs.begin(), signs.end(), i) == signs.end()) {
            ascii.push_back(i);
        }
    }
    return ascii;
}

const std::vector<char> charSet = asciiTable();

static void whitespaceSequence(std::string &s) {
    std::mt19937 rng{getSeed()};

    std::uniform_int_distribution<size_t> wsp_distrib(0,
                                                      whitespaces.size() - 1);
    std::uniform_int_distribution<size_t> length_distrib(1, TestSize::L);

    size_t len{length_distrib(rng)};

    for (size_t idx = 0; idx < len; ++idx) {
        s.push_back(whitespaces[wsp_distrib(rng)]);
    }
}

static int signSequence(std::string &s) {
    std::mt19937 rng{getSeed()};

    std::uniform_int_distribution<size_t> sign_distrib(0, signs.size() - 1);
    std::uniform_int_distribution<size_t> length_distrib(1, TestSize::L);

    size_t len{length_distrib(rng)};

    int sign_value = 1;
    for (size_t idx = 0; idx < len; ++idx) {
        char added_sign = signs[sign_distrib(rng)];
        s.push_back(added_sign);
        if (added_sign == '-') {
            sign_value *= -1;
        }
    }
    return sign_value;
}

TEST(ft_atoi_base_whitespaces_only) {
    TestResult res{TestSize::M};

    std::uniform_int_distribution<size_t> wsp_distrib(0,
                                                      whitespaces.size() - 1);
    std::uniform_int_distribution<size_t> length_distrib(1, TestSize::L);

    for (size_t i = 0; i < res.n_tested; ++i) {
        std::string sample_string{};
        whitespaceSequence(sample_string);
        sample_string.push_back('1');

        if (ft_atoi_base(const_cast<char *>(sample_string.c_str()),
                         const_cast<char *>("01")) != 1) {
            ++res.n_failures;
        }
    }
    return res;
}

TEST(ft_atoi_base_signs_only) {
    TestResult res{TestSize::M};

    std::uniform_int_distribution<size_t> char_distrib(0, charSet.size() - 1);
    std::uniform_int_distribution<size_t> length_distrib(1, TestSize::L);

    for (size_t i = 0; i < res.n_tested; ++i) {
        std::string sample_string{};
        auto sign_value = signSequence(sample_string);
        sample_string.push_back('1');

        if (ft_atoi_base(const_cast<char *>(sample_string.c_str()),
                         const_cast<char *>("01")) != 1 * sign_value) {
            ++res.n_failures;
        }
    }
    return res;
}

TEST(ft_atoi_base_whitespaces_signs_int_values) {
    TestResult res{TestSize::M};

    for (size_t i = 0; i < res.n_tested; ++i) {
        std::string sample_string{};
        whitespaceSequence(sample_string);
        auto sign_value = signSequence(sample_string);

        auto value = randomIntegerValue<int>();
        sample_string += std::to_string(value);

        if (ft_atoi_base(const_cast<char *>(sample_string.c_str()),
                         const_cast<char *>("0123456789")) !=
            value * sign_value) {
            ++res.n_failures;
        }
    }

    return res;
}

TEST(ft_atoi_base_whitespaces_signs_int_garbage_values) {
    TestResult res{TestSize::M};

    for (size_t i = 0; i < res.n_tested; ++i) {
        std::string sample_string{};
        whitespaceSequence(sample_string);
        auto sign_value = signSequence(sample_string);

        auto value = randomIntegerValue<int>();
        sample_string += std::to_string(value);
        sample_string += "garbage";

        if (ft_atoi_base(const_cast<char *>(sample_string.c_str()),
                         const_cast<char *>("0123456789")) !=
            value * sign_value) {
            ++res.n_failures;
        }
    }

    return res;
}

TEST(ft_atoi_base_wrong_base) {
    TestResult res{};

    std::string sample_string{};
    auto value = randomIntegerValue<int>();
    sample_string += std::to_string(value);

    std::string base{"0123456789"};

    std::vector<char> forbidden{signs};
    forbidden.insert(forbidden.end(), whitespaces.begin(), whitespaces.end());

    for (auto c : forbidden) {
        for (size_t i = 0; i <= base.size(); ++i) {
            ++res.n_tested;

            std::string s{base};

            s.insert(i, 1, c);

            if (ft_atoi_base(const_cast<char *>(sample_string.c_str()),
                             const_cast<char *>(s.c_str())) != 0) {
                ++res.n_failures;
            }
        }
    }
    return res;
}
