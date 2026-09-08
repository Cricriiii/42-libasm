;   Executable      : ft_isspace
;   Version         : 1.0
;   Created date    : 2026-09-07
;   Last update     : 2026-09-07
;   Author          : Christophe Gajean
;   Description     : Assembly implementation of man 3 isspace
;                     based on the libc prototype.
;
;   Prototype       : int isspace(int c);
;
;   Registers       : RDI -> int c


SECTION .text       ; Section containing code

global ft_isspace

ft_isspace:
    xor rax, rax            ; Reset RAX

; Test EOF
    cmp edi, -1             ; Test if 'c' is EOF
    jz .false               ; If so, return false


; Test space ' '
    cmp edi, 0x20
    jz .true


; Test if '\t', '\n', '\v', '\f', '\r'
; Values range from 0x09 to 0x0D
    cmp edi, 0x09           ; Test if character is greater or equal '\t'
    jl .false               ; If not, return false

    cmp edi, 0x0D           ; Test if character is lesser or equal '\r'
    jg .false               ; If not, return false

                            ; Else, return true
.true:
    mov eax, 1              ; Set return value to true
    ret

.false:
    mov eax, 0              ; Set return value to false
    ret