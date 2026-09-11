;------------------------------------------------------------------------------
;   Executable      : ft_list_sort
;   Version         : 1.0
;   Created date    : 2026-09-09
;   Last update     : 2026-09-10
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
%define CMP_FCT     rbp-0x10
; Indexes
%define MAX_IDX     rbp-0x14
%define CUR_IDX     rbp-0x18
; Sorting pointers
%define PREV_NODE   rbp-0x20
%define CUR_NODE    rbp-0x28
%define NEXT_NODE   rbp-0x30
%define F_SORTED    rbp-0x31

ft_list_sort:
; Create the stack frame
  push rbp        ; Alignment prologue
  mov rbp, rsp    ; Anchor the base pointer at the stack position
  sub rsp, 0x40   ; Creates a 64 bytes wide stack frame

; Save parameters onto the stack
  mov [BEGIN_LIST], rdi     ; Push begin_list
  mov [CMP_FCT], rsi        ; Push data

; Get the list size to initialize the wall / max index value
  mov rdi, [rdi]            ; Store list start
  call ft_list_size         ; Get list size

  cmp eax, 1                ; If size < 2
  jbe .epilogue             ; If so, return
  mov [MAX_IDX], eax        ; Else save the size on the stack
  dec dword [MAX_IDX]       ; Adjust the number of comparison to be made
                            ; Ex: 4 nodeents means 3 comparisons maximum

; Initialize prev_node, cur_node, next_node and cur_index
.reset_pointers:
  mov qword [PREV_NODE], 0  ; Previous pointer is null

  mov r8, [BEGIN_LIST]      ; The first nodeent of the list
  mov r8, [r8]              ; Dereference the t_list** pointer
  mov [CUR_NODE], r8        ; goes in CUR_NODE

  mov r8, [r8+0x08]         ; The second nodeent of the list
  mov [NEXT_NODE], r8       ; goes into NEXT_NODE

  mov dword [CUR_IDX], 1    ; Initialize the current index

  mov byte [F_SORTED], 1    ; Reset the sorted flag

.assess_completion:
; Test comparison index against number of expected comparisons
  mov r8d, [CUR_IDX]        ; Save current index
  cmp r8d, dword [MAX_IDX]  ; Compare current and max indexes

  jle .compare              ; Last comparison not done

  dec dword [MAX_IDX]       ; Last comparison done
                            ; Move the wall backwards
  
  cmp dword [MAX_IDX], 0    ; Test if all comparisons are done
  jz .epilogue              ; If so, return

; If no swap occurred, F_SORTED flag value is still one
  cmp byte [F_SORTED], 1    ; Test if list sorted
  je .epilogue              ; If so, return  

  jmp .reset_pointers       ; Else start over

.compare:  
; Compare cur_node, next_node
  mov rdi, [CUR_NODE]       ; Pointer to structure
  mov rdi, [rdi]            ; Dereference to get first 8 bytes (data field)
  mov rsi, [NEXT_NODE]      ; Pointer to structure
  mov rsi, [rsi]            ; Dereference to get first 8 bytes (data field)
  call [CMP_FCT]            ; Call the comparison function

  cmp eax, 0                ; Compare cur_node and next_node
  jg .swap                  ; cur_node is greater than next_node

.advance_pointers_no_swap:
; Advance prev_node pointer
  mov r8, [CUR_NODE]        ; Prepare prev_node = cur_node
  mov [PREV_NODE], r8       ; prev_node = cur_node

; Advance cur_node pointer
  mov r8, [NEXT_NODE]       ; Prepare cur_node = next_node
  mov [CUR_NODE], r8        ; cur_node = next_node

; Advance next_node pointer
  add r8, 0x08              ; Reach the next_node 'next' field addres
  mov r8, [r8]              ; Store its value in r8
  mov [NEXT_NODE], r8       ; next_node = next_node->next

  inc dword [CUR_IDX]       ; Increment current comparison index

  jmp .assess_completion    ; Loop

.advance_pointers_swap:
; Advance prev_node pointer
  mov r8, [NEXT_NODE]       ; Prepare prev_node = old next_node
  mov [PREV_NODE], r8       ; prev_node = old next_node

; cur_node remains the old cur_node
  mov r8, [CUR_NODE]        ; Retrieve cur_node

; Advance next_node pointer from the current nodeent
  add r8, 0x08              ; Reach the cur_node 'next' field address
  mov r8, [r8]              ; Store its value in r8
  mov [NEXT_NODE], r8       ; next_node = next_node->next

  inc dword [CUR_IDX]       ; Increment current comparison index

  jmp .assess_completion    ; Loop  

.swap:
  mov byte [F_SORTED], 0    ; Swap needed, list is not sorted

; cur_node->next = next_node->next
  mov r8, [CUR_NODE]        ; Retrieve 'cur_node' t_list* address
  add r8, 0x08              ; Retrieve 'cur_node->next' field address (not its value)

  mov r9, [NEXT_NODE]       ; Retrieve 'next_node' t_list* address
  add r9, 0x08              ; Compute address of 'next_node->next' field (&next_node->next)
  mov r9, [r9]              ; Dereference: r9 now holds the value of 'next_node->next'

  mov [r8], r9              ; cur_node->next = next_node->next

; next_node->next = cur_node
  mov r8, [NEXT_NODE]       ; Retrieve 'next_node' t_list* address
  add r8, 0x08              ; Compute address of 'next_node->next' field (&next_node->next)
  
  mov r9, [CUR_NODE]        ; Retrieve 'cur_node' t_list* address

  mov [r8], r9              ; next_node->next = cur_node
                            ; next_node->next is inherited from previous step

; Then, two cases, either swapping head or any swapping middle nodeent
  cmp dword [CUR_IDX], 1    ; Test if cur_index == 0
  jz .swap_head             ; If so, swap head of list

.swap_others:
; prev_node->next = next_node
  mov r8, [PREV_NODE]       ; Retrieve 'prev_node' t_list* address
  add r8, 0x08              ; Compute address of 'prev_node->next' field (&prev_node->next)
  
  mov r9, [NEXT_NODE]       ; Retrieve 'next_node' t_list* address
  mov [r8], r9              ; prev_node->next = next
  
  jmp .advance_pointers_swap     ; Move on to the next nodeents

; Swap head of list
.swap_head:
; *begin_list = next_node
  mov r8, [BEGIN_LIST]      ; Retrieve 't_list **begin_list' address
  mov r9, [NEXT_NODE]       ; Retrieve 'next_node' t_list* address
  mov [r8], r9      ; *begin_list = next_node

  jmp .advance_pointers_swap     ; Move on to the next nodeents

.epilogue:
  leave                     ; Destroy the stack frame
  ret