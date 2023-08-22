bits 64
SECTION .text

; **************************************
; LINUX
;
; - first 6 int/ptr args passed in:
;     RDI, RSI, RDX, RCX, R8, R9
; - Arg 7+ is pushed on the stack
; **************************************

GLOBAL tok_print
tok_print:
    mov rcx, rdi
    mov eax, 4   ; kernel opcode 4 for SYS_WRITE
    mov ebx, 1   ; write to STDOUT
    mov rdx, rsi ; number of bytes to write
    int 80h
    ret

GLOBAL tok_exit
tok_exit:    
    mov eax,1 ; kernel opcode 1 for SYS_EXIT
    mov ebx,0
    int 80h

GLOBAL tok_time
tok_time:
    rdtsc
    shl rdx, 32
    or rax, rdx
    ret

