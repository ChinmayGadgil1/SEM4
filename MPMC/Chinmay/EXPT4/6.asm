section .data
  
    msg1 db 'Enter a number: '
    msg1len equ $-msg1
    even_msg db 'The number is Even', 10
    even_msglen equ $-even_msg
    odd_msg db 'The number is Odd', 10
    odd_msglen equ $-odd_msg
    newline db 10
    newlinelen equ $-newline

section .bss
    num resb 2    ; Reserve 2 bytes for input (number + newline)
    result resb 1

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

section .text
global _start

_start:
    ; Get input from user
    writesystem msg1, msg1len
    readsystem num, 2

    mov al, [num]
    sub al, '0'

    mov ah, 0    
    mov bl, 2    
    div bl      

    cmp ah, 0
    je even_number

odd_number:
    writesystem odd_msg, odd_msglen
    jmp exit

even_number:
    writesystem even_msg, even_msglen

exit:
    mov eax, 1
    xor ebx, ebx
    int 80h
