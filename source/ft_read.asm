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

extern set_errno    ; Included in ./source/common

global ft_read      ; Make ft_read callable / visible from outside

ft_read:
; Create the stack frame
    push rbp        ; Alignment prologue
    mov rbp, rsp    ; Anchor the base pointer at the stack position

    mov rax, 0      ; Specify the sys_read syscall
    syscall         ; Make the kernel call

    cmp rax, 0      ; Check syscall return value
    jl .error       ; If error (RAX<0), jump to the error sequence

; Success and fail paths: RAX contains the number of written bytes
.epilogue:
    leave           ; Destroy the stack frame
    ret

.error:
    mov rdi, rax    ; Prepare call of set_errno with raw errno value
    call set_errno  ; Set errno value

    mov rax, -1     ; Set ft_write return value
    jmp .epilogue   ; Jump to the return sequence

