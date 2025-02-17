section .data
    msg1 db 'Enter a number: '
    msg1len equ $-msg1
    
    msg_greater db 'Number is greater than 5', 10
    msg_greater_len equ $-msg_greater
    
    msg_less db 'Number is less than 5', 10
    msg_less_len equ $-msg_less
    
    msg_equal db 'Number is equal to 5', 10
    msg_equal_len equ $-msg_equal

section .bss
    num resb 2       ; For storing input number

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
    
    
    readsystem num, 2
    
 
    mov al, [num]
    sub al, '0'
    
    ; Compare with 5
    cmp al, 5
    je equal        
    jg greater      
    jl less        

greater:
    writesystem msg_greater, msg_greater_len
    jmp exit

less:
    writesystem msg_less, msg_less_len
    jmp exit

equal:
    writesystem msg_equal, msg_equal_len
    jmp exit

exit:
    mov eax, 1
    mov ebx, 0
    int 80h
