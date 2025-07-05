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
    call int_to_ascii
    mov eax, 4
    mov ebx, 1
    mov ecx, result_str
    mov edx, result_len
    int 80h
    ret

int_to_ascii:
    ; Handle special case for 0
    test eax, eax
    jnz .not_zero
    
    ; If the value is 0, just output "0"
    mov byte [result_str], '0'
    mov ecx, result_str
    mov edx, 1
    ret

.not_zero:
    ; Initialize: Point to the end of the buffer for reverse writing
    mov edi, result_str
    xor ecx, ecx          ; Counter for number of digits
    mov ebx, 10           ; Divisor for conversion

.convert_loop:
    ; Extract digits one by one
    xor edx, edx          ; Clear EDX for division
    div ebx               ; Divide EAX by 10, remainder in EDX
    add dl, '0'           ; Convert remainder to ASCII
    
    ; Store digit and update counter
    push edx              ; Save the digit
    inc ecx               ; Increment digit counter
    
    ; Continue until no digits left
    test eax, eax
    jnz .convert_loop
    
    ; Now ECX contains the number of digits
    mov edx, ecx          ; Save length for return

.write_loop:
    ; Write digits in correct order
    pop eax               ; Get digit (in reverse order)
    mov [edi], al         ; Store in buffer
    inc edi               ; Move to next position
    loop .write_loop      ; Repeat for all digits
    
    mov ecx, result_str   ; Point to beginning of result
    ret

section .data
result_str db '0000000000'
result_len equ 10