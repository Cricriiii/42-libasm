/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 12:50:42 by cgajean           #+#    #+#             */
/*   Updated: 2026/09/20 20:00:38 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#include "TestRegistry.hpp"

TestResult error_report{};

/**
 * Print the tester banner before any test runs.
 */
__attribute__((constructor)) static void print_banner() {
    std::system("clear");
    std::cout << "\n\e[0;37m"
              << "*************************************************************"
                 "***    \n"
              << " _      _ _                           _            _         "
                 "       \n"
              << "| |    (_) |                         | |          | |        "
                 "       \n"
              << "| |     _| |__   __ _ ___ _ __ ___   | |_ ___  ___| |_ ___ _ "
                 "__     \n"
              << "| |    | | '_ \\ / _` / __| '_ ` _ \\  | __/ _ \\/ __| __/ _ "
                 "\\ '__|\n"
              << "| |____| | |_) | (_| \\__ \\ | | | | | | ||  __/\\__ \\ ||  "
                 "__/ |   \n"
              << "|______|_|_.__/ \\__,_|___/_| |_| |_|  "
                 "\\__\\___||___/\\__\\___|_|  \n"
              << "*************************************************************"
                 "***     \n\n";
}

/**
 * Print the aggregate test result after all tests have completed.
 */
__attribute__((destructor)) static void finalize_output() {
    std::cout
        << "\n\e[0;37m"
        << "***************************************************************"
        << "\nTotal succeeded <"
        << (error_report.n_tested - error_report.n_failures) << "/"
        << error_report.n_tested << ">\n"
        << "***************************************************************"
           "\n\n";
}

/**
 * Run every registered test and report its result.
 */
int main(void) {
    const char* outcome[] = {"\e[0;31m[FAIL] ", "\e[0;32m[SUCCESS] "};

    for (auto& t : TestRegistry::getInstance().tests) {
        std::cout << "\e[0;36m[RUN] " << t.name << "... \n";
        try {
            TestResult result = t.fn();
            error_report.n_tested += result.n_tested;
            error_report.n_failures += result.n_failures;

            std::cout << outcome[result.n_tested && result.n_failures == 0]
                      << t.name << "   ("
                      << (result.n_tested - result.n_failures) << "/"
                      << result.n_tested << ")\n";

        } catch (const std::exception& e) {
            std::cerr << "\e[0;31m[ERROR] " << e.what() << "\n";
            ++error_report.n_failures;

        } catch (...) {
            std::cerr << "\e[0;31m[ERROR] Unknown exception\n";
            ++error_report.n_failures;
        }
    }

    return error_report.n_failures != 0;
}
