section .bss
    num_digits resb 1
    number1 resb 10
    number2 resb 10
    result resb 11

section .data
    prompt1 db "Enter the number of digits: ", 0
    prompt2 db "Enter the first number: ", 0
    prompt3 db "Enter the second number: ", 0
    newline db 10, 0

section .text
    global _start

_start:
    ; Prompt for number of digits
    mov eax, 4
    mov ebx, 1
    mov ecx, prompt1
    mov edx, 24
    int 0x80

    ; Read number of digits
    mov eax, 3
    mov ebx, 0
    mov ecx, num_digits
    mov edx, 1
    int 0x80

    ; Convert num_digits from ASCII to integer
    sub byte [num_digits], '0'

    ; Prompt for the first number
    mov eax, 4
    mov ebx, 1
    mov ecx, prompt2
    mov edx, 21
    int 0x80

    ; Read the first number
    mov eax, 3
    mov ebx, 0
    mov ecx, number1
    mov edx, 10
    int 0x80

    ; Prompt for the second number
    mov eax, 4
    mov ebx, 1
    mov ecx, prompt3
    mov edx, 22
    int 0x80

    ; Read the second number
    mov eax, 3
    mov ebx, 0
    mov ecx, number2
    mov edx, 10
    int 0x80

    ; Convert the first number from ASCII to integer
    mov ecx, num_digits
    mov esi, number1
    xor eax, eax
    xor ebx, ebx
convert1:
    mov bl, [esi]
    sub bl, '0'
    imul eax, eax, 10
    add eax, ebx
    inc esi
    loop convert1
    mov ebx, eax

    ; Convert the second number from ASCII to integer
    mov ecx, num_digits
    mov esi, number2
    xor eax, eax
    xor edx, edx
convert2:
    mov dl, [esi]
    sub dl, '0'
    imul eax, eax, 10
    add eax, edx
    inc esi
    loop convert2

    ; Add the two numbers
    add eax, ebx

    ; Convert the result to ASCII
    mov esi, result + 10
    mov byte [esi], 0
    dec esi
convert_result:
    xor edx, edx
    mov ecx, [num_digits]
    div ecx
    add dl, '0'
    mov [esi], dl
    dec esi
    test eax, eax
    jnz convert_result
    inc esi

    ; Print the result
    mov eax, 4
    mov ebx, 1
    mov ecx, esi
    mov edx, result + 10
    sub edx, esi
    int 0x80

    ; Print newline
    mov eax, 4
    mov ebx, 1
    mov ecx, newline
    mov edx, 1
    int 0x80

    ; Exit
    mov eax, 1
    xor ebx, ebx
    int 0x80