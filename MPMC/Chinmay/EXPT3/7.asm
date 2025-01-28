section .data
msg db 'Multiples of three from 0 to 9:', 10
msgLen equ $-msg
newline db 10
newlineLen equ $-newline

%macro writesystem 2
    push ecx               
    mov eax, 4
    mov ebx, 1
    mov ecx, %1
    mov edx, %2
    int 80h
    pop ecx                
%endmacro

section .bss
output resb 1

section .text
global _start
_start:
    writesystem msg, msgLen

    mov ecx, 0             
print_multiple:
    mov eax, ecx
    add eax, '0'           
    mov [output], al       
    writesystem output, 1 
    writesystem newline, newlineLen 
    add ecx, 3            
    cmp ecx, 10           
    jl print_multiple

    mov eax, 1            
    mov ebx, 0
    int 80h
