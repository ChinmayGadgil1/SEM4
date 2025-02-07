section .data
    prompt db 'Enter number to search: '
    prompt_len equ $-prompt
    
    found_msg db 'Number found at position: '
    found_len equ $-found_msg
    
    not_found_msg db 'Number not found in array', 10
    not_found_len equ $-not_found_msg
    
    array db 5, 2, 8, 1, 9, 3, 7, 4, 6, 0    
    array_len equ $-array
    
    newline db 10, 0
    
section .bss
    search_num resb 2        
    digit_space resb 8       
    digit_space_pos resb 8   

section .text
global _start


int_to_string:
    mov ecx, digit_space + 7  
    mov ebx, 10
    mov byte [ecx], 0         
    
next_digit:
    xor edx, edx              
    div ebx                   
    add dl, '0'               
    dec ecx                   
    mov [ecx], dl             
    test eax, eax             
    jnz next_digit            
    mov eax, ecx              
    ret

_start:
    ; Display prompt
    mov eax, 4
    mov ebx, 1
    mov ecx, prompt
    mov edx, prompt_len
    int 80h

    ; Read input
    mov eax, 3
    mov ebx, 0
    mov ecx, search_num
    mov edx, 2
    int 80h

    
    movzx eax, byte [search_num]
    sub eax, '0'
    mov ebx, eax        

  
    xor ecx, ecx        ; ECX = 0 (array index)

search_loop:
    cmp ecx, array_len
    je number_not_found

    mov al, [array + ecx]
    cmp al, bl
    je number_found
    
    inc ecx
    jmp search_loop

number_found:
    mov eax, 4
    mov ebx, 1
    mov ecx, found_msg
    mov edx, found_len
    int 80h

    mov eax, ecx        
    call int_to_string  
    

    mov edx, digit_space + 8
    sub edx, eax        
    
    
    mov ecx, eax        
    mov eax, 4
    mov ebx, 1
    int 80h


    mov eax, 4
    mov ebx, 1
    mov ecx, newline
    mov edx, 1
    int 80h
    jmp exit

number_not_found:
    mov eax, 4
    mov ebx, 1
    mov ecx, not_found_msg
    mov edx, not_found_len
    int 80h

exit:
    mov eax, 1
    xor ebx, ebx
    int 80h
