;   Executable      : ft_strcpy
;   Version         : 1.0
;   Created date    : 2026-09-05
;   Last update     : 2026-09-05
;   Author          : Christophe Gajean
;   Description     : Assembly implementation of man 3 strcpy
;                     based on the libc prototype.

;   Prototype       : char *strcpy(char *restrict dst, 
;                                    const char *restrict src);

;   Registers       : RDI -> char *restrict dst
;                     RSI -> const char *restrict src


SECTION .text

global ft_strcpy    ; Make ft_strcopy callable / visible from outside


ft_strcpy:
    xor rax, rax    ; Initializing the RAX register for imminent use
;    mov rcx, -1    ; Not setting the RCX counter as strcpy only stops
                    ; at the first null bytes in src
    mov rdx, rdi    ; Saving dst string address as return value

.copy:
    mov al, byte [rsi]  ; Storing current src character into AL
    stosb               ; Storing character into current dst byte
    cmp byte [rsi], 0   ; Compare current src byte with null character
    je .done            ; If current src byte is null character, done.
;    dec rcx            ; See comment above about RDC
    inc rsi             ; Selecting next source character
    jmp .copy           ; Loop

.done:
    mov rax, rdx        ; Store destination pointer in RAX in accordance to
                        ; System V ABI requirements
    ret                 ; Return