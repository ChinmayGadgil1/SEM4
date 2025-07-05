section .data
    prompt_size db 'Enter array size: ', 0
    prompt_elem db 'Enter element ', 0
    colon db ': ', 0
    msg_array db 'Your array: [', 0
    comma db ', ', 0
    bracket db ']', 10, 0
    msg_even db 'Number of even elements: ', 0
    msg_odd db 'Number of odd elements: ', 0
    newline db 10, 0

section .bss
    array_size resb 1     ; Size of array
    array resb 20         ; Can store up to 20 single-digit numbers
    input_buffer resb 2   ; Input buffer (digit + newline)
    elem_index resb 1     ; Current element index
    even_count resb 1     ; Count of even numbers
    odd_count resb 1      ; Count of odd numbers
    display_buffer resb 2 ; Buffer for displaying numbers

section .text
global _start

; Define macros for read and write
%macro write 2
    mov eax, 4            ; sys_write
    mov ebx, 1            ; stdout
    mov ecx, %1
    mov edx, %2
    int 80h
%endmacro

%macro read 2
    mov eax, 3            ; sys_read
    mov ebx, 0            ; stdin
    mov ecx, %1
    mov edx, %2
    int 80h
%endmacro

_start:
    mov byte [even_count], 0
    mov byte [odd_count], 0
    
    ; Display prompt for array size
    write prompt_size, 18
    
    ; Read array size
    read input_buffer, 2
    
    ; Convert ASCII to number
    movzx eax, byte [input_buffer]
    sub al, '0'
    mov [array_size], al
    
    ; Initialize element index
    mov byte [elem_index], 0
    
read_elements:
    ; Check if we've read all elements
    movzx ecx, byte [elem_index]
    cmp cl, [array_size]
    jae analyze_array
    
    ; Display prompt for element
    write prompt_elem, 14
    
    ; Display current element index (add 1 for user-friendly 1-based indexing)
    movzx eax, byte [elem_index]
    inc eax
    add al, '0'
    mov [display_buffer], al
    write display_buffer, 1
    
    ; Display colon
    write colon, 2
    
    ; Read element value
    read input_buffer, 2
    
    ; Store the element in array
    movzx eax, byte [input_buffer]
    movzx ebx, byte [elem_index]
    mov [array + ebx], al
    
    ; Increment element index
    inc byte [elem_index]
    jmp read_elements

analyze_array:
    ; Display the array
    write msg_array, 13
    
    ; Reset element index for display
    mov byte [elem_index], 0
    
display_loop:
    ; Check if we've displayed all elements
    movzx ecx, byte [elem_index]
    cmp cl, [array_size]
    jae display_end
    
    ; Display current element
    movzx ebx, byte [elem_index]
    mov al, [array + ebx]
    mov [display_buffer], al
    write display_buffer, 1
    
    ; Check if this is the last element
    inc ecx
    cmp cl, [array_size]
    jae skip_comma
    
    ; Display comma
    write comma, 2
    
skip_comma:
    inc byte [elem_index]
    jmp display_loop

display_end:
    ; Display closing bracket
    write bracket, 2
    
    ; Count odd and even numbers
    mov byte [elem_index], 0
    
count_loop:
    ; Check if we've counted all elements
    movzx ecx, byte [elem_index]
    cmp cl, [array_size]
    jae display_counts
    
    ; Get current element
    movzx ebx, byte [elem_index]
    movzx eax, byte [array + ebx]
    sub al, '0'           ; Convert ASCII to number
    
    ; Check if odd or even (test bit 0)
    test al, 1
    jz count_even
    
    ; Odd number
    inc byte [odd_count]
    jmp next_count
    
count_even:
    ; Even number
    inc byte [even_count]
    
next_count:
    inc byte [elem_index]
    jmp count_loop

display_counts:
    ; Display even count message
    write msg_even, 25
    
    ; Convert even_count to ASCII and display
    movzx eax, byte [even_count]
    add al, '0'
    mov [display_buffer], al
    write display_buffer, 1
    
    ; Display newline
    write newline, 1
    
    ; Display odd count message
    write msg_odd, 24
    
    ; Convert odd_count to ASCII and display
    movzx eax, byte [odd_count]
    add al, '0'
    mov [display_buffer], al
    write display_buffer, 1
    
    ; Display newline
    write newline, 1
    
    ; Exit program
    mov eax, 1            ; sys_exit
    mov ebx, 0            ; Exit code 0
    int 80h