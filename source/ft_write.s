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

global ft_write     ; Make ft_write callable / visible from outside

ft_write:
    push rbp        ; Create the stack frame
    mov rbp, rsp

    mov rax, 1      ; Specify sys_write syscall
    syscall         ; Make the kernel call

    cmp rax, 0      ; Check syscall return value
    jl .error       ; If error (RAX<0), jump to the error sequence

; Success. Return value is the number of written bytes
; This number was passed as 'count' in RDX
    mov rax, rdx    ; The value is stored in RAX
                    ; in accordance with System V ABI requirements
    jmp .return     ; Return to the return sequence

.error:
; https://man7.org/linux/man-pages/man2/intro.2.html
; On error, sys_write returns the negated errno value

    neg rax         ; Get the absolute value of errno
    mov rcx, rax    ; Set it aside in rcx

; https://www.tortall.net/projects/yasm/manual/html/objfmt-elf32-wrt.html
; https://www.segmentationfault.fr/linux/role-plt-got-ld-so/
    call __errno_location wrt ..plt  ; Get errno memory address
                                     ;
                                     ; Linux programs are linked as PIE
                                     ; (Position Independant Executable).
                                     ; On the other hand, the linking process
                                     ; requires the memory offset between
                                     ; 'call' instruction to be resolved.
                                     ;
                                     ; With a PIC (Program Independant Code)
                                     ; it is impossible to do so with external
                                     ; librairies such as glibc (also PIC), 
                                     ; since offsets vary from one execution
                                     ; to another.
                                     ;
                                     ; It is necessary to build a dynamic
                                     ; interface, called PLT (Procedure Linkage
                                     ; Table), whose role is to store
                                     ; dynamically the external procedures
                                     ; addresses, resolved at linking.
                                     ;
                                     ; The WRT operator and the special symbol
                                     ; '..plt' does so.
                                     ;                                 
    mov [rax], rcx                   ; Set errno value as set aside in rcx

    mov rax, -1     ; Set ft_write return value

.return:
    leave           ; Destroy the stack frame
    ;mov rsp, rbp   ; It is equivalent to
    ;pop rbp        ;    
    ret             ; Return