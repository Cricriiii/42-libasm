;   Executable      : ft_write
;   Version         : 1.0
;   Created date    : 2026-09-05
;   Last update     : 2026-09-05
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

extern errno_location   ; Included by <errno.h>
                        ; int * __errno_location(void);
                        ; Returns a pointer to errno

global ft_write     ; Make ft_write callable / visible from outside

ft_write:
    mov rax, 1      ; Specify sys_write syscall
    syscall         ; Make the kernel call

    cmp rax, 0      ; Check syscall return value
    jl .error       ; If error (RAX<0), jump to the error sequence

; Success. Return value is the number of written bytes
; This number was passed as 'count' in RDX
    mov rax, rdx    ; The value is stored in RAX
                    ; in accordance with System V ABI requirements
    ret             ; Return to the caller.

.error:
; https://man7.org/linux/man-pages/man2/intro.2.html
; On error, sys_write returns the negated errno value

    neg rax         ; Get the absolute value of errno
    mov r8, rax     ; Set it aside in r8

    call errno_location  ; Get errno memory address
    mov [rax], r8        ; Set errno value as set aside in r8

    mov rax, -1     ; Set ft_write return value
    ret             ; Return