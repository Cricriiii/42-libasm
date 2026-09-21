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

There are two ways to build and test the project:

- [Local build](#local-build): uses the tools installed on the host system.
- [Docker build](#docker-build): uses the environment defined by `Dockerfile`.

## Local build

### Prerequisites

- Linux on an x86-64 system
- GNU Make
- NASM
- A C++ compiler with C++23 support
- GNU binutils (`ar`)

On Debian or Ubuntu, install the required tools with:

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

### Rebuild everything with the bonus

```sh
make re
```

### Clean generated files

Remove generated object files:

```sh
make clean
```

Remove generated object files and archives:

```sh
make fclean
```

### Other local targets

Format C++ source files:

```sh
make format
```

Display all available Makefile targets:

```sh
make help
```

## Docker build

### Prerequisites

- Docker

The `Dockerfile` is based on Fedora and installs NASM, `g++`, and GNU Make.
It copies the project into the image and runs `make bonus` during the image
build. The resulting image uses `tester_cpp/libasm_tester` as its entrypoint.

### Build the Docker image

From the repository root:

```sh
make docker
```

This target first runs `make fclean` locally, then builds the Docker image with
the bonus library and tester.

### Run the Dockerized tester

```sh
make test_docker
```

The tester starts automatically when the container is launched because it is
the image entrypoint.

## Technical Stack

- NASM x86-64 assembly
- System V AMD64 ABI
- C++23 for the test infrastructure and support utilities
- GNU Make for the build system
- Static archives created with `ar`
- Docker for the isolated build and test environment

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
Dockerfile        Docker build environment and tester entrypoint
Makefile		  Root Makefile, general builder and tester
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

AI was used to help review test coverage, identify undefined-behavior risks in
invalid-input tests, improve comments, and organize this documentation.
