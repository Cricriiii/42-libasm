;------------------------------------------------------------------------------
;   Executable      : ft_list_push_front
;   Version         : 1.0
;   Created date    : 2026-09-09
;   Last update     : 2026-09-09
;   Author          : Christophe Gajean
;   Description     : Adds a new element of type t_list to the beginning of
;                   : the list.
;
;   Prototype       : void ft_list_push_front(t_list **begin_list, void *data);
;
;   Registers       : RDI -> t_list **begin_list
;                     RSI -> void *data
;------------------------------------------------------------------------------

SECTION .text       ; Section containing code

extern malloc       ; Included in <stdlib.h>

global ft_list_push_front

%define BEGIN_LIST_PTR    rbp-0x08
%define DATA_PTR          rbp-0x10
%define NEW_ITEM_PTR      rbp-0x18
%define NEW_ITEM_SIZ      0x10

ft_list_push_front:
; Create the stack frame
  push rbp        ; Alignment prologue
  mov rbp, rsp    ; Anchor the base pointer at the stack position
  sub rsp, 0x20   ; Creates a 32 bytes wide stack frame

; Save parameters onto the stack
  mov [BEGIN_LIST_PTR], rdi     ; push 'begin_list'
  mov [DATA_PTR], rsi           ; push 'data'

; Allocate new item
  mov rdi, NEW_ITEM_SIZ         ; Load 16 bytes into malloc parameter
  call malloc wrt ..plt         ; Allocate

  cmp rax, 0                    ; Test malloc return value
  jz .epilogue                  ; If null pointer is return directly

  mov [NEW_ITEM_PTR], rax       ; Else store the new pointer on the stack

; Fill the new item
  ; 'data' field
  ; add rax, 0x08                 ; Increment address by 8 bytes (total +8 bytes)
  mov r8, [DATA_PTR]            ; Save the 'data' parameter value
  mov [rax], r8                 ; Fill the 'data' field with 'data' parameter value

  ; 'next' field
  add rax, 0x08                 ; Increment address by 8 bytes (total +8 bytes)
  mov r8, [BEGIN_LIST_PTR]      ; Save the 'begin_list' (t_list **) parameter value
  mov r8, [r8]                  ; Save the 'begin list' (t_list *) parameter value
  mov [rax], r8                 ; Fill the 'next' field with 'begin_list' parameter value

; Update the head of the list with the new item address
  mov r8, [BEGIN_LIST_PTR]      ; Save the head list address
  mov r9, [NEW_ITEM_PTR]        ; Save the new item address
  mov [r8], r9                  ; Update the head list address with the new item address

.epilogue:
  leave                         ; Epilogue: destroy the stack frame
  ret