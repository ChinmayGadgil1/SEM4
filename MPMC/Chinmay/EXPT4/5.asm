section .data
    prompt1 db 'Enter first string: ', 0
    prompt1_len equ $-prompt1
    
    prompt2 db 'Enter second string: ', 0
    prompt2_len equ $-prompt2
    
    equal_msg db 'Strings are equal', 10
    equal_len equ $-equal_msg
    
    first_larger db 'First string is larger', 10
    first_larger_len equ $-first_larger
    
    second_larger db 'Second string is larger', 10
    second_larger_len equ $-second_larger
    
    newline db 10
    newline_len equ $-newline

section .bss
    string1 resb 100
    string2 resb 100
    str1_len resb 1
    str2_len resb 1

%macro write 2
    mov eax, 4
    mov ebx, 1
    mov ecx, %1
    mov edx, %2
    int 80h
%endmacro

%macro read 2
    mov eax, 3
    mov ebx, 0
    mov ecx, %1
    mov edx, %2
    int 80h
%endmacro

section .text
    global _start

_start:
    ; Get first string
    write prompt1, prompt1_len
    read string1, 100
    mov [str1_len], al
    
    ; Get second string
    write prompt2, prompt2_len
    read string2, 100
    mov [str2_len], al

    ; Compare strings
    mov esi, string1         
    mov edi, string2         
    mov ecx, 100            
    cld                     

compare_loop:
    cmpsb                   
    jne check_larger        
    cmp byte [esi-1], 10    
    je strings_equal        
    loop compare_loop

check_larger:
    mov al, [esi-1]         
    mov bl, [edi-1]         
    cmp al, bl
    ja first_is_larger      
    jmp second_is_larger    

strings_equal:
    write equal_msg, equal_len
    jmp exit

first_is_larger:
    write first_larger, first_larger_len
    jmp exit

second_is_larger:
    write second_larger, second_larger_len
    jmp exit

exit:
    mov eax, 1
    xor ebx, ebx
    int 80h
