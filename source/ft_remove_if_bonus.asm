;------------------------------------------------------------------------------
;   Executable      : ft_list_remove_if
;   Version         : 1.0
;   Created date    : 2026-09-10
;   Last update     : 2026-09-10
;   Author          : Christophe Gajean
;   Description     : Sort the list in ascending orders. Uses a bubble sort
;                     implementation. Elements are swapped. This version
;                     implements a wall system that is decremented by one on
;                     each loop.
;
;   Prototype       : void ft_list_remove_if(t_list **begin_list,
;                                            void *data_ref,
;                                            int (*cmp)(),
;                                            void (*free_fct)(void *));
;
;   Registers       : RDI -> t_list **begin_list
;                     RSI -> void *data_ref
;                     RDX -> int (*cmp)()
;                     RCX -> void (*free_fct)(void *)
;------------------------------------------------------------------------------

SECTION .text           ; Section containing code

global ft_list_remove_if

; Function parameters
%define BEGIN_LIST  rbp-0x08
%define DATA_REF    rbp-0x10
%define CMP_FCT     rbp-0x18
%define FREE_FCT    rbp-0x20
; Sorting pointers
%define PREV_ELEM   rbp-0x28
%define CUR_ELEM    rbp-0x30

ft_list_remove_if:
; Create the stack frame
  push rbp        ; Alignment prologue
  mov rbp, rsp    ; Anchor the base pointer at the stack position
  sub rsp, 0x40   ; Creates a 64 bytes wide stack frame

; Save parameters onto the stack
  mov [BEGIN_LIST], rdi     ; Push begin_list
  mov [DATA_REF], rdi       ; Push data_ref
  mov [CMP_FCT], rdx        ; Push cmp
  mov [FREE_FCT], rcx       ; Push free_fct

; Start
