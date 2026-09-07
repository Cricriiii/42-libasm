;------------------------------------------------------------------------------
; check_duplicated  : Looks for duplicated character
; UPDATED           : 2026-09-07
; RETURNS           : (1) if duplicated is found, (0) otherwise
; MODIFIES          : Nothing
; CALL              : Nothing
; DESCRIPTION       : Scans the string passed in RDI and looks for duplicated
;                   : characters.

SECTION .data       ; Section containing initialized data

    BITSET_SIZE equ 255                      ; Size of the bitset
    Ascii_BitSet: times BITSET_SIZE db 0     ; Declare a 255-bytes wide bitset

SECTION .text       ; Section containing code

global check_duplicated

check_duplicated:
    xor rax, rax            ; Initialize RAX

.next_character:
    cmp byte [rdi], 0   ; Test if string is complete (null character)
    jz .assess          ; If so, no assess duplication

    movzx r9d, byte [rdi]        ; Extend the byte with no sign extend
    lea rax, [Ascii_BitSet+r9d]  ; Load the address of Ascii_BitSet[c] in RAX
    inc byte [rax]               ; Set the character as 'seen once'
    
    lea rsi, [rdi+1]             ; Set the inner loop pointer in RSI

.assess:
    mov rcx, BITSET_SIZE         ; Setting the iteration total number
    
    
.assess_loop:


.true:
    mov al, 1
    ret

.false:
    mov al, 0
    ret