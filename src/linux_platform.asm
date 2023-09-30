bits 64
SECTION .text

; **************************************
; LINUX has many ABI's, but the ones I care about
; (x64 and x32) seem exactly the same
;
; from C:
; - first 6 int/ptr args passed in:
;     RDI, RSI, RDX, RCX, R8, R9
; - Arg 7+ is pushed on the stack
;
; Assembly syscalls on x86-64:
; - args passed in:
;   rax (the opcode)
;   rdi, rsi, rdx, r10, r8, r9
; - syscalls return arg 1 in RAX and 2 in RDX (man syscall)
; **************************************

GLOBAL tok_print
tok_print:
    mov rcx, rdi
    mov rax, 1   ; kernel opcode 4 for SYS_WRITE
    mov rdi, 1   ; write to STDOUT
    mov rdx, rsi ; number of bytes to write
    mov rsi, rcx ; pointer to string
    syscall
    ret


%define PROT_READ 1
%define PROT_WRITE 2
%define PROT_READ_OR_WRITE 3
%define MAP_SHARED 1
%define MAP_PRIVATE 2
%define MAP_ANONYMOUS 32
%define MAP_SHARED_OR_ANON 33
GLOBAL tok_malloc
tok_malloc:
    mov rsi, rdi     ; amount of bytes to malloc
    mov rax, 9       ; opcode 9 for SYS_MMAP
    mov rdi, 0       ; address null, plz choose for me
    mov rdx, PROT_READ_OR_WRITE       
    mov r10, MAP_SHARED_OR_ANON
    mov r8, -1        ; fd is expected to be -1 'on some systems', wtf
    mov r9, 0        ; offset
    syscall          ; return address now in rax
    ret

GLOBAL tok_exit
tok_exit:    
    mov rax, 60 ; opcode 60 for SYS_EXIT
    mov rbx, 0
    syscall
    ret

GLOBAL tok_time
tok_time:
    rdtsc
    shl rdx, 32
    or rax, rdx
    ret

