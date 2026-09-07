;   Executable      : ft_atoi_base
;   Version         : 1.0
;   Created date    : 2026-09-05
;   Last update     : 2026-09-07
;   Author          : Christophe Gajean
;   Description     : Assembly implementation of a base-dependant
;                   : alpha to integer conversion procedure.
;                   :
;                   : The procedure converts and returns the integer value
;                   : of the ASCII string parameter 'str' stored in RDI.
;                   : The base length is dictated by the length of the
;                   : char array 'base' stored in RSI.
;
;   Prototype       : int ft_atoi_base(char *str, char *base);
;
;   Registers       : RDI -> char *str
;                     RSI -> char *base
;

SECTION .data       ; Section containing uninitialized data
    Result: dd 0    ; int Result = 0;

    Forbidden: db ""

SECTION .text       ; Section containing code

extern ft_isspace   ; Included in /source/common

global ft_atoi_base ; Make ft_atoi_base callable from outside

ft_atoi_base:
; Create the stack frame
    push rbp        ; Alignment prologue
    mov rbp, rsp    ; Anchor the base pointer at the stack position
    ; sub rsp, 0x20 ; Move RSP 36 bytes away

.check_base:






    mov eax, Result ; Store the int value of the result in EAX

.epilogue:
    leave           ; Destroy the stack frame
    ret

.error:
    mov rax, 0      ; Return 0 on error
    jmp .epilogue   ; 


; ;------------------------------------------------------------------------------
; ; check_duplicated  : Looks for duplicated character
; ; UPDATED           : 2026-09-07
; ; RETURNS           : (1) if duplicated is found, (0) otherwise
; ; MODIFIES          : Nothing
; ; CALL              : Nothing
; ; DESCRIPTION       : Scans the string passed in RDI and looks for duplicated
; ;                   : characters.

; SECTION .data       ; Section containing initialized data
;     Ascii_BitSet: times 255 db 0     ; Declare a 255-bytes wide bitset

; SECTION .text       ; Section containing code

; global check_duplicated

; check_duplicated:
;     cmp byte [rdi], 0   ; Test if string is complete (null character)
;     jz .false           ; If so, no duplicated character has been found

;     lea rsi, [rdi+1]    ; Set the inner loop pointer in RSI

; .inner_loop:
;     cmp byte [rsi], 0   ; Test if the inner loop reached the end of the string
;     jz .next_character  ; If so, move to the next string character

; ; Check if the character has already been encountered
;     lea r9, [Ascii_BitSet+sil]  ; Load the address in the Ascii_BitSet table
;     cmp byte [r9], 1            ; Check if the value has already been found
;     jz .true                    ; If so, duplicate found, return true

;     mov byte [r9], 1            ; Set the character as 'seen once'

;     inc rsi                     ; Step in the inner loop
;     jmp .inner_loop             ; Loop

; .next_character:
;     inc rdi              ; Test the next character
;     jmp check_duplicated ; Loop

; .true:
;     mov rax, 1
;     ret

; .false:
;     mov rax, 0
;     return



