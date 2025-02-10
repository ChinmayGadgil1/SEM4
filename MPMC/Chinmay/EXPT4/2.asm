section .data
    msg1 db 'Enter the first number: '
    msg1len equ $-msg1
    msg2 db 'Enter the second number: '
    msg2len equ $-msg2
    msg3 db 'Enter the third number: '
    msg3len equ $-msg3
    msg4 db 'The largest number is: '
    msg4len equ $-msg4
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

    mov al, [num1]    ; Load first number
    sub al, '0'       ; Convert to number
    
    mov bl, [num2]    ; Load second number
    sub bl, '0'       ; Convert to number
    
    cmp al, bl
    jge compare_third ; If first >= second, keep first
    mov al, bl        ; If second > first, keep second

compare_third:
    mov bl, [num3]    ; Load third number
    sub bl, '0'       ; Convert to number
    
    cmp al, bl
    jge print_result  ; If larger >= third, keep larger
    mov al, bl        ; If third is larger, keep third

print_result:
    add al, '0'       ; Convert back to ASCII
    mov [largest], al ; Store result

    ; Display result
    writesystem msg4, msg4len
    writesystem largest, 1
    writesystem newline, newlinelen

exit:
    mov eax, 1
    mov ebx, 0
    int 80h
