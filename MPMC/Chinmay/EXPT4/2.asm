section .data
    msg1 db 'Enter the first number: '
    msg1len equ $-msg1
    msg2 db 'Enter the second number: '
    msg2len equ $-msg2
    msg3 db 'Enter the third number: '
    msg3len equ $-msg3
    msg4 db 'The largest number is: '
    msg4len equ $-msg4
    equal_msg db 'All numbers are equal!', 10
    equal_msglen equ $-equal_msg
    newline db 10
    newlinelen equ $-newline

section .bss
    num1 resb 2
    num2 resb 2
    num3 resb 2
    largest resb 2

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
    readsystem num1, 2
    
    writesystem msg2, msg2len
    readsystem num2, 2
    
    writesystem msg3, msg3len
    readsystem num3, 2

    mov al, [num1]   
    sub al, '0'       
    
    mov bl, [num2]    
    sub bl, '0'       
    
    cmp al, bl
    jne compare_numbers   
    
    mov cl, [num3]
    sub cl, '0'
    
    cmp al, cl
    jne compare_numbers   
    
    writesystem equal_msg, equal_msglen
    jmp exit

compare_numbers:
    mov al, [num1]   
    sub al, '0'       
    
    mov bl, [num2]    
    sub bl, '0'       
    
    cmp al, bl
    jge compare_third 
    mov al, bl        

compare_third:
    mov bl, [num3]    
    sub bl, '0'      
    
    cmp al, bl
    jge print_result  
    mov al, bl        

print_result:
    add al, '0'       
    mov [largest], al


    writesystem msg4, msg4len
    writesystem largest, 1
    writesystem newline, newlinelen

exit:

    mov eax, 1
    mov ebx, 0
    int 80h
