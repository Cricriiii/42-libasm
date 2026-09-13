;------------------------------------------------------------------------------
;   Executable      : ft_write
;   Version         : 1.0
;   Created date    : 2026-09-05
;   Last update     : 2026-09-11
;   Author          : Christophe Gajean
;   Description     : Assembly implementation of man 2 write
;                     based on the libc prototype.
;
;   Prototype       : ssize_t write(
;                               int fd, const void buf[.count], size_t count);
;
;   Registers       : RDI -> int fd
;                     RSI -> const void buf[.count]
;                     RDX -> size_t count
;------------------------------------------------------------------------------

SECTION .text       ; Section containing code

extern set_errno    ; Included in ./source/common

global ft_write     ; Make the function callable / visible from outside

ft_write:
    mov rax, 1      ; Specify sys_write syscall
                    ; The RDI, RSI and RDX registers are already set
    syscall         ; Make the kernel call

    cmp rax, 0      ; Check syscall return status
    jl .error       ; Expected return: 0 or positive -> OK, else Error

; Success and fail paths: here, RAX contains the return value
.end:
    ret

.error:
    mov rdi, rax    ; Put the errno value as returned by the syscall
    call set_errno  ; Set errno

    mov rax, -1     ; Set ft_write return value to -1 (error)
    jmp .end