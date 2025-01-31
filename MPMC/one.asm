section .data
msg db ' ',10
arr db 1,2,3,4,5
arrLen equ 5

%macro writesystem 2
mov eax,4
mov ebx,1
mov ecx, %1
mov edx, %2
int 80h
%endmacro

%macro readsystem 2
mov eax,3
mov ebx,2
mov ecx,%1
mov edx,%2
int 80h
%endmacro

section .bss
sum resb 5

section .text
global _start
_start:
    ; Initialize eax to 0
    xor eax, eax
    
    mov ecx, arrLen
    mov esi, arr        ; Correct: Load address of arr, not its contents

loop_start:
    add al, [esi]       ; Add byte-sized values
    inc esi 
    dec ecx 
    jnz loop_start

    ; Convert the numeric sum to ASCII before storing
    add al, '0'         ; Convert to ASCII
    mov [sum], al
    
    writesystem sum, 5
    
    mov eax, 1
    mov ebx, 0
    int 80h
