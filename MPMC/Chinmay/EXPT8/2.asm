section .data
    prompt db "Enter number: ", 0
    prompt_len equ $ - prompt
    pos_msg db "Number of positive numbers: ", 0
    pos_len equ $ - pos_msg
    neg_msg db "Number of negative numbers: ", 0
    neg_len equ $ - neg_msg
    newline db 10

section .bss
    array resw 5        
    num resw 1          
    pos_count resw 1    
    neg_count resw 1    

section .text
    global _start

_start:
    ; Initialize counters
    mov word [pos_count], 0
    mov word [neg_count], 0
    
    ; Input loop for 5 numbers
    mov ecx, 5          ; Counter for loop
    mov esi, array      ; Array index
    
input_loop:
    push ecx            ; Save counter
    
    ; Display prompt
    mov eax, 4
    mov ebx, 1
    mov ecx, prompt
    mov edx, prompt_len
    int 80h
    
    ; Read number
    mov eax, 3
    mov ebx, 0
    mov ecx, num
    mov edx, 2
    int 80h
    
    ; Convert ASCII to number
    mov ax, [num]
    sub ax, '0'
    
    ; Store number in array
    mov [esi], ax
    
    ; Check if positive or negative
    cmp ax, 0
    jl negative
    inc word [pos_count]
    jmp continue
    
negative:
    inc word [neg_count]
    
continue:
    add esi, 2          ; Move to next array element
    pop ecx             ; Restore counter
    loop input_loop
    
    ; Display results
    mov eax, 4
    mov ebx, 1
    mov ecx, pos_msg
    mov edx, pos_len
    int 80h
    
    ; Convert positive count to ASCII and display
    mov ax, [pos_count]
    add ax, '0'
    mov [num], ax
    mov eax, 4
    mov ebx, 1
    mov ecx, num
    mov edx, 1
    int 80h
    
    ; New line
    mov eax, 4
    mov ebx, 1
    mov ecx, newline
    mov edx, 1
    int 80h
    
    ; Display negative count message
    mov eax, 4
    mov ebx, 1
    mov ecx, neg_msg
    mov edx, neg_len
    int 80h
    
    ; Convert negative count to ASCII and display
    mov ax, [neg_count]
    add ax, '0'
    mov [num], ax
    mov eax, 4
    mov ebx, 1
    mov ecx, num
    mov edx, 1
    int 80h
    
    ; Exit program
    mov eax, 1
    xor ebx, ebx
    int 80h