;   Executable      : ft_read
;   Version         : 1.0
;   Created date    : 2026-09-07
;   Last update     : 2026-09-07
;   Author          : Christophe Gajean
;   Description     : Assembly implementation of man 2 read
;                     based on the libc prototype.
;
;   Prototype       : ssize_t read(int fd, void buf[.count], size_t count);
;
;   Registers       : RDI -> int fd
;                     RSI -> void buf[.count]
;                     RDX -> size_t count

SECTION .text

extern __errno_location ; Included by <errno.h>
                        ; int * __errno_location(void);
                        ; Returns a pointer to errno

global ft_read      ; Make ft_read callable / visible from outside

ft_read:
    push rbp        ; Create the stack frame
    mov rbp, rsp

    mov rax, 0      ; Specify the sys_read syscall
    syscall         ; Make the kernel call

    cmp rax, 0      ; Check syscall return value
    jl .error       ; If error (RAX<0), jump to the error sequence

    mov rax, rdx    ; Success, ft_read will return 'count' in RAX
    jmp .return     ; Jump to the return sequence

.error:
    neg rax         ; Make errno resulting
                    ; from the previous syscall positive

    mov rcx, rax    ; Set errno aside in the unused RCX register
    call __errno_location wrt ..plt ; Call __errno location through
                    ; the Procedure Linkage table.
                    ; Returns with errno address stored in RAX
                    ; See comments in ft_write.s

    mov [rax], rcx  ; Set errno
    mov rax, -1     ; Set ft_write return value to error (-1)

.return:
    leave           ; Destroy the stack frame
    ret             ; Return