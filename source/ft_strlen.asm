;------------------------------------------------------------------------------
;   Executable      : ft_strlen
;   Version         : 1.0
;   Created date    : 2026-08-30
;   Last update     : 2026-09-11
;   Author          : Christophe Gajean
;   Description     : Assembly implementation of man 3 strlen
;
;
;   Prototype       : size_t strlen(const char *s);
;
;   Registers       : RDI -> char *restrict dst
;------------------------------------------------------------------------------

SECTION .text       ; Section containing code

global ft_strlen    ; Make the function callable / visible from outside

ft_strlen:
    push rbp        ; Alignment prologue
    mov rbp, rsp    ; Anchor the base pointer at the stack position

    xor rax, rax    ; Set searched byte value (0) in AL as expected by SCASB
    mov rcx, -1     ; Set the maximum scan count to 64 bits
                    ; This value means infinity here, as 64-bits exceeds
                    ; the virtual memory space

    mov rdx, rdi    ; System V ABI expects the 1st argument in RDI
                    ; Make RDI points to the first byte of the string
                    ; RDX will be the base pointer
                    ; RDI will scan the string during SCASB's loop

    cld             ; Set search direction to up-memory
    repne scasb     ; Scan the string while a null byte is not found
                    ; Each loop increments RDI and decrements RCX

                    ; RDI is now located one byte after null byte
    dec rdi         ; Make it point to the null character
    sub rdi, rdx    ; Subtract start position from end position
    mov rax, rdi    ; Save string length in RAX (size_t is 64 bits)
                    ; in accordance with System V ABI requirements

    leave           ; Epilogue: destroy the stack frame
    ret