section .data
    prompt db 'Enter n: '
    prompt_len equ $ - prompt
    msg db 'Factorial: '
    msg_len equ $ - msg
    newline db 10

section .bss
    n resb 2
    result resd 1
    result_str resb 10    ; Buffer for ASCII result

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
    mov edx, esi         ; ESI contains length from int_to_ascii
    int 80h
    ret

; Simplified int_to_ascii procedure
; Input: EAX = integer to convert
; Output: result_str = ASCII representation
;         ESI = length of the string
int_to_ascii:
    mov edi, result_str + 9  ; Start from the end of buffer
    mov byte [edi], 0        ; Null-terminate string
    mov ebx, 10              ; Divisor
    xor esi, esi             ; Counter for string length
    
    ; Handle zero as special case
    test eax, eax
    jnz .convert_loop
    dec edi
    mov byte [edi], '0'      ; Just put '0' for zero
    inc esi
    jmp .done

.convert_loop:
    xor edx, edx             ; Clear EDX for division
    div ebx                  ; Divide EAX by 10, remainder in EDX
    
    ; Convert remainder to ASCII and store
    dec edi                  ; Move pointer backward
    add dl, '0'              ; Convert to ASCII
    mov [edi], dl            ; Store digit
    inc esi                  ; Increment length counter
    
    test eax, eax            ; Check if more digits
    jnz .convert_loop        ; Continue if more digits

.done:
    ; Move the digits to the beginning of result_str if needed
    mov ecx, esi             ; Get length for copying
    mov edx, result_str      ; Destination for copy
    
    ; Check if we need to move the string
    cmp edi, result_str
    je .exit                 ; Skip if already at start
    
    ; Copy the string to the beginning of buffer
.copy_loop:
    mov al, [edi]            ; Get a character
    mov [edx], al            ; Store at destination
    inc edi                  ; Next source byte
    inc edx                  ; Next destination byte
    dec ecx                  ; Decrement counter
    jnz .copy_loop           ; Continue until done
    
.exit:
    ret