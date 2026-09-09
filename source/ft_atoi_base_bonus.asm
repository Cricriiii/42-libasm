;------------------------------------------------------------------------------
;   Executable      : ft_atoi_base_bonus
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
;   Prototype       : int ft_atoi_base_bonus(char *str, char *base);
;
;   Registers       : RDI -> char *str
;                     RSI -> char *base
;------------------------------------------------------------------------------

SECTION .data       ; Section containing uninitialized data
    Result: dd 0    ; int Result = 0;

SECTION .text       ; Section containing code

global ft_atoi_base_bonus ; Make ft_atoi_base_bonus callable from outside

%define SRC_PTR         rbp-0x08
%define BASE_PTR        rbp-0x10
%define BASE_LENGTH     rbp-0x18
%define RESULT          rbp-0x20
%define EXPR_SIGN       rbp-0x28

%macro NUL_BYTE_JMP_RET 1
    mov r10, [%1]
    cmp byte [r10], 0
    jz .set_return_value
%endmacro

ft_atoi_base_bonus:
; Create the stack frame
    push rbp        ; Alignment prologue
    mov rbp, rsp    ; Anchor the base pointer at the stack position
    sub rsp, 0x40   ; Creates a 64 bytes wide stack frame

; Save parameters onto the stack
    mov [SRC_PTR], rdi         ; Create moving pointer to source string
    mov [BASE_PTR], rsi        ; Create moving pointer to base string

; Check if base is valid
    mov rdi, rsi               ; Store base string address in RDI
    call assess_base

    cmp rax, 0                 ; If base is invalid, size is 0
    jz .error

    mov [BASE_LENGTH], rax     ; Store base length value

    mov dword [EXPR_SIGN], 1   ; Initialize sign to 1


; Store ft_atoi_base_bonus result onto the stack
    xor rax, rax                ; Store 0 in AL for STOSD
    lea rdi, [RESULT]           ; Calculate the address of the result
    cld                         ; Set direction flag to up memory
    stosd                       ; Copy 0 on 4 bytes

.skip_whitespaces:
    NUL_BYTE_JMP_RET SRC_PTR

    mov r10, [SRC_PTR]          ; Load the current source address
    movzx edi, byte [r10]       ; Prepare call to ft_isspace
    call ft_isspace

    cmp eax, 1                  ; Check if current character is a whitespace
    jnz .convert_sign           ; If not, start converting
    
    inc [SRC_PTR]               ; Else load next character
    jmp .skip_whitespaces       ; Loop

; Assess the expression sign with regards to the '+' and '-' signs
; Stop at the first character different than '+' or '-'

.convert_sign:
; test_is_plus
    mov r10, [SRC_PTR]          ; Load the current source address
    cmp byte [r10], 0x2b        ; Test if character is '+'
    jnz .test_is_minus          ; If not, continue testing

    inc [SRC_PTR]               ; Else move pointer to the next character
    NUL_BYTE_JMP_RET SRC_PTR

    jmp .convert_sign           ; Loop

.test_is_minus:
    mov r10, [SRC_PTR]          ; Load the current source address
    cmp byte [r10], 0x2d        ; Test if character is '-'
    jnz .conversion             ; If not, start conversion

    neg dword [EXPR_SIGN]       ; Change sign

    inc [SRC_PTR]               ; Else move pointer to the next character
    NUL_BYTE_JMP_RET SRC_PTR

    jmp .convert_sign           ; Loop

; This is the actual string to integer conversion
; Each character if looked up in the base string
; RCX holds the index of the character in the base string
; R8 and R9 hold respectively the current source and compare characters
    xor rcx, rcx                ; Reset the index value

.conversion:
    mov r10, [SRC_PTR]          ; Load the current source address
    movzx r8, byte [r10]        ; Store source character in R8
    
    mov r10, [BASE_PTR]         ; Store base string address in temporary R10
    movzx r9, byte [r10 + rcx]  ; Store current source character in R9

    cmp r8, r9                  ; Compare source and base characters
    jz .calculate               ; Both characters are equal

    inc rcx                     ; Move index to next base character
                                ; We need to check if it reaches the end of the
                                ; base string

    cmp rcx, [BASE_LENGTH]      ; Test if index points to the end
    je .set_return_value        ; If so, last convertible character was found
    jmp .conversion             ; Else, try next base character

.calculate:
    mov eax, [RESULT]           ; Store current result in EAX
    imul eax, [BASE_LENGTH]     ; Multiply result by the base length
    add eax, ecx                ; Add the remainder
    mov [RESULT], eax            ; Store the result value on the stack

    xor rcx, rcx                ; Reset the index value
    inc [SRC_PTR]               ; Else move pointer to the next character
    NUL_BYTE_JMP_RET SRC_PTR
    jmp .conversion             ; Loop with the next source character

.set_return_value:
    mov eax, [RESULT]           ; Set return value
    imul eax, dword [EXPR_SIGN] ; Apply the expression sign

.epilogue:
    leave                       ; Destroy the stack frame
    ret

.error:
    mov rax, 0                  ; Return 0 on error
    jmp .epilogue               ; 


;------------------------------------------------------------------------------
; assess_base       : Assess base validity and return base length
; UPDATED           : 2026-09-08
; RETURNS           : (1) if duplicated is found, (0) otherwise
; MODIFIES          : Nothing
; CALL              : Nothing
; DESCRIPTION       : Scans the string passed and looks for duplicated
;                     or forbidden characters and returns size_t base_length
; PROTOTYPE         : size_t assess_base(const char *base);
; REGISTERS         : RDI -> Base string address
;------------------------------------------------------------------------------

%define INT_SET_SIZ 255

SECTION .text       ; Section containing code

extern ft_strlen    ; Included in /source/
extern ft_isspace   ; Included in /source/common

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
    mov rcx, INT_SET_SIZ    ; Set the number of iterations
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
    mov rcx, INT_SET_SIZ        ; Initialize the loop counter to 255
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