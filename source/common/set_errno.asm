;   Executable      : set_errno
;   Version         : 1.0
;   Created date    : 2026-09-07
;   Last update     : 2026-09-07
;   Author          : Christophe Gajean
;   Description     : Provide a generic procedure to set errno value
;
;   Registers       : RDI -> raw errno value as returned by syscalls


SECTION .text       ; Section containing code

extern __errno_location ; Included by <errno.h>
                        ; int * __errno_location(void);
                        ; Returns a pointer to errno

global set_errno    ; Make set_errno visible from outside

set_errno:
; Build the stack frame. Size = 16 bytes
    push rbp        ; Align the stack frame on a 16-bytes boundary
    mov rbp, rsp    ; Anchor the base pointer at the stack position
    sub rsp, 0x10   ; Move RSP 16 bytes away

    neg rdi         ; Negate the raw errno value to make it positive
    mov dword [rbp-0x4], edi    ; Save the errno value

; https://www.tortall.net/projects/yasm/manual/html/objfmt-elf32-wrt.html
; https://www.segmentationfault.fr/linux/role-plt-got-ld-so/
    call __errno_location wrt ..plt ; Get errno memory address
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

    lea r9, [rbp-0x4]   ; Calculate and store the stack address of errno
    mov r8d, [r9]       ; Fetch the errno value and store it in r8
    mov dword [rax], r8d      ; Set the errno value

; Return
    leave
    ret
