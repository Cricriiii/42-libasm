;------------------------------------------------------------------------------
;   Executable      : ft_strcpy
;   Version         : 1.0
;   Created date    : 2026-09-05
;   Last update     : 2026-09-11
;   Author          : Christophe Gajean
;   Description     : Assembly implementation of man 3 strcpy
;                     based on the libc prototype.
;
;   Prototype       : char *strcpy(char *restrict dst, 
;                                    const char *restrict src);
;
;   Registers       : RDI -> char *restrict dst
;                     RSI -> const char *restrict src
;------------------------------------------------------------------------------

SECTION .text

global ft_strcpy        ; Make the function callable / visible from outside

ft_strcpy:
; Create the stack frame
    push rbp            ; Alignment prologue
    mov rbp, rsp        ; Anchor the base pointer at the stack position

    mov rax, rdi        ; Set aside 'dst' parameter as the return value

;   mov rcx, -1         ; strcpy only stops at a null byte or segfault
                        ; STOSB won't require a counter

.copy:
    mov al, byte [rsi]  ; Store current 'src' character into AL
    stosb               ; Copy it in 'dst'

    cmp byte [rsi], 0   ; Assess if current 'src' chararacter is null byte
    je .done            ; If so, copy is finished

;   dec rcx             ; Without REP, STOSB doesn't decrement RCX
                        ; But we don't need it anyway

    inc rsi             ; Else, select next 'src' character to copy
                        ; STOSB automatically increments RDI

    jmp .copy           ; Loop

.done:
    leave               ; Epilogue: destroy the stack frame
    ret                 ; RAX contains the 'dst' string address