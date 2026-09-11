;------------------------------------------------------------------------------
;   Executable      : ft_list_remove_if
;   Version         : 1.0
;   Created date    : 2026-09-10
;   Last update     : 2026-09-10
;   Author          : Christophe Gajean
;   Description     : Sort the list in ascending orders. Uses a bubble sort
;                     implementation. nodes are swapped. This version
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
%define PREV_NODE   rbp-0x28
%define CUR_NODE    rbp-0x30
%define REC_NODE    rbp-0x38

ft_list_remove_if:
; Create the stack frame
  push rbp                  ; Alignment prologue
  mov rbp, rsp              ; Anchor the base pointer at the stack position
  sub rsp, 0x40             ; Creates a 64 bytes wide stack frame

; Save parameters onto the stack
  mov [BEGIN_LIST], rdi     ; Push begin_list
  mov [DATA_REF], rsi       ; Push data_ref
  mov [CMP_FCT], rdx        ; Push cmp
  mov [FREE_FCT], rcx       ; Push free_fct

; Initialize prev_node and cur_node pointers
  mov qword [PREV_NODE], 0  ; prev_node = nullptr
  
  mov r8, [rdi]             ; Dereference t_list **begin_list
  mov [CUR_NODE], r8        ; cur_node = *begin_list

.compare:
; Test if the end of the list is reached
  cmp [CUR_NODE], 0         ; Test if list is empty
  jz .epilogue              ; If so, return

; Compare current node data field to data_ref
  mov rdi, [CUR_NODE]       ; Put &cur_node->data into RDI
  mov rdi, [rdi]            ; Put cur_node->data into RDI
  mov rsi, [DATA_REF]       ; Put data_ref in RSI
  call [CMP_FCT]            ; Call the data compare function

  cmp eax, 0                ; Test the return of the data compare function
  jz .delete                ; If 0, cur_node->data == data_ref: delete

; If cur_node->data != data_ref, simply advance pointers to the next node
  mov r8, [CUR_NODE]        ; Save cur_node in R8
  mov [PREV_NODE], r8       ; prev_node = cur_node

  mov r8, [r8+0x08]         ; Save cur_node->next
  mov [CUR_NODE], r8        ; cur_node = cur_node->next
  
  jmp .compare

; If cur_node->data == data_ref, delete cur_node before advancing pointers
.delete:
;Fetch cur_node->next address
  mov r8, [CUR_NODE]        ; Store the current node pointer address
  mov r8, [r8+0x08]         ; Fetch cur_node->next address

; Assert if deleting the head node or a middle node
  mov r9, [BEGIN_LIST]      ; Save begin_list
  mov r9, [r9]              ; Dereference (*begin_list)
  cmp r9, [CUR_NODE]        ; Test *begin_list == cur_node
  jnz .delete_middle        ; If not equal, delete a middle node
                            ; Else delete the head node

;.delete_head:
  mov r9, [BEGIN_LIST]      ; Store t_list **begin_list address
  mov [r9], r8              ; Do *begin_list = cur_node->next
  jmp .save_recovery_ptr    ; Skip the delete_middle scenario

.delete_middle:
  mov r9, [PREV_NODE]       ; Store the previous node pointer address
  mov [r9+0x08], r8         ; prev_node->next = cur_node->next

; Save the recovery node address
.save_recovery_ptr:
  mov [REC_NODE], r8        ; Do rec_node = cur_next->next

; Delete the current node
  mov rdi, [CUR_NODE]       ; Store the cur_node address
  call [FREE_FCT]           ; Delete cur_node

; Advance pointers
  mov r8, [REC_NODE]        ; Retrieve the restart node address
  mov [CUR_NODE], r8        ; This node becomes the new cur_node

  jmp .compare              ; End of loop, test the next element

.epilogue:
  leave                     ; Epilogue: destroy the stack frame
  ret