section .data
    prompt1 db 'Enter first number (1-9): '
    prompt1_len equ $ - prompt1
    prompt2 db 'Enter second number (1-9): '
    prompt2_len equ $ - prompt2
    
    sum_msg db 'Sum: '
    sum_len equ $ - sum_msg
    diff_msg db 'Difference: '
    diff_len equ $ - diff_msg
    prod_msg db 'Product: '
    prod_len equ $ - prod_msg
    quot_msg db 'Quotient: '
    quot_len equ $ - quot_msg
    rem_msg db 'Remainder: '
    rem_len equ $ - rem_msg
    
    newline db 10

section .bss
    num1 resb 2
    num2 resb 2
    result resb 2

section .text
    global _start

_start:
    ; Get first number
    mov eax, 4
    mov ebx, 1
    mov ecx, prompt1
    mov edx, prompt1_len
    int 80h
    
    mov eax, 3
    mov ebx, 0
    mov ecx, num1
    mov edx, 2
    int 80h
    
    ; Get second number
    mov eax, 4
    mov ebx, 1
    mov ecx, prompt2
    mov edx, prompt2_len
    int 80h
    
    mov eax, 3
    mov ebx, 0
    mov ecx, num2
    mov edx, 2
    int 80h

    ; Convert ASCII to numbers
    movzx eax, byte [num1]    ; Zero-extend to use full register
    sub al, '0'
    movzx ebx, byte [num2]    ; Zero-extend to use full register
    sub bl, '0'
    
    ; Save original numbers
    push eax
    push ebx
    
    ; Addition
    add al, bl
    add al, '0'
    mov [result], al
    
    mov eax, 4
    mov ebx, 1
    mov ecx, sum_msg
    mov edx, sum_len
    int 80h
    
    mov eax, 4
    mov ebx, 1
    mov ecx, result
    mov edx, 1
    int 80h
    
    mov eax, 4
    mov ebx, 1
    mov ecx, newline
    mov edx, 1
    int 80h
    
    ; Restore numbers for subtraction
    pop ebx
    pop eax
    push eax
    push ebx
    
    ; Subtraction
    sub al, bl
    add al, '0'
    mov [result], al
    
    mov eax, 4
    mov ebx, 1
    mov ecx, diff_msg
    mov edx, diff_len
    int 80h
    
    mov eax, 4
    mov ebx, 1
    mov ecx, result
    mov edx, 1
    int 80h
    
    mov eax, 4
    mov ebx, 1
    mov ecx, newline
    mov edx, 1
    int 80h
    
    ; Restore numbers for multiplication
    pop ebx
    pop eax
    push eax
    push ebx
    
    ; Multiplication
    mul bl              ; Result in AX
    add al, '0'
    mov [result], al
    
    mov eax, 4
    mov ebx, 1
    mov ecx, prod_msg
    mov edx, prod_len
    int 80h
    
    mov eax, 4
    mov ebx, 1
    mov ecx, result
    mov edx, 1
    int 80h
    
    mov eax, 4
    mov ebx, 1
    mov ecx, newline
    mov edx, 1
    int 80h
    
    ; Restore numbers for division
    pop ebx
    pop eax
    
    ; Division
    xor edx, edx        ; Clear EDX for division
    div ebx             ; Quotient in EAX, remainder in EDX
    push edx            ; Save remainder
    
    ; Handle quotient
    add al, '0'
    mov [result], al
    
    mov eax, 4
    mov ebx, 1
    mov ecx, quot_msg
    mov edx, quot_len
    int 80h
    
    mov eax, 4
    mov ebx, 1
    mov ecx, result
    mov edx, 1
    int 80h
    
    mov eax, 4
    mov ebx, 1
    mov ecx, newline
    mov edx, 1
    int 80h
    
    ; Handle remainder
    pop eax             ; Get back remainder
    add al, '0'
    mov [result], al
    
    mov eax, 4
    mov ebx, 1
    mov ecx, rem_msg
    mov edx, rem_len
    int 80h
    
    mov eax, 4
    mov ebx, 1
    mov ecx, result
    mov edx, 1
    int 80h
    
    mov eax, 4
    mov ebx, 1
    mov ecx, newline
    mov edx, 1
    int 80h
    
    ; Exit program
    mov eax, 1
    mov ebx, 0
    int 80h