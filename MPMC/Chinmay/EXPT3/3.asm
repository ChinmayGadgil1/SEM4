section .data
    msg1 db "Enter length: ", 0
    msg2 db "Enter width: ", 0
    msg3 db "Rectangle area: ", 0
    msg4 db "Rectangle perimeter: ", 0
    newline db 10, 0

section .bss
    length resd 1
    width resd 1
    area resd 1
    perimeter resd 1
    input resb 16

section .text
    global _start

_start:
    ; Prompt user for length
    mov eax, 4         ; sys_write
    mov ebx, 1         ; file descriptor: stdout
    mov ecx, msg1      ; message address
    mov edx, 14        ; message length
    int 0x80

    ; Read length
    mov eax, 3         ; sys_read
    mov ebx, 0         ; file descriptor: stdin
    mov ecx, input     ; buffer
    mov edx, 16        ; buffer size
    int 0x80

    ; Convert length from ASCII to integer
    mov eax, 0
    mov ebx, input
    call atoi
    mov [length], eax

    ; Prompt user for width
    mov eax, 4
    mov ebx, 1
    mov ecx, msg2
    mov edx, 13
    int 0x80

    ; Read width
    mov eax, 3
    mov ebx, 0
    mov ecx, input
    mov edx, 16
    int 0x80

    ; Convert width from ASCII to integer
    mov eax, 0
    mov ebx, input
    call atoi
    mov [width], eax

    ; area = length * width
    mov eax, [length]
    mul dword [width]
    mov [area], eax

    ; perimeter = 2 * (length + width)
    mov eax, [length]
    add eax, [width]
    shl eax, 1
    mov [perimeter], eax

    ; Print area label
    mov eax, 4
    mov ebx, 1
    mov ecx, msg3
    mov edx, 17
    int 0x80

    ; Print area
    mov eax, [area]
    call print_num

    ; Print a newline
    mov eax, 4
    mov ebx, 1
    mov ecx, newline
    mov edx, 1
    int 0x80

    ; Print perimeter label
    mov eax, 4
    mov ebx, 1
    mov ecx, msg4
    mov edx, 21
    int 0x80

    ; Print perimeter
    mov eax, [perimeter]
    call print_num

    ; Print a newline
    mov eax, 4
    mov ebx, 1
    mov ecx, newline
    mov edx, 1
    int 0x80

    ; Exit
    mov eax, 1
    xor ebx, ebx
    int 0x80

;-----------------------------------------
; atoi: Convert ASCII string to integer
;       ebx points to the input buffer
;       returns integer in eax
;-----------------------------------------
atoi:
    push ebx
    mov ecx, 0
parse_loop:
    movzx edx, byte [ebx]
    cmp edx, 0
    je done
    cmp edx, '0'
    jl done
    cmp edx, '9'
    jg done
    sub edx, '0'
    imul ecx, ecx, 10
    add ecx, edx
    inc ebx
    jmp parse_loop
done:
    mov eax, ecx
    pop ebx
    ret

;-----------------------------------------
; print_num: Print integer in eax to stdout
;-----------------------------------------
print_num:
    push eax       ; save original eax
    push ecx
    push edx
    push esi

    mov ecx, 0
    mov edx, 0
    push eax

.divide_loop:
    inc ecx
    mov edx, 0
    mov esi, 10
    idiv esi       ; divide eax by 10
    add edx, '0'   ; remainder -> ASCII code for digit
    push edx
    cmp eax, 0
    jnz .divide_loop

.print_loop:
    dec ecx
    mov eax, 4     ; sys_write
    mov ebx, 1     ; stdout
    mov edx, 1
    pop esi
    push ecx
    mov [input], esi
    mov ecx, input
    int 0x80
    pop ecx
    cmp ecx, 0
    jnz .print_loop

    pop eax
    pop esi
    pop edx
    pop ecx
    pop eax
    ret
