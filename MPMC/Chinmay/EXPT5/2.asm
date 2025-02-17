section .data
    prompt db 'Enter two numbers: '
    plen equ $ - prompt
    msg db 'Entered numbers are: '
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
    num1 resb 5
    num2 resb 5

section .text
    global _start

_start:
    writesystem prompt,plen
    readsystem num1,5
	readsystem num2,5
    writesystem msg,mlen
 	writesystem num1,5
	writesystem num2,5
    mov eax, 1
    xor ebx, ebx
    int 0x80
