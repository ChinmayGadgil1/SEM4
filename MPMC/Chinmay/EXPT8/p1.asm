section .data
msg db "Enter 5 elements:"
msglen equ $-msg
size db 5

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

section .bss
arr resb 5
buff resb 1

section .text

global _start

_start:
    write msg,msglen
    xor esi,esi

get:
    read buff,1
    mov al, [buff]          ; Load the actual byte from buff
    mov [arr+esi], al       ; Store it in array
    inc esi
    cmp esi, 5              ; Compare with immediate value 5
    jl get                  ; Jump back if less than 5

    xor esi,esi             ; Reset counter for display

display:
    lea ecx, [arr+esi]      ; Get address of current array element
    write ecx, 1            ; Write 1 byte from that address
    inc esi
    cmp esi, 5              ; Compare with immediate value 5
    jl display              ; Jump back if less than 5

exit:
    mov eax,1
    mov ebx,0               ; Use 0 for successful exit
    int 0x80