section .data
    prompt db 'Enter n: '
    prompt_len equ $ - prompt
    msg db 'Series: '
    msg_len equ $ - msg
    space db ' '
    newline db 10

section .bss
    n resb 2
    num1 resb 2
    num2 resb 2
    result resb 2

section .text
global _start

_start:
    call write_prompt
    call read_n
    call write_msg
    mov byte [num1], '0'
    mov byte [num2], '1'
    movzx ecx, byte [n]
    sub ecx, '0'
loop:
    push ecx
    call write_num1
    call write_space
    call add_nums
    mov al, [num2]
    mov [num1], al
    mov al, [result]
    mov [num2], al
    pop ecx
    dec ecx
    jnz loop
    call write_newline
    mov eax, 1
    mov ebx, 0
    int 80h

write_prompt:
    mov eax, 4
    mov ebx, 1
    mov ecx, prompt
    mov edx, prompt_len
    int 80h
    ret

read_n:
    mov eax, 3
    mov ebx, 0
    mov ecx, n
    mov edx, 2
    int 80h
    ret

write_msg:
    mov eax, 4
    mov ebx, 1
    mov ecx, msg
    mov edx, msg_len
    int 80h
    ret

write_num1:
    mov eax, 4
    mov ebx, 1
    mov ecx, num1
    mov edx, 1
    int 80h
    ret

write_space:
    mov eax, 4
    mov ebx, 1
    mov ecx, space
    mov edx, 1
    int 80h
    ret

write_newline:
    mov eax, 4
    mov ebx, 1
    mov ecx, newline
    mov edx, 1
    int 80h
    ret

add_nums:
    movzx eax, byte [num1]
    sub al, '0'
    movzx ebx, byte [num2]
    sub bl, '0'
    add eax, ebx
    add al, '0'
    mov [result], al
    ret