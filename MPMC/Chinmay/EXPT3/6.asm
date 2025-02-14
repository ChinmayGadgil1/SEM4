section .data
    newline db 10

section .bss
    digit resb 1

section .text
    global _start

_start:
    mov byte [digit], 0

print_loop:
    cmp byte [digit], 10
    jge exit_program

    mov al, [digit]
    mov ah, 0
    mov bl, 2
    div bl

    cmp ah, 1
    jne continue

    mov al, [digit]
    add al, '0'
    mov [digit+1], al
    
    mov eax, 4
    mov ebx, 1
    mov ecx, digit+1
    mov edx, 1
    int 80h

    mov eax, 4
    mov ebx, 1
    mov ecx, newline
    mov edx, 1
    int 80h

continue:
    inc byte [digit]
    jmp print_loop

exit_program:
    mov eax, 1
    mov ebx, 0
    int 80h
