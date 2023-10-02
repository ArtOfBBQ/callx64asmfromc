bits 64

; section   .data

section .text

GLOBAL _tok_exit
_tok_exit:
    mov eax, 33554433     ; terminate program
    ; mov eax, 0x2000001  ; same instruction as above
    mov ebx, 0            ; exit code 0
    syscall
    ret

GLOBAL _tok_time
_tok_time:
    or rax, rax
    or rdx, rdx
    rdtscp
    shl rdx, 32
    or rax, rdx
    ret

