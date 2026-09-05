;   Executable      : ft_strlen
;   Version         : 1.0
;   Created date    : 2026-08-30
;   Last update     : 2026-09-03
;   Author          : Christophe Gajean
;   Description     : Assembly implementation of man 3 strlen
;
;
;   Prototype       : size_t strlen(const char *s);
;
;   Registers       : RDI -> char *restrict dst


SECTION .text

global ft_strlen      ; Make ft_strlen calable / visible from outside

ft_strlen:
    xor rax, rax      ; Set searched byte value (0) in AL as expected by SCASB.
    mov rcx, -1       ; Set the maximum scan count to 64 bits.
                      ; This value means infinity here, as 64-bits exceeds.
                      ; the virtual memory space.

    mov rdx, rdi      ; System V ABI expects the 1st argument in RDI.
                      ; RDI will be the moving pointer of SCASB.
                      ; RDX will be the base pointer.

    cld               ; Set search direction to up-memory.
    repne scasb       ; Repeat while null byte is not found.
                      ; Each loop increments RDI and decrements RCX.

                      ; RDI is now located one byte after null byte.
    dec rdi           ; Make it point to the null character.
    sub rdi, rdx      ; Subtract start position from end position.
    mov rax, rdi      ; Save length in RAX according to System V ABI.
    ret               ; Return to caller.