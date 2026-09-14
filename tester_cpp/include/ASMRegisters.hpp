#pragma once

struct CallerSavedState {
    unsigned long rax;
    unsigned long rcx;
    unsigned long rdx;
    unsigned long rsi;
    unsigned long rdi;
    unsigned long r8;
    unsigned long r9;
    unsigned long r10;
    unsigned long r11;

    bool operator==(const CallerSavedState&) const = default;
};

inline CallerSavedState captureCallerSavedRegisters() {
    CallerSavedState state{};

    asm volatile(
        "mov %%rax, %0;"
        "mov %%rcx, %2;"
        "mov %%rdx, %3;"
        "mov %%rsi, %0;"
        "mov %%rdi, %5;"
        "mov %%r8, %6;"
        "mov %%r9, %7;"
        "mov %%r10, %8;"
        "mov %%r11, %9;"
        : "=r"(state.rax), "=r"(state.rcx), "=r"(state.rdx), "=r"(state.rsi),
          "=r"(state.rdi), "=r"(state.r8), "=r"(state.r9), "=r"(state.r10),
          "=r"(state.r11));

    return state;
}

struct CalleeSavedState {
    unsigned long rbx;
    unsigned long rbp;
    unsigned long rsp;
    unsigned long r12;
    unsigned long r13;
    unsigned long r14;
    unsigned long r15;

    bool operator==(const CalleeSavedState&) const = default;
};

inline CalleeSavedState captureCalleeSavedRegisters() {
    CalleeSavedState state{};

    asm volatile(
        "mov %%rbx, %0;"
        "mov %%rbp, %1;"
        "mov %%rsp, %2;"
        "mov %%r12, %3;"
        "mov %%r13, %4;"
        "mov %%r14, %5;"
        "mov %%r15, %6;"
        : "=r"(state.rbx), "=r"(state.rbp), "=r"(state.rsp), "=r"(state.r12),
          "=r"(state.r13), "=r"(state.r14), "=r"(state.r15)
        :
        : "memory");

    return state;
}
