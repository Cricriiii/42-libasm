;------------------------------------------------------------------------------
;   Executable      : ft_strdup
;   Version         : 1.0
;   Created date    : 2026-09-07
;   Last update     : 2026-09-11
;   Author          : Christophe Gajean
;   Description     : Assembly implementation of man 2 read
;                     based on the libc prototype.
;
;   Prototype       : char *strdup(const char *s);
;
;   Registers       : RDI -> const char *s
;------------------------------------------------------------------------------

SECTION .text       ; Section containing code

extern ft_strlen    ; Included in /source/
extern ft_strcpy    ; Included in /source/
extern set_errno    ; Included in ./source/common
extern malloc       ; Included by <stdlib.h>
                    ; void *malloc(size_t size);
                    ; Returns a pointer to the beginning of
                    ; the allocated memory zone

global ft_strdup    ; Make the function callable / visible from outside

%define SRC_STR rbp-0x08

ft_strdup:
; Create the stack frame
    push rbp        ; Alignment prologue
    mov rbp, rsp    ; Anchor the base pointer at the stack position
    sub rsp, 0x20   ; Creates a 32 bytes wide stack frame

; Set aside the source string 's' address
    mov [SRC_STR], rdi    ; Save 's' parameter onto the stack

; Calculate the string length
    call ft_strlen  ; Call ft_strlen on the address of string 's'
                    ; already stored in RDI

; Allocate a new string with malloc
    mov rdi, rax    ; Set malloc 'size' argument to the length of 's'
    inc rdi         ; Make room for the null character (0)
    call malloc wrt ..plt   ; Allocate memory

    cmp rax, 0      ; Test malloc return value
    jz .error       ; If RAX=0, null pointer has been returned
                    ; Jump to the error sequence

; Copy source string into new string
    mov rdi, rax        ; Set new string as destination string
    mov rsi, [SRC_STR]  ; Set source string as source string
    call ft_strcpy      ; Copy source string into destination string
                        ; RAX now contains the new string address

.epilogue:
    leave               ; Epilogue: destroy the stack frame
    ret

.error:
    mov rdi, rax    ; Put the errno value as returned by the syscall
    call set_errno  ; Set errno

    mov rax, 0      ; ft_strdup will return a null pointer
    jmp .epilogue   ; Jump to the return sequence