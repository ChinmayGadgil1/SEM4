section .data
    prompt db 'Enter n: '
    prompt_len equ $ - prompt
    msg db 'Factorial: '
    msg_len equ $ - msg
    newline db 10

section .bss
    n resb 2
    result resd 1

section .text
global _start

_start:
    call write_prompt
    call read_n
    call write_msg
    movzx ecx, byte [n]
    sub ecx, '0'
    mov eax, 1
    call factorial
    call write_result
        call write_newline
        mov eax, 1
        mov ebx, 0
        int 80h
    
    write_newline:
        mov eax, 4
        mov ebx, 1
        mov ecx, newline
        mov edx, 1
        int 80h
        ret

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

factorial:
    cmp ecx, 1
    jle end_factorial
    imul eax, ecx
    dec ecx
    call factorial
end_factorial:
    mov [result], eax
    ret

write_result:
    mov eax, [result]
    sub eax, '0'  ; Convert result to ASCII
    mov [result], eax  ; Store the result back
    mov eax, 4
    mov ebx, 1
    mov ecx, result
    mov edx, 1  ; Assuming result is a single digit
    
    int 80h
    ret
    

