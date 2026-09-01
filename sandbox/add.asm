
SECTION .data
    Total dq 0

SECTION .text

global _start

_start:
    mov rsi, rsp            ;store stack pointer address into RSI

    inc rsi                 ;make RSI point to argv
    jz Exit                 ;if argv is NULL, exit

.loop:
    


    mov rdi, [rsi]          ;store value of RSI into RDI
    add [Total], rdi        ;
    sub byte [Total], 48    ;

    inc rsi;
    mov rdi, [rsi];
    add [Total], rdi;
    sub byte [Total], 48;

    mov rax, 1;
    mov rdi, 0;
    sub rsi, 48;
    mov rsi, Total;
    syscall;

    call Exit;

Exit:
    mov rax, 60;
    mov rdi,0;
    syscall;
