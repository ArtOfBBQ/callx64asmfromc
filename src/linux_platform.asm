bits 64
SECTION .text


; **************************************
; LINUX
;
; - first 6 int/ptr args passed in:
;     RDI, RSI, RDX, RCX, R8, R9
; - Arg 7+ is pushed on the stack
; **************************************


; **************************************
; MICROSOFT
; By default, the 1st 4 args are passed by registers
; registers used depend on type and position of arg
; remaining args get pushed to stack, right to left

; - Integer arguments are passed in RCX, RDX, R8 & R9
;   ints have their MSB left, so small ints can be
;   read from the narrow registers
; - Pointers of all types seem to use exactly the same
;   4 registers as int args
; - Float args are psased in XMM0L, XMM1L, XMM2L, XMM3L
; - m128 types, arrays are never passed by immediate
;   value. A pointer is passed to memory allocated by
;   caller. Must be 16 byte aligned
; **************************************

GLOBAL tok_printf
tok_printf:
    mov rcx, rdi ; pointer to string to ecx
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

