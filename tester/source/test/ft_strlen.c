#include "tester.h"

// int test_ft_strlen(void)
// {
//     const char *samples[] = {
//         "",
//         "\0",
//         "\0\0",
//         "a",
//         "hello",
//         "hello world",
//         "hello\0 world"
//     };

//     const size_t sample_count = sizeof(samples) / sizeof(*samples);

//     for (size_t i = 0; i < sample_count; ++i)
//         assert(ft_strlen(samples[i]) == strlen(samples[i]));

//     return (0);
// }

// int main(void)
// {
//     return (test_ft_strlen());
// }



// bool test_callee_saved(void)
// {
//     unsigned long rbx1, r12_1, r13_1, r14_1, r15_1;
//     unsigned long rbx2, r12_2, r13_2, r14_2, r15_2;

//     // Snapshot AVANT l'appel
//     __asm__ volatile(
//         "mov %%rbx, %0\n\t"
//         "mov %%r12, %1\n\t"
//         "mov %%r13, %2\n\t"
//         "mov %%r14, %3\n\t"
//         "mov %%r15, %4\n\t"
//         : "=r"(rbx1), "=r"(r12_1), "=r"(r13_1), "=r"(r14_1), "=r"(r15_1)
//         :
//         : "memory"
//     );

//     ft_strlen("hello world");

//     // Snapshot APRÈS l'appel
//     __asm__ volatile(
//         "mov %%rbx, %0\n\t"
//         "mov %%r12, %1\n\t"
//         "mov %%r13, %2\n\t"
//         "mov %%r14, %3\n\t"
//         "mov %%r15, %4\n\t"
//         : "=r"(rbx2), "=r"(r12_2), "=r"(r13_2), "=r"(r14_2), "=r"(r15_2)
//         :
//         : "memory"
//     );

//     bool ok = (rbx1 == rbx2 && r12_1 == r12_2 && r13_1 == r13_2
//                && r14_1 == r14_2 && r15_1 == r15_2);

//     printf(ok ? "OK : callee-saved registers were preserved\n"
//               : "FAIL : one or more callee-saved registers were corrupted\n");
//     return ok;
// }

// int main(void)
// {
//     test_callee_saved();
//     return 0;
// }
