;------------------------------------------------------------------------------
;   Executable      : ft_list_sort
;   Version         : 1.0
;   Created date    : 2026-09-09
;   Last update     : 2026-09-09
;   Author          : Christophe Gajean
;   Description     : Sort the list in ascending orders. Uses a bubble sort
;                     implementation. Elements are swapped. This version
;                     implements a wall system that is decremented by one on
;                     each loop.
;
;   Prototype       : void ft_list_sort(t_list **begin_list, int (*cmp)());
;
;   Registers       : RDI -> t_list **begin_list
;                     RSI -> int (*cmp)())
;------------------------------------------------------------------------------

SECTION .text           ; Section containing code

extern ft_list_size     ; Included in /source/

global ft_list_sort

; Function parameters
%define BEGIN_LIST  rbp-0x08
%define CMP_FN      rbp-0x10
; Indexes
%define MAX_IDX     rbp-0x14
%define CUR_IDX     rbp-0x18
; Sorting pointers
%define PREV_ELEM   rbp-0x20
%define CUR_ELEM    rbp-0x28
%define NEXT_ELEM   rbp-0x30

ft_list_sort:
; Create the stack frame
  push rbp        ; Alignment prologue
  mov rbp, rsp    ; Anchor the base pointer at the stack position
  sub rsp, 0x40   ; Creates a 48 bytes wide stack frame

; Save parameters onto the stack
  mov [BEGIN_LIST], rdi     ; Push begin_list
  mov [CMP_FN], rsi         ; Push data

; Get the list size to initialize the wall / max index value
  mov rdi, [rdi]            ; Store list start
  call ft_list_size         ; Get list size

  cmp eax, 1                ; If size < 2
  jbe .epilogue             ; If so, return
  mov [MAX_IDX], eax        ; Else save the size on the stack
  dec dword [MAX_IDX]       ; Adjust the number of comparison to be made
                            ; Ex: 4 elements means 3 comparisons maximum

; Initialize prev_elem, cur_elem and next_elem
.reset_pointers:
  mov qword [PREV_ELEM], 0  ; Previous pointer is null

  mov r8, [BEGIN_LIST]      ; The first element of the list
  mov r8, [r8]              ; Dereference the t_list** pointer
  mov [CUR_ELEM], r8        ; goes in CUR_ELEM

  mov r8, [r8+0x08]         ; The second element of the list
  mov [NEXT_ELEM], r8       ; goes into NEXT_ELEM

  mov dword [CUR_IDX], 1    ; Initialize the current index

.assess_completion:
; Test comparison index against number of expected comparisons
  mov r8d, [CUR_IDX]        ; Save current index
  cmp r8d, dword [MAX_IDX]  ; Compare current and max indexes

  jle .compare              ; Last comparison not done

  dec dword [MAX_IDX]       ; Last comparison done
                            ; Move the wall backwards
  
  cmp dword [MAX_IDX], 0    ; Test if all comparisons are done
  jz .epilogue              ; If so, return
  jmp .reset_pointers         ; Else start over

.compare:  
; Compare cur_elem, next_elem
  mov rdi, [CUR_ELEM]       ; Pointer to structure
  mov rdi, [rdi]            ; Dereference to get first 8 bytes (data field)
  mov rsi, [NEXT_ELEM]      ; Pointer to structure
  mov rsi, [rsi]            ; Dereference to get first 8 bytes (data field)
  call [CMP_FN]             ; Call the comparison function

  cmp eax, 0                ; Compare cur_elem and next_elem
  jg .swap                  ; cur_elem is greater than next_elem

.advance_pointers:
  inc dword [CUR_IDX]       ; Increment current comparison index

; Advance prev_elem pointer
  mov r8, [CUR_ELEM]        ; Prepare prev_elem = cur_elem
  mov [PREV_ELEM], r8       ; prev_elem = cur_elem

; Advance cur_elem pointer
  mov r8, [NEXT_ELEM]       ; Prepare cur_elem = next_elem
  mov [CUR_ELEM], r8        ; cur_elem = next_elem

; Advance next_elem pointer
  add r8, 0x08              ; Reach the next_elem 'next' field addres
  mov r8, [r8]              ; Store its value in r8
  mov [NEXT_ELEM], r8       ; next_elem = next_elem->next

  jmp .assess_completion    ; Loop

.swap:
; cur_elem->next = next_elem->next
  mov r8, [CUR_ELEM]        ; Retrieve 'cur_elem' t_list* address
  add r8, 0x08              ; Retrieve 'cur_elem->next' field address (not its value)

  mov r9, [NEXT_ELEM]       ; Retrieve 'next_elem' t_list* address
  add r9, 0x08              ; Compute address of 'next_elem->next' field (&next_elem->next)
  mov r9, [r9]              ; Dereference: r9 now holds the value of 'next_elem->next'

  mov [r8], r9              ; cur_elem->next = next_elem->next

; next_elem->next = cur_elem
  mov r8, [NEXT_ELEM]       ; Retrieve 'next_elem' t_list* address
  add r8, 0x08              ; Compute address of 'next_elem->next' field (&next_elem->next)
  
  mov r9, [CUR_ELEM]        ; Retrieve 'cur_elem' t_list* address

  mov [r8], r9              ; next_elem->next = cur_elem
                            ; next_elem->next is inherited from previous step

; Then, two cases, either swapping head or any swapping middle element
  cmp dword [CUR_IDX], 1    ; Test if cur_index == 0
  jz .swap_head             ; If so, swap head of list

.swap_others:
; prev_elem->next = next_elem
  mov r8, [PREV_ELEM]       ; Retrieve 'prev_elem' t_list* address
  add r8, 0x08              ; Compute address of 'prev_elem->next' field (&prev_elem->next)
  
  mov r9, [NEXT_ELEM]       ; Retrieve 'next_elem' t_list* address
  mov [r8], r9              ; prev_elem->next = next
  
  jmp .advance_pointers     ; Move on to the next elements

; Swap head of list
.swap_head:
; *begin_list = next_elem
  mov r8, [BEGIN_LIST]      ; Retrieve 't_list **begin_list' address
  mov r9, [NEXT_ELEM]       ; Retrieve 'next_elem' t_list* address
  mov [r8], r9      ; *begin_list = next_elem

  jmp .advance_pointers     ; Move on to the next elements

.epilogue
  leave           ; Destroy the stack frame
  ret