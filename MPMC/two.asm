section .data
    msg1 db 'Enter the elements of the array:', 10
    msg1len equ $-msg1
    msg2 db 'Enter the number of elements in the array: '
    msg2len equ $-msg2
    msg3 db 'Enter element to search:', 10
    msg3len equ $-msg3
    msg4 db 'Found at position: '
    msg4len equ $-msg4
    msg5 db 'Element not found', 10
    msg5len equ $-msg5
    newline db 10
    newlinelen equ $-newline
    array db 0,0,0,0,0,0,0,0,0
    arraylen equ 9

section .bss
    num resb 2       ; To store number of elements
    element resb 2   ; To store each input element
    i resb 2         ; Counter
    position resb 2  ; To store position
    x resb 2         ; Search element

%macro writesystem 2
    mov eax, 4
    mov ebx, 1
    mov ecx, %1
    mov edx, %2
    int 80h
%endmacro

%macro readsystem 2
    mov eax, 3
    mov ebx, 0      ; Changed from 2 to 0 for stdin
    mov ecx, %1
    mov edx, %2
    int 80h
%endmacro

section .text
global _start
_start:
    ; Get number of elements
    writesystem msg2, msg2len
    readsystem num, 2
    mov al, [num]
    sub al, '0'      ; Convert ASCII to number
    mov [num], al

    ; Input array elements
    writesystem msg1, msg1len
    mov cl, [num]    ; Counter for loop
    mov esi, array   ; Array pointer

inputelement:
readsystem element,2
mov ebx, [element]
mov [esi], ebx
dec byte[num]
inc esi
cmp byte[num], '0'
jne inputelement


search_loop:
    mov al, [esi]
    cmp al, [x]
    je found
    inc esi
    inc dl
    loop search_loop

    ; Element not found
    writesystem msg5, msg5len
    jmp exit

found:
    writesystem msg4, msg4len
    add dl, '0'      ; Convert number to ASCII
    mov [position], dl
    writesystem position, 1
    writesystem newline, newlinelen

exit:
    mov eax, 1
    mov ebx, 0
    int 80h
