section .bss
    num resb 10
    str resb 100

section .data
    prompt_num db "Enter a number: ", 0
    prompt_str db "Enter a string: ", 0
    output_num db "You entered the number: ", 0
    output_str db "You entered the string: ", 0
    newline db 10, 0

section .text
    global _start

_start:
    mov eax, 4
    mov ebx, 1
    mov ecx, prompt_num
    mov edx, 16
    int 0x80

    mov eax, 3
    mov ebx, 0
    mov ecx, num
    mov edx, 9
    int 0x80
    mov byte [num + eax], 0

    mov eax, 4
    mov ebx, 1
    mov ecx, prompt_str
    mov edx, 16
    int 0x80

    mov eax, 3
    mov ebx, 0
    mov ecx, str
    mov edx, 99
    int 0x80
    mov byte [str + eax], 0

    mov eax, 4
    mov ebx, 1
    mov ecx, output_num
    mov edx, 23
    int 0x80

    mov eax, 4
    mov ebx, 1
    mov ecx, num
    mov edx, 10
    int 0x80

    mov eax, 4
    mov ebx, 1
    mov ecx, newline
    mov edx, 1
    int 0x80

    mov eax, 4
    mov ebx, 1
    mov ecx, output_str
    mov edx, 23
    int 0x80

    mov eax, 4
    mov ebx, 1
    mov ecx, str
    mov edx, 100
    int 0x80

    mov eax, 1
    mov ebx, 0
    int 0x80
