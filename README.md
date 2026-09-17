*This project has been created as part of the 42 curriculum by cgajean.*

# libasm

## Description

`libasm` is an x86-64 assembly library developed as part of the 42 curriculum.
The project reimplements selected standard C and POSIX functions using NASM
assembly while respecting the System V AMD64 calling convention.

The mandatory part includes:

- `ft_strlen`
- `ft_strcpy`
- `ft_strcmp`
- `ft_write`
- `ft_read`
- `ft_strdup`

The bonus part includes linked-list utilities and base conversion:

- `ft_atoi_base`
- `ft_list_push_front`
- `ft_list_size`
- `ft_list_sort`
- `ft_list_remove_if`

The repository also contains `libcpp`, a small C++ support library used by the
tester, and a dedicated C++ test suite in `tester_cpp`.

## Instructions

### Prerequisites

- Linux on an x86-64 system
- GNU Make
- NASM
- A C++ compiler with C++23 support
- GNU binutils (`ar`)

On Debian or Ubuntu, the required tools can be installed with:

```sh
sudo apt install build-essential nasm
```

### Build the mandatory library and tester

From the repository root:

```sh
make
```

This builds:

- `libasm/libasm.a`
- `libcpp/libcpp.a`
- `tester_cpp/libasm_tester`

### Run the mandatory tests

```sh
make test
```

### Build and run the bonus tests

```sh
make bonus
make test
```

### Clean generated files

```sh
make clean
```

To remove generated files and archives completely:

```sh
make fclean
```

To rebuild everything, including the bonus library and tests:

```sh
make re
```

## Technical Stack

- NASM x86-64 assembly
- System V AMD64 ABI
- C++23 for the test infrastructure and support utilities
- GNU Make for the build system
- Static archives created with `ar`

Assembly is used for the functions under evaluation. C++ is used only for the
test runner and its support utilities, which makes it possible to compare the
assembly implementations with the corresponding libc functions.

## Project Structure

```text
libasm/
	source/       Assembly implementations
	Makefile      Library build rules
libcpp/
	include/      C++ support declarations
	source/       Random generators and test helpers
tester_cpp/
	include/      Test framework and declarations
	source/       Mandatory and bonus tests
	README.md     Tester-specific documentation
```

## Testing

The tester compares return values, `errno`, copied or read data, linked-list
results, and callee-saved register preservation where applicable. Invalid-input
tests that may terminate a process are isolated in child processes.

## Resources

- [x64 Assembly Language - Programming with Linux, 4th ed., Jeff Duntemann](https://www.wiley.com/en-us/x64+Assembly+Language+Step-by-Step%3A+Programming+with+Linux%2C+4th+Edition-p-9781394155248)
- [System V AMD64 ABI](https://refspecs.linuxbase.org/elf/x86_64-abi-0.99.pdf)
- [Linux manual pages](https://man7.org/linux/man-pages/)
- [C++ reference](https://en.cppreference.com/)
- 42 `libasm` subject and evaluation guidelines

AI was used to help review test coverage, identify undefined-behavior risks in
invalid-input tests, improve comments, and organize this documentation.
