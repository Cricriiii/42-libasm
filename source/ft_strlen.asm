;   Executable      : ft_strlen
;   Version         : 1.0
;   Created date    : 2026-08-30
;   Last update     : 2026-08-30
;   Author          : Christophe Gajean
;   Description     : Assembly implementation of man 3 strlen
;

ft_strlen:
    xor rax, rax

.loop
    cmp 
    je .done        ; NULL character encountered, end of string
    

.done
    ret             ; Return to caller
