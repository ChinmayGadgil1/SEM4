section .data
    newline db 10
    digit db 0

section .text
global _start
_start:
    mov ecx, 0

print_loop:
    push ecx

    mov eax, ecx
    mov edx, 0
    mov ebx, 3
    div ebx
    
    cmp edx, 0
    jne next_num

    pop ecx
    push ecx
    add ecx, '0'
    mov [digit], cl
    
    mov eax, 4
    mov ebx, 1
    mov ecx, digit
    mov edx, 1
    int 80h
    
    mov eax, 4
    mov ebx, 1
    mov ecx, newline
    mov edx, 1
    int 80h

next_num:
    pop ecx
    inc ecx
    cmp ecx, 10
    jl print_loop

exit:
    mov eax, 1
    mov ebx, 0
    int 80h
