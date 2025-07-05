; Program to count even and odd numbers in a user input array
; x86 Assembly for Linux

section .data
    prompt_size db "Enter the size of array (1-9): ", 0
    prompt_size_len equ $ - prompt_size
    
    prompt_element db "Enter element ", 0
    prompt_element_len equ $ - prompt_element
    
    colon db ": ", 0
    colon_len equ $ - colon
    
    even_msg db "Count of even numbers: ", 0
    even_len equ $ - even_msg
    
    odd_msg db "Count of odd numbers: ", 0
    odd_len equ $ - odd_msg
    
    newline db 10                         ; Newline character

section .bss
    array_size resb 2                     ; Buffer for array size input (digit + newline)
    array resd 10                         ; Reserve space for up to 10 integers (32-bit)
    element_input resb 12                 ; Buffer for element input
    element_index resb 1                  ; Current element index as ASCII
    even_count resb 1                     ; Count of even numbers
    odd_count resb 1                      ; Count of odd numbers
    display_buf resb 2                    ; Buffer for displaying numbers

section .text
    global _start

_start:
    ; Initialize counters
    mov byte [even_count], 0
    mov byte [odd_count], 0
    
    ; Prompt for array size
    mov eax, 4                            ; System call for write
    mov ebx, 1                            ; File descriptor 1 is stdout
    mov ecx, prompt_size                  ; Message to write
    mov edx, prompt_size_len              ; Message length
    int 80h                               ; Call kernel
    
    ; Read array size
    mov eax, 3                            ; System call for read
    mov ebx, 0                            ; File descriptor 0 is stdin
    mov ecx, array_size                   ; Buffer to store input
    mov edx, 2                            ; Read up to 2 bytes (digit + newline)
    int 80h                               ; Call kernel
    
    ; Convert array_size from ASCII to number
    movzx ecx, byte [array_size]          ; Get the first byte
    sub ecx, '0'                          ; Convert ASCII to number
    
    ; Store array size in EDI for later use
    mov edi, ecx
    
    ; Initialize array index to 0
    mov esi, 0
    
input_loop:
    ; Check if we've collected all elements
    cmp esi, edi
    jge count_elements                    ; If index >= size, we're done collecting
    
    ; Display element prompt with index
    mov eax, 4
    mov ebx, 1
    mov ecx, prompt_element
    mov edx, prompt_element_len
    int 80h
    
    ; Convert current index to ASCII for display
    mov eax, esi
    add eax, 1                            ; Make it 1-indexed for user-friendliness
    add eax, '0'                          ; Convert to ASCII
    mov [element_index], al
    
    ; Display current element index
    mov eax, 4
    mov ebx, 1
    mov ecx, element_index
    mov edx, 1
    int 80h
    
    ; Display colon
    mov eax, 4
    mov ebx, 1
    mov ecx, colon
    mov edx, colon_len
    int 80h
    
    ; Read the element
    mov eax, 3
    mov ebx, 0
    mov ecx, element_input
    mov edx, 12                           ; Allow up to 12 chars for number input
    int 80h                               ; Call kernel
    
    ; Simple conversion from ASCII to integer
    mov ebx, 0                            ; Clear EBX to hold our number
    mov ecx, 0                            ; Initialize counter
    
convert_loop:
    movzx eax, byte [element_input + ecx] ; Load next digit
    cmp al, 10                            ; Check if it's a newline
    je conversion_done                    ; If newline, conversion is done
    
    sub al, '0'                           ; Convert ASCII to number
    imul ebx, ebx, 10                     ; Multiply current value by 10
    add ebx, eax                          ; Add new digit
    
    inc ecx                               ; Move to next character
    jmp convert_loop                      ; Repeat for next digit
    
conversion_done:
    ; Store converted number in array
    mov [array + esi*4], ebx
    
    ; Move to next element
    inc esi
    jmp input_loop
    
count_elements:
    ; Reset array index to 0
    mov esi, 0
    
count_loop:
    ; Check if we've processed all elements
    cmp esi, edi
    jge display_results                   ; If index >= size, we're done counting
    
    ; Check if the current element is even or odd
    mov eax, [array + esi*4]
    test eax, 1                           ; Test least significant bit
    jnz odd_number                        ; If odd bit is set, it's odd
    
    ; Element is even
    inc byte [even_count]
    jmp continue
    
odd_number:
    ; Element is odd
    inc byte [odd_count]
    
continue:
    ; Move to next element
    inc esi
    jmp count_loop
    
display_results:
    ; Display even count message
    mov eax, 4
    mov ebx, 1
    mov ecx, even_msg
    mov edx, even_len
    int 80h
    
    ; Display even count value
    mov al, [even_count]
    call display_number
    
    ; Display odd count message
    mov eax, 4
    mov ebx, 1
    mov ecx, odd_msg
    mov edx, odd_len
    int 80h
    
    ; Display odd count value
    mov al, [odd_count]
    call display_number
    
    ; Exit program
    mov eax, 1                            ; System call number for exit
    xor ebx, ebx                          ; Return 0 status
    int 80h                               ; Call kernel

; Subroutine to display a number in AL register
display_number:
    add al, '0'                           ; Convert number to ASCII
    mov [display_buf], al                 ; Store in buffer
    mov byte [display_buf + 1], 10        ; Add newline character
    
    mov eax, 4                            ; System call for write
    mov ebx, 1                            ; File descriptor 1 (stdout)
    mov ecx, display_buf                  ; Buffer to write
    mov edx, 2                            ; Two bytes (digit + newline)
    int 80h                               ; Call kernel
    ret                                   ; Return from subroutine