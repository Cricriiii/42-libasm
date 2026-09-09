;------------------------------------------------------------------------------
;   Executable      : ft_list_size
;   Version         : 1.0
;   Created date    : 2026-09-09
;   Last update     : 2026-09-09
;   Author          : Christophe Gajean
;   Description     : Adds a new element of type t_list to the beginning of
;                   : the list.
;
;   Prototype       : unsigned int ft_list_size(t_list *begin_list);
;
;   Registers       : RDI -> t_list *begin_list
;------------------------------------------------------------------------------

SECTION .text       ; Section containing code

global ft_list_size

ft_list_size:
; Create the stack frame
  push rbp        ; Alignment prologue
  mov rbp, rsp    ; Anchor the base pointer at the stack position

; Initialize
  xor eax, eax    ; Initialize the counter
  mov rsi, rdi    ; Create a copy pointer of the list beginning

.count:
  cmp rsi, 0      ; Check if element is null
  jz .prologue    ; Return

  inc eax             ; Increase counter
  mov rsi, [rsi+0x08] ; RSI = RSI->next
  jmp .count          ; Loop

.prologue:
  leave           ; Destroy the stack frame
  ret