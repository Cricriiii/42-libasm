;------------------------------------------------------------------------------
; assess_base       : Assess base validity and return base length
; UPDATED           : 2026-09-08
; RETURNS           : (1) if duplicated is found, (0) otherwise
; MODIFIES          : Nothing
; CALL              : Nothing
; DESCRIPTION       : Scans the string passed in RDI and looks for duplicated
;                     or forbidden characters and returns size_t base_length
; PROTOTYPE         : size_t assess_base(const char *base);
;------------------------------------------------------------------------------

SECTION .data       ; Section containing initialized data

    BITSET_SIZE equ 255                     ; Size of the bitset

SECTION .text       ; Section containing code

extern ft_strlen    ; Included in /source/
extern ft_isspace   ; Included in /source/common

global assess_base  ; Make the function visible from outside

assess_base:
    xor rax, rax    ; Initialize RAX

; Create the stack frame
    push rbp        ; Alignment prologue
    mov rbp, rsp    ; Anchor the base pointer at the stack position
    sub rsp, 0x420  ; Create a 1056 bytes stack frame:
                    ;   Upper 1020 bytes used as 255 integer wide counter
                    ;   for the ASCII table
                    ;   Lower 36 bytes for alignment and local storage

; Save base string address after the ASCII table in the stack    
    mov [rbp-0x404], rdi    ; Located 8 bytes after the end of the table    

; Clear the ASCII table area in the stack - STOSD
    xor rax, rax            ; Store null value to be copied in AL
    lea rdi, [rbp-0x04]     ; Store the address of the first table element
    mov rcx, BITSET_SIZE    ; Set the number of iterations
    std                     ; Set the direction flag to 'down memory'

    rep stosd               ; Fire the copy of 255 '0 values' in the table

    cld                     ; Clear the flag register according to the
                            ; System V ABI requirements

; Calculate base string length
    mov rdi, [rbp-0x404]    ; Retrieve the stacked base string address
    call ft_strlen

    cmp rax, 1              ; Test if base string length > 1
    jna .invalid            ; If not, base is invalid

    mov [rbp-0x40c], rax    ; Save base length on the stack

    mov rdi, [rbp-0x404]    ; Reload base string address from the stack

.next_character:
; Test null character
    cmp byte [rdi], 0   ; Test if string is complete (null character)
    jz .assess          ; If so, assess validity

; Test if whitespace
    mov [rbp-0x414], rdi    ; Save the current character address on the stack
                            ; as RDI is caller-saved
    movzx rdi, byte [rdi]   ; Store the current character as an unsigned int
    call ft_isspace         ; RDI already contains the character address
    cmp eax, 0              ; Test if character is not a space
    jnz .invalid            ; If not, character is space and base string is invalid

    mov rdi, [rbp-0x414]    ; Retrieve current character address from the stack    

; Test '+', '-'
    cmp byte [rdi], 0x2b        ; Test if c == '+'
    jz .invalid                 ; If so, base is invalid

    cmp byte [rdi], 0x2d        ; Test if c == '-'
    jz .invalid                 ; If so, base is invalid

; Increment the current character count
    movzx r9, byte [rdi]       ; Prepare byte value to index Ascii_Bitset
    lea rax, [rbp-0x04]        ; Load the current character address in RAX
    shl r9, 2                  ; Multiply by 4
    sub rax, r9
                                ; Starting from 1st element located at rbp-0x04
                                ; Step is 4 bytes wide (int)
    inc byte [rax]              ; Increment the byte 'seen' count
    
    inc rdi                     ; Increment base string pointer
    jmp .next_character         ; Test next character

; Assess the character count validity
.assess:
    mov rcx, BITSET_SIZE        ; Initialize the loop counter to 255
    dec rcx                     ; Adjust it to 254 for correct maximum offset

.assess_loop:
; Load the current character address in RAX starting from the last element
    mov r9, rcx                 ; Store the counter before multiplication
    shl r9, 2                   ; Multiply counter by 4 
    lea rax, [rbp-0x04]         ; Store the start of the count table in RAX 
    sub rax, r9                 ; Offset the start of the table

    cmp dword [rax], 1          ; Test if character occurrence against 1
    jg .invalid                 ; If  count > 1, duplicated character

    dec rcx                     ; Decrement loop index
    cmp rcx, 0                  ; Check if the loop reached
                                ; the start of the bitset
    jg .assess_loop             ; If not, loop

; The base is valid, return its size
.valid:
    mov rax, [rbp-0x40c]         ; Retrieve the base length from the stack
    leave                        ; Destroy the stack frame
    ret

.invalid:
    mov rax, 0                   ; Invalid base. return (int) 0;
    leave
    ret