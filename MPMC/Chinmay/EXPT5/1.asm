section .data
    msg db 'Your number is: '
    mlen equ $ - msg
    num db '5', 0xA  

%macro writesystem 2
    mov eax, 4
    mov ebx, 1
    mov ecx, %1
    mov edx, %2
    int 80h
%endmacro

section .text
    global _start

_start:
    writesystem msg, mlen
    writesystem num, 2  
    mov eax, 1
    xor ebx, ebx
    int 0x80
