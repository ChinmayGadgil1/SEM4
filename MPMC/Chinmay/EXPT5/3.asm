section .data
    prompt db 'Enter a number: '
    plen equ $ - prompt
    msg db 'Your number is: '
    mlen equ $ - msg

%macro writesystem 2
    mov eax, 4
    mov ebx, 1
    mov ecx, %1
    mov edx, %2
    int 80h
%endmacro

%macro readsystem 2
    mov eax, 3
    mov ebx, 0
    mov ecx, %1
    mov edx, %2
    int 80h
%endmacro

section .bss
    num resb 5

section .text
    global _start

_start:
    writesystem prompt,plen
    readsystem num,5

    writesystem msg,mlen
 	writesystem num,5

    mov eax, 1
    xor ebx, ebx
    int 0x80
