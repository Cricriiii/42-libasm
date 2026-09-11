;------------------------------------------------------------------------------
;   Executable      : set_errno
;   Version         : 1.0
;   Created date    : 2026-09-07
;   Last update     : 2026-09-07
;   Author          : Christophe Gajean
;   Description     : Provide a generic procedure to set errno value
;
;   Registers       : RDI -> raw errno value as returned by syscalls
;------------------------------------------------------------------------------

SECTION .text               ; Section containing code

extern __errno_location     ; Included by <errno.h>
                            ; int * __errno_location(void);
                            ; Returns a pointer to errno

global set_errno            ; Make the function callable / visible from outside

%define ERRVAL rbp-0x04

set_errno:
; Create the stack frame
    push rbp                ; Alignment prologue
    mov rbp, rsp            ; Anchor the base pointer at the stack position
    sub rsp, 0x10           ; Creates a 16 bytes wide stack frame

; Set errno
    neg rdi                 ; Compute the absolute errno value
    mov [ERRVAL], edi       ; Set the errno value aside on the stack

    ; https://www.tortall.net/projects/yasm/manual/html/objfmt-elf32-wrt.html
    ; https://www.segmentationfault.fr/linux/role-plt-got-ld-so/
    call __errno_location wrt ..plt ; Get errno memory address
                                    ;
                                    ; Linux programs are linked as PIE
                                    ; (Position Independant Executable).
                                    ; However, the linking process requires
                                    ; that the memory offset between all the
                                    ; 'call' instructions to be resolved
                                    ; beforehands
                                    ;
                                    ; With a PIC (Program Independant Code)
                                    ; it is impossible to do so with external
                                    ; librairies such as glibc (also PIC), 
                                    ; since offsets vary from one execution
                                    ; to another
                                    ;
                                    ; It is then necessary to build a dynamic
                                    ; interface, called PLT (Procedure Linkage
                                    ; Table), whose role is to dynamically
                                    ; interface the external procedures
                                    ; addresses and the local call instructions
                                    ;
                                    ; The WRT operator and the special symbol
                                    ; '..plt' do so.

    mov r8d, [ERRVAL]               ; Fetch the errno value and store it in r8
    mov dword [rax], r8d            ; Set the errno value

; Leave function
    leave           ; Epilogue: destroy the stack frame
    ret