;------------------------------------------------------------------------------
;   Executable      : ft_strcmp
;   Version         : 1.0
;   Created date    : 2026-09-05
;   Last update     : 2026-09-11
;   Author          : Christophe Gajean
;   Description     : Assembly implementation of man 3 strcmp
;                     based on the libc prototype.
;
;   Prototype       : int strcmp(const char *s1, const char *s2);
;
;   Registers       : RDI -> const char *s1
;                     RSI -> const char *s2
;------------------------------------------------------------------------------

SECTION .text           ; Section containing code

global ft_strcmp        ; Make the function callable / visible from outside

ft_strcmp:
    mov al, byte [rdi]  ; Store *s1 in AL
    cmp al, 0           ; Test if the end of s1 has been reached
    jz .end            ; If so, exit loop

    cmp al, byte [rsi]  ; Compare *s1 and *s2
    jnz .end           ; If different (ZF=0), exit loop

                        ; Else
    inc rdi             ; ++s1
    inc rsi             ; ++s2
    jmp ft_strcmp       ; Loop

.end:
; man 3 strcmp specifies that:
;                         "the comparison is done using unsigned characters".

; So far, only the existence of a divergence between s1 and s2 has been tested,
; not its value.

; POSIX.1 specifies only that:
;   The sign of a nonzero return value shall be determined by the sign of the
;    difference between the values of the first pair of bytes (both interpreted
;    as type unsigned char) that differ in the strings being compared.
; In  glibc,  as in most other implementations, the return value is the 
;    arithmetic result of subtracting the last compared byte in s2 from the
;    last compared byte in s1.
;    (If the two characters are equal, this difference is 0.)

    movzx eax, byte [rdi]   ; Zero-extend character pointed to by s1
    movzx ecx, byte [rsi]   ; Zero-extend character pointed to by s2
    sub eax, ecx            ; Store return value (*s1-*s2) in EAX
                            ; in accordance with System V ABI requirements

    ret