bits 64

; section   .data

section .text

GLOBAL _tok_printf
_tok_printf:
    mov eax, 33554436     ; write to stdout
    mov r8,  rdi          ; stash rdi which we're about to overwrite
    mov edi, 1            ; STDOUT file descriptor is 1
    mov rdx, rsi          ; the size of the value to print goes in rdx
    mov rsi, r8           ; The poiner to string to print goes in rsi
    syscall
    ret

GLOBAL _tok_exit
_tok_exit:
    mov eax, 33554433     ; terminate program
    ; mov eax, 0x2000001  ; same instruction as above
    mov ebx, 0            ; exit code 0
    syscall

