section .data
    msg1 db 'Enter the first number: ', 0
    msg1len equ $-msg1
    msg2 db 'Enter the second number: ', 0
    msg2len equ $-msg2
    msg3 db 'The larger number is: ', 0
    msg3len equ $-msg3
    equal_msg db 'Numbers are equal!', 0
    equal_msglen equ $-equal_msg
    newline db 10, 0
    newlinelen equ $-newline
    


section .bss
    num1 resb 4
    num2 resb 4
    result resb 4

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
    
    writesystem msg1, msg1len
    readsystem num1, 4
    writesystem msg2, msg2len
    readsystem num2, 4

    mov eax, [num1]
    mov ebx, [num2]
    cmp eax, ebx
    je numbers_equal   
    jg first_is_larger 
    

    mov eax, ebx
    jmp display_result

numbers_equal:
    writesystem equal_msg, equal_msglen
    writesystem newline, newlinelen
    jmp exit_program

first_is_larger:
    mov eax, [num1]

display_result:
    mov [result], eax
    writesystem msg3, msg3len
    writesystem result, 4
    writesystem newline, newlinelen

exit_program:
    mov eax, 1
    xor ebx, ebx
    int 80h
