;------------------------------------------------------------------------------
;   Executable      : ft_isspace
;   Version         : 1.0
;   Created date    : 2026-09-07
;   Last update     : 2026-09-11
;   Author          : Christophe Gajean
;   Description     : Assembly implementation of man 3 isspace
;                     based on the libc prototype.
;
;   Prototype       : int isspace(int c);
;
;   Registers       : EDI -> int c
;------------------------------------------------------------------------------

SECTION .text       ; Section containing code

global ft_isspace   ; Make the function callable / visible from outside

ft_isspace:
    push rbp        ; Alignment prologue
    mov rbp, rsp    ; Anchor the base pointer at the stack position

; Start testing
    cmp edi, -1     ; (c == EOF) ?
    jz .false       ; If so, false

    cmp edi, 0x20   ; (c == ' ') ?
    jz .true        ; If so, true

    cmp edi, 0x09   ; (c >= '\t') ?
    jl .false       ; If not, false

    cmp edi, 0x0D   ; (c <= '\r') ?
    jg .false       ; If not, false

                    ; Else, true
.true:
    mov eax, 1      ; Set return value to true
    leave           ; Epilogue: destroy the stack frame
    ret

.false:
    mov eax, 0      ; Set return value to false
    leave           ; Epilogue: destroy the stack frame
    ret