# libasm Tester

## Description

`libasm_tester` is the C++23 test runner for the `libasm` project. It compares
the assembly implementations with the corresponding libc or POSIX functions
and checks returned values, `errno`, data contents, linked-list behavior, and
callee-saved register preservation.

The tester has two configurations:

- Mandatory tests for the required `libasm` functions.
- Bonus tests for `ft_atoi_base` and linked-list functions.

## Prerequisites

Build the libraries from the repository root before building the tester:

- Linux x86-64
- GNU Make
- NASM
- A C++ compiler with C++23 support

## Build From the Repository Root

Build the mandatory tester:

```sh
make
```

Build the tester with bonus tests:

```sh
make bonus
```

Run the executable:

```sh
make test
```

The executable is generated at:

```text
tester_cpp/libasm_tester
```

## Build From This Directory

The libraries must already exist in `libasm/libasm.a` and `libcpp/libcpp.a`.

```sh
make
./libasm_tester
```

For the bonus test suite:

```sh
make bonus
./libasm_tester
```

## Useful Targets

```sh
make clean   # Remove tester object files
make fclean  # Remove object files and libasm_tester
make re      # Clean and rebuild the mandatory tester
make help    # Display available targets
```

## Test Layout

```text
include/
  TestRegistry.hpp       Test registration and result types
  ASMRegisters.hpp       Register-preservation helpers
  tested/libasm_decl.hpp Assembly function declarations
source/
  main.cpp               Test runner entry point
  tested/                Mandatory and bonus test cases
```

Each test returns a `TestResult` containing the number of checks performed and
the number of failures. The process exits with a non-zero status when at least
one check fails.
