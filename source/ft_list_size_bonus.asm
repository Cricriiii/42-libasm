;------------------------------------------------------------------------------
;   Executable      : ft_list_size
;   Version         : 1.0
;   Created date    : 2026-09-09
;   Last update     : 2026-09-11
;   Author          : Christophe Gajean
;   Description     : Calculate the length of the list.
;
;   Prototype       : unsigned int ft_list_size(t_list *begin_list);
;
;   Registers       : RDI -> t_list *begin_list
;------------------------------------------------------------------------------

SECTION .text           ; Section containing code

global ft_list_size     ; Make the function callable / visible from outside

ft_list_size:
; Initialize
    xor eax, eax        ; Initialize the counter
    mov rsi, rdi        ; Create a copy pointer of the list beginning

.count:
    cmp rsi, 0          ; Check if element is null
    jz .end             ; Return

    inc eax             ; Increase counter
    mov rsi, [rsi+0x08] ; RSI = RSI->next
    jmp .count          ; Loop

.end:
    ret