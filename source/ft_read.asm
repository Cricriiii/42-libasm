;------------------------------------------------------------------------------
;   Executable      : ft_read
;   Version         : 1.0
;   Created date    : 2026-09-07
;   Last update     : 2026-09-11
;   Author          : Christophe Gajean
;   Description     : Assembly implementation of man 2 read
;                     based on the libc prototype.
;
;   Prototype       : ssize_t read(int fd, void buf[.count], size_t count);
;
;   Registers       : RDI -> int fd
;                     RSI -> void buf[.count]
;                     RDX -> size_t count
;------------------------------------------------------------------------------


SECTION .text       ; Section containing code

extern set_errno    ; Included in ./source/common

global ft_read      ; Make the function callable / visible from outside

ft_read:
    mov rax, 0      ; Specify the sys_read syscall
                    ; The RDI, RSI and RDX registers are already set
    syscall         ; Make the kernel call

    cmp rax, 0      ; Check syscall return value
    jl .error       ; Expected return: 0 or positive -> OK, else Error

; Success and fail paths: here, RAX contains the return value
.end:
    ret

.error:
    mov rdi, rax    ; Prepare call of set_errno with raw errno value
    call set_errno  ; Set errno value

    mov rax, -1     ; Set ft_write return value
    jmp .end        ; Jump to the return sequence