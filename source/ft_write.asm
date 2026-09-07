;   Executable      : ft_write
;   Version         : 1.0
;   Created date    : 2026-09-05
;   Last update     : 2026-09-07
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

SECTION .text

extern __errno_location ; Included by <errno.h>
                        ; int * __errno_location(void);
                        ; Returns a pointer to errno

extern set_errno        ; Included in ./source/common

global ft_write     ; Make ft_write callable / visible from outside

ft_write:
; Create the stack frame
    push rbp        ; Alignment prologue
    mov rbp, rsp    ; Anchor the base pointer at the stack position

    mov rax, 1      ; Specify sys_write syscall
    syscall         ; Make the kernel call

    cmp rax, 0      ; Check syscall return value
    jl .error       ; If error (RAX<0), jump to the error sequence

; Success and fail paths: RAX contains the number of written bytes
.return:
    leave           ; Destroy the stack frame
    ret

.error:
    mov rdi, rax    ; Prepare call of set_errno with raw errno value
    call set_errno  ; Set errno value

    mov rax, -1     ; Set ft_write return value
    jmp .return     ; Jump to the return sequence
