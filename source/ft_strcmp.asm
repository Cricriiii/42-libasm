;   Executable      : ft_strcmp
;   Version         : 1.0
;   Created date    : 2026-09-05
;   Last update     : 2026-09-05
;   Author          : Christophe Gajean
;   Description     : Assembly implementation of man 3 strcmp
;                     based on the libc prototype.
;
;   Prototype       : int strcmp(const char *s1, const char *s2);
;
;   Registers       : RDI -> const char *s1
;                     RSI -> const char *s2

SECTION .text

global ft_strcmp        ; Make ft_strcmp callable / visible from outside

ft_strcmp:
    xor rax, rax        ; Initialize RAX
    xor rcx, rcx        ; Initialize RCX

.compare:
    mov al, byte [rdi]  ; Store current *s1 in AL
    cmp al, 0           ; Test if the end of s1 has been reached
    jz .done            ; If so, the loop is over

    cmp al, byte [rsi]  ; Compare *s1 and current *s2
    jnz .done           ; If different (ZF=0), the loop is over

    inc rdi             ; Else, increment both pointers
    inc rsi
    jmp .compare        ; Loop

.done:
; man 3 strcmp specifies that:
;                         "the comparison is done using unsigned characters".

; So far, only the existence of a divergence between s1 and s2 has been tested,
; not its value.

; In order to conform with the unsignedness requirement, we must extend
; value bit width to 32 bits, as expected by the ft_strcmp return type. 
    movzx eax, byte [rdi]   ; Move current *s1 with zero-extend
    movzx ecx, byte [rsi]   ; Move current *s2 with zero-extend
    sub eax, ecx            ; Store return value (*s1-*s2) in EAX
                            ; in accordance with System V ABI requirements
    ret                     ; Return