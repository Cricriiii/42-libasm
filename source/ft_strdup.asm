;   Executable      : ft_strdup
;   Version         : 1.0
;   Created date    : 2026-09-07
;   Last update     : 2026-09-07
;   Author          : Christophe Gajean
;   Description     : Assembly implementation of man 2 read
;                     based on the libc prototype.
;
;   Prototype       : char *strdup(const char *s);
;
;   Registers       : RDI -> const char *s

SECTION .text       ; Section containing code

extern ft_strlen    ; Included in /source/
extern ft_strcpy    ; Included in /source/
extern set_errno    ; Included in ./source/common
extern malloc       ; Included by <stdlib.h>
                    ; void *malloc(size_t size);
                    ; Returns a pointer to the beginning of
                    ; the allocated memory zone

global ft_strdup    ; Make ft_strdup callable / visible from outside

ft_strdup:
; Create the stack frame
    push rbp        ; Alignment prologue
    mov rbp, rsp    ; Anchor the base pointer at the stack position
    sub rsp, 0x20   ; Move RSP 36 bytes away

; Set aside the source string 's' address
    mov qword [rbp-0x8], rdi    ; Save the address into the stack

; Calculate the string length with ft_strlen
    call ft_strlen  ; Call ft_strlen on the address of string s
                    ; already stored in RDI
                    ; Return value in RAX

; Allocate a new string with malloc
    mov rdi, rax    ; Set malloc 'size' argument to the length of 's'
    inc rdi         ; Make room for the null character (0)
    call malloc wrt ..plt   ; Allocate memory

; Test malloc return value for errors
    cmp rax, 0      ; RAX contains malloc return value
    jz .error       ; Error (RAX=0), null pointer has been returned
                    ; Jump to the error sequence

; Copy the old string data into the new string with ft_strcpy
    mov rdi, rax    ; RAX contains the new string address
    mov rsi, qword [rbp-0x8]     ; RBP-0x8 contains the source string address
    call ft_strcpy  ; Copy source string into destination string
                    ; Returns the destination string address in RAX
                    ; in accordance with System V ABI requirements

.return:
    leave           ; Destroy the stack frame
    ret

.error:
    mov rdi, rax    ; Prepare call of set_errno with raw errno value
    call set_errno  ; Set errno value

    mov rax, 0      ; Store a null pointer in RAX before return
                    ; in accordance with System V ABI requirements
    jmp .return     ; Jump to the return sequence